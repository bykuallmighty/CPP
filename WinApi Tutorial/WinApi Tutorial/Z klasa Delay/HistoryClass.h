#ifndef HISTORYCLASS_H
#define HISTORYCLASS_H

#include <vector>
#include <fstream>
#include <time.h>
#include <string>


class History{
private:
    const std::vector<std::string> file_;
    const std::string file_name_;
public:
    History();
    History(const std::vector<std::string> &file, const std::string &file_name);

    void writeHistory(const std::vector<std::string> &file, const std::string &file_name);

    std::vector<std::string> returnFile();
};
#endif