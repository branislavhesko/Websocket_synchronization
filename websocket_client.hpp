//
// Created by brani on 17.02.20.
//

#ifndef WEBSOCKETS_COMMUNICATION_WEBSOCKET_CLIENT_HPP
#define WEBSOCKETS_COMMUNICATION_WEBSOCKET_CLIENT_HPP

#include <ixwebsocket/IXWebSocket.h>

#include "json.hpp"
#include "request_handler.hpp"


class WebSocketClient {
    using json = nlohmann::json;
    using map = std::map<std::string, std::string>;
private:
    enum class LOGIN_TYPE{PASSWORD, REFRESH_TOKEN};
    map login_via_password_request();
    map login_via_refresh_token_request();

    ix::WebSocket web_socket_;
    std::string ip_;
    int port_;
    std::string refresh_token_ = "";
    const std::string kUserLogin = "core";
    const std::string kUserPassword = "insane";

    bool login(LOGIN_TYPE);

public:
    WebSocketClient(std::string ip, int port);
    bool connect();
    void run();
};


#endif //WEBSOCKETS_COMMUNICATION_WEBSOCKET_CLIENT_HPP
