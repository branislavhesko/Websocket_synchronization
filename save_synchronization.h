//
// Created by brani on 09.02.20.
//
#ifndef WEBSOCKETS_COMMUNICATION_SAVE_SYNCHRONIZATION_H
#define WEBSOCKETS_COMMUNICATION_SAVE_SYNCHRONIZATION_H

#include <fstream>
#include <string>
#include <utility>


class SaveSynchronization {
public:
    explicit SaveSynchronization(std::string file_name);
    ~SaveSynchronization();
    struct Entry {
        u_int64_t server_utc;
        u_int64_t client_utc;
        std::string server_formatted;
        std::string client_formatted;

        Entry(u_int64_t server_utc, u_int64_t client_utc, std::string server_str,
              std::string client_str) : server_utc(server_utc), client_utc(client_utc),
                                        server_formatted(std::move(server_str)),
                                        client_formatted(std::move(client_str)) {};
        [[nodiscard]] std::string to_line() const{
            return std::to_string(client_utc) + "\t" + client_formatted + "\t" +
                std::to_string(server_utc) + "\t" + server_formatted;
        }

    };

    void save_entry(const Entry& entry);


private:
    std::string file_name;
    std::fstream file;
    const std::string header_ = std::string("client_utc") + "\t" + "client_formatted" +
                                "\t" + "server_utc" + "\t" + "server_formatted" + "\n";

    void write_header(const std::string &);
};


#endif //WEBSOCKETS_COMMUNICATION_SAVE_SYNCHRONIZATION_H
