#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <string>

#include "HistoryClass.h"

History::History(const std::vector<std::string> &file, const std::string &file_name) : file_(file), file_name_(file_name){
    writeHistory(file, file_name);
}

void History::writeHistory(const std::vector<std::string> &file, const std::string &file_name){
    std::ofstream historyFile("history.txt", std::ofstream::app);
    time_t now; time(&now);
    tm *ltm = localtime(&now);
    historyFile << std::endl << file_name << " - " << ltm->tm_hour << ":" << ltm->tm_min << " - "
        << ltm->tm_mday << "." << ltm->tm_mon << "." << ltm->tm_year + 1900 << std::endl
        << std::endl;


    for (auto a : file){
        historyFile << file_name << " - " << ltm->tm_hour << ":" << ltm->tm_min << " - "
            << ltm->tm_mday << "." << ltm->tm_mon << "." << ltm->tm_year + 1900 << " - " << a << std::endl;
    }
}

std::vector<std::string> History::returnFile(){
        return file_;
}
