#include <iostream>
#include <ixwebsocket/IXWebSocket.h>
#include <chrono>
#include <thread>
#include <string>

#include "timer.h"


int main() {
    using namespace std::chrono_literals;
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
    webSocket.setOnMessageCallback([](const ix::WebSocketMessagePtr &msg) {
                                       if (msg->type == ix::WebSocketMessageType::Message) {
                                           std::cout << msg->str << std::endl;
                                       }
                                   }
    );

// Now that our callback is setup, we can start our background thread and receive messages
    webSocket.start();
    webSocket.connect(1);
// Send a message to the server (default to TEXT mode)

    for (int i=0; i<100; i++) {
        webSocket.send(std::to_string(Timer::get_utc_seconds()) + "\t" + Timer::get_formatted_time());
        std::this_thread::sleep_for(1s);
    }

// ... finally ...

// Stop the connection
    webSocket.stop();
}