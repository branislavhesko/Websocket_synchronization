//
// Created by brani on 17.02.20.
//

#include <iostream>
#include "websocket_client.hpp"

WebSocketClient::WebSocketClient(std::string ip, int port): ip_(std::move(ip)), port_(port) {
    web_socket_.setUrl(ip + std::to_string(port));
    web_socket_.setHeartBeatPeriod(45);
    web_socket_.disablePerMessageDeflate();
    web_socket_.setOnMessageCallback([this](const ix::WebSocketMessagePtr &msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "CLIENT RECEIVED: " << msg->str << std::endl;
            std::string action, method;
            std::tie(action, method) = GeneralRequestHandler::parse_request(json::parse(msg->str)["action"]);
            if (action == "login") {
                return
            }
            web_socket_.send(SupportedRequest().get_request(method)(msg->str));
        }
    });
}

bool WebSocketClient::connect() {
    web_socket_.start();
    web_socket_.connect(1);
    return true;
}

bool WebSocketClient::login(WebSocketClient::LOGIN_TYPE login_type) {
    if (login_type == WebSocketClient::LOGIN_TYPE::PASSWORD) {
        web_socket_.send(json(login_via_password_request()).dump());
    } else if (login_type == WebSocketClient::LOGIN_TYPE::REFRESH_TOKEN) {
        web_socket_.send(json(login_via_refresh_token_request()).dump());
    } else {
        return false;
    }
}

WebSocketClient::map WebSocketClient::login_via_password_request() {
    return map{{"action", "user:login"}, {"type", "password"}, {"username", kUserLogin}, {"password", kUserPassword}};
}

WebSocketClient::map WebSocketClient::login_via_refresh_token_request() {
    return map{{"action", "user:login"}, {"type", "refresh_token"}, {"refresh_token", refresh_token_}};
}

void WebSocketClient::run() {
    connect();
    login(WebSocketClient::LOGIN_TYPE::PASSWORD);
}

