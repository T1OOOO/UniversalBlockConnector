#include "tcpservermulticontroller.h"
#include <QtDebug>

namespace {
const int defaultMaxConnections = 3;
}

TcpServerMultiController::TcpServerMultiController(QObject *parent)
    : ByteArrayDataController{parent} {
  m_server = new QTcpServer(this);
  connect(m_server, &QTcpServer::newConnection, this,
          &TcpServerMultiController::slot_onNewConnection);

  m_widget = new TcpServerMultiWidget();
  connect(m_widget, &TcpServerMultiWidget::signal_open, this,
          &TcpServerMultiController::slot_onOpen);
  connect(m_widget, &TcpServerMultiWidget::signal_close, this,
          &TcpServerMultiController::slot_onClose);
  connect(m_widget, &TcpServerMultiWidget::signal_closeSocket, this,
          &TcpServerMultiController::slot_onClose);

  connect(this, &TcpServerMultiController::signal_open, m_widget,
          &TcpServerMultiWidget::slot_onOpen);
  connect(this, &TcpServerMultiController::signal_close, m_widget,
          &TcpServerMultiWidget::slot_onClose);
  connect(this, &TcpServerMultiController::signal_error, m_widget,
          &TcpServerMultiWidget::slot_onError);
  registerWidget(m_widget);

  m_clientList.resize(5);
  m_clientList.fill(nullptr);
}

TcpServerMultiController::~TcpServerMultiController() { close(); }

bool TcpServerMultiController::open(const QString &address, const qint16 port) {
  close();

  if (!m_server->listen(QHostAddress(address), port)) {
    emit signal_close();

    return false;
  }

  emit signal_open();
  m_widget->setTitle("Listen");

  return true;
}

void TcpServerMultiController::close() {
  m_server->close();

  for (auto *sock : m_clientList) {
    if (sock == nullptr) {
      continue;
    }

    sock->disconnect();
    sock->close();
    sock->deleteLater();
  }

  m_clientList.fill(nullptr);

  emit signal_close();
}

void TcpServerMultiController::write(const QByteArray &data) {
  for (auto *sock : m_clientList) {
    if (sock == nullptr) {
      continue;
    }

    sock->write(data);
  }
}

void TcpServerMultiController::slot_onNewConnection() {
  while (m_server->hasPendingConnections()) {
    QTcpSocket *sock = m_server->nextPendingConnection();

    if (!hasClientFree()) {
      sock->close();
      sock->deleteLater();

      continue;
    }

    connect(sock, &QTcpSocket::readyRead, this,
            &TcpServerMultiController::slot_onReadyRead);
    connect(sock, &QTcpSocket::stateChanged, this,
            &TcpServerMultiController::slot_onStateChanged);
    connect(sock, &QTcpSocket::errorOccurred, this,
            &TcpServerMultiController::slot_onErrorOccurred);

    auto it = std::find_if(m_clientList.begin(), m_clientList.end(),
                           [](auto *sock) -> bool { return sock == nullptr; });
    if (it == m_clientList.end()) {
      sock->disconnect(this);
      sock->close();
      sock->deleteLater();

      continue;
    }

    *it = sock;

    const int num = std::distance(m_clientList.begin(), it);
    auto *model = m_widget->getModel();
    model->setClient(num, sock->peerAddress().toString(), sock->peerPort());
  }

  m_widget->updateColumnSize();
}

void TcpServerMultiController::slot_onStateChanged(
    QAbstractSocket::SocketState state) {
  auto *sock = qobject_cast<QTcpSocket *>(sender());
  if (sock == nullptr) {
    return;
  }

  if (state == QAbstractSocket::SocketState::ListeningState) {
  } else if (state == QAbstractSocket::SocketState::UnconnectedState) {
    removeClient(sock);
  }
}

void TcpServerMultiController::slot_onErrorOccurred(
    QAbstractSocket::SocketError error) {
  auto *sock = qobject_cast<QTcpSocket *>(sender());
  if (sock == nullptr) {
    return;
  }

  removeClient(sock);
}

void TcpServerMultiController::slot_onReadyRead() {
  auto *sock = qobject_cast<QTcpSocket *>(sender());
  if (sock == nullptr) {
    return;
  }

  if (sock->bytesAvailable() == 0) {
    return;
  }

  auto it =
      std::find_if(m_clientList.cbegin(), m_clientList.cend(),
                   [sock](auto *client) -> bool { return sock == client; });
  if (it == m_clientList.cend()) {
    return;
  }

  const int num = std::distance(m_clientList.cbegin(), it);
  const QByteArray data = sock->readAll();

  sendDataAll(num, data);
}

void TcpServerMultiController::onReceiveData(PortType portType,
                                             PortIndex portIndex,
                                             const QByteArray &data) {
  write(data);
}

int TcpServerMultiController::getClientUsed() const {
  const int count =
      std::count_if(m_clientList.cbegin(), m_clientList.cend(),
                    [](auto *sock) -> bool { return sock != nullptr; });

  return count;
}

bool TcpServerMultiController::hasClientFree() const {
  const int count = defaultMaxConnections - getClientUsed();

  return count > 0;
}

void TcpServerMultiController::removeClient(QTcpSocket *sock) {
  if (sock == nullptr) {
    return;
  }

  auto it = std::find(m_clientList.begin(), m_clientList.end(), sock);
  if (it != m_clientList.end()) {
    *it = nullptr;
  }

  const int num = std::distance(m_clientList.begin(), it);
  auto *model = m_widget->getModel();
  model->resetClient(num);

  sock->disconnect(this);
  sock->close();
  sock->deleteLater();

  m_widget->updateColumnSize();
}

void TcpServerMultiController::updateGui() {
  auto *model = m_widget->getModel();

  for (int i = 0; i < m_clientList.size(); i++) {
    const auto *sock = m_clientList.at(i);
    if (sock == nullptr) {
      model->resetClient(i);

      continue;
    }

    const QString address = sock->peerAddress().toString();
    const quint16 port = sock->peerPort();

    model->setClient(i, address, port);
  }

  m_widget->updateColumnSize();
}

void TcpServerMultiController::slot_onOpen(const QString &address,
                                           const quint16 port) {
  if (!open(address, port)) {
    logger()->debug() << "Failed to open";
  }
}

void TcpServerMultiController::slot_onClose() { close(); }

void TcpServerMultiController::slot_onCloseSocket(const int num) {
  if (num >= m_clientList.size()) {
    return;
  }

  auto *sock = m_clientList.at(num);

  removeClient(sock);
}
