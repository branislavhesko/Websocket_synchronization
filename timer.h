//
// Created by brani on 09.02.20.
//

#ifndef WEBSOCKETS_COMMUNICATION_TIMER_H
#define WEBSOCKETS_COMMUNICATION_TIMER_H

#include <zconf.h>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

struct Timer {
    using clock = std::chrono::system_clock;

    static u_int64_t get_utc_seconds() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now().time_since_epoch()).count();;
    }

    static std::string get_formatted_time() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        std::string output_string = oss.str();
        return output_string;
    }

    static std::pair<uint64_t, std::string> parse_client_message(const std::string& msg) {
        uint64_t utc = std::stol(msg.substr(0, msg.find('\t')));
        std::string formatted = msg.substr(msg.find('\t'), msg.size());
        return std::make_pair(utc, formatted);
    }
};

#endif //WEBSOCKETS_COMMUNICATION_TIMER_H
