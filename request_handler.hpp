//
// Created by brani on 14.02.20.
//

#include <map>
#include <memory>
#include "json.hpp"

#ifndef WEBSOCKETS_COMMUNICATION_REQUEST_HANDLER_HPP
#define WEBSOCKETS_COMMUNICATION_REQUEST_HANDLER_HPP

#endif //WEBSOCKETS_COMMUNICATION_REQUEST_HANDLER_HPP


class GeneralRequestHandler {

public:
    using json = nlohmann::json;
    using map = std::map<std::string, std::string>;

    static std::pair<std::string, std::string> parse_request(std::string action_field) {
        std::string delimiter = ":";
        auto pos = action_field.find(delimiter);
        auto action = action_field.substr(0, pos);
        action_field.erase(0, pos + delimiter.length());
        return std::pair(action, action_field);
    }

    static auto string_to_json(const std::string& message) {
        return json::parse(message);
    }

    template <typename T>
    static auto json_to_string(const T& json_serializable_object) {
        json json_object(json_serializable_object);
        return json_object.dump();
    }
    static inline map get_status_ok() {
        return map{{"status", "ok"}};
    }
};


class ProfileRequestHandler: public GeneralRequestHandler {
public:
    static std::string set_profiles(const std::string & message) {
        auto instructions = string_to_json(message);
        /* DO SOME MANIPULATION */

        map response{{"action", "config:set_profiles"}, {"data", json_to_string(get_status_ok())}};
        return json_to_string(json(response));
    }

    static std::string get_profiles(const std::string & message) {
        /* call get_profiles */
        const map kFakeProfile{
                {"action", "config:get_profiles"},
                {"data", json_to_string(map{
                    {"some", "fake"}, {"data", "created"}})}
        };
        return json_to_string(kFakeProfile);
    }
};

struct SupportedRequest {
    std::map<std::string, std::function<std::string(const std::string&)>> requests{
            {"set_profiles", ProfileRequestHandler::set_profiles},
            {"get_profiles", ProfileRequestHandler::get_profiles}
    };

    auto get_request(const std::string & method) {
        return requests[method];
    }
};

std::unique_ptr<GeneralRequestHandler> request_factory(const SupportedRequest& request) {

    return std::make_unique<GeneralRequestHandler>();
}
