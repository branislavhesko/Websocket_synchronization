//
// Created by brani on 14.02.20.
//


#include <iostream>
#include <ixwebsocket/IXWebSocket.h>
#include <chrono>
#include <thread>
#include <string>
#include <queue>

#include "json.hpp"
#include "request_handler.hpp"


int main() {
    using namespace std::chrono_literals;
    using json = nlohmann::json;
    bool server_running = true;
// Our websocket object
    ix::WebSocket webSocket;

    std::string url("ws://127.0.0.1:3000");
    webSocket.setUrl(url);

// Optional heart beat, sent every 45 seconds when there is not any traffic
// to make sure that load balancers do not kill an idle connection.
    webSocket.setHeartBeatPeriod(45);

// Per message deflate connection is enabled by default. You can tweak its parameters or disable it
    webSocket.disablePerMessageDeflate();

// Setup a callback to be fired when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback([&webSocket](const ix::WebSocketMessagePtr &msg) {
                                       if (msg->type == ix::WebSocketMessageType::Message) {
                                           std::cout << "CLIENT RECEIVED: " << msg->str << std::endl;
                                           std::string action, method;
                                           std::tie(action, method) = GeneralRequestHandler::parse_request(json::parse(msg->str)["action"]);
                                           webSocket.send(SupportedRequest().get_request(method)(msg->str));
                                       }
                                   }
    );

// Now that our callback is setup, we can start our background thread and receive messages
    webSocket.start();
    webSocket.connect(1);
// Send a message to the server (default to TEXT mode)

    while(server_running) {
        std::this_thread::sleep_for(300ms);
        webSocket.send("I want a request!");
    }

// ... finally ...

// Stop the connection
    webSocket.stop();
}