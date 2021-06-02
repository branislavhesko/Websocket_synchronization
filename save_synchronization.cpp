//
// Created by brani on 09.02.20.
//

#include <iostream>
#include "save_synchronization.h"


void SaveSynchronization::save_entry(const Entry& entry) {
    std::string line_to_write = entry.to_line();
    file << line_to_write << std::endl;
}

SaveSynchronization::SaveSynchronization(std::string file_name): file_name(std::move(file_name)){
    file.open(this->file_name, std::ios::out);
    std::cout << "Is file opened? " << file.is_open() << std::endl;
    write_header(header_);
}

void SaveSynchronization::write_header(const std::string & header) {
    file << header << std::endl;
}

SaveSynchronization::~SaveSynchronization() {
    std::cout << "Calling destructor!" << std::endl;
    file.close();
}
