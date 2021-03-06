#pragma once

#include <thread>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include "IWebSocket.hpp"

namespace QtPiDeck::Services {
class WebSocketpp final : public IWebSocket {
public:
  WebSocketpp() noexcept;
  ~WebSocketpp() noexcept;
  void connect(QStringView address) noexcept final;
  void disconnect() noexcept final;
  [[nodiscard]] auto send(QLatin1String message) noexcept -> std::optional<SendingError> final;
  void setTextReceivedHandler(TextReceivedHandler handler) noexcept final { m_textReceivedHandler = handler; }
  void setFailHandler(FailHandler handler) noexcept final { m_failHandler = handler; }
  void setConnectedHandler(ConnectedHandler handler) noexcept final { m_connectedHandler = handler; }

private:
  auto connected() noexcept -> bool;

  websocketpp::client<websocketpp::config::asio_client> m_webSocket{};
  websocketpp::connection_hdl m_connectionHandle{};
  TextReceivedHandler m_textReceivedHandler{};
  FailHandler m_failHandler{};
  ConnectedHandler m_connectedHandler{};
  std::thread m_iothread{};
};
}
