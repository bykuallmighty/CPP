#ifndef INPUTCLASS_H
#define INPUTCLASS_H

#include <vector>
#include <string>

#include <boost/filesystem.hpp>



class InputOutput{
private:
    //contains all files in folder
    std::vector<boost::filesystem::path> files_;
    //contains lines of a file that passes checks
    std::vector<std::string> lines_;
    //names of files that are excluded from reading
    std::vector<std::string> excludedNames_;

    bool correctPath_;
    bool start_;

    HANDLE fileChanges_;
    DWORD dwWaitStatus_;
    

    int numberOfFiles_;

public:
    InputOutput() : correctPath_(false), start_(false), numberOfFiles_(0){};
    InputOutput(const Options &option);
    

    bool start(const Options &option, HWND &, HWND &);
    bool stop();

    void manageFiles(const boost::filesystem::path&, const std::string &, const std::string &, const std::string &,
        const std::string &, const std::vector<std::string> &, const std::string &, const bool &, HWND &, const bool &ifOnlyToTP01);
    //reads all files in directory and returns names
    std::vector<boost::filesystem::path> returnFilesInDir(const boost::filesystem::path &, bool &, HWND &);
    //checks if file passes certain checks, and also if it doesn't containe excludedNames in title
    bool ifProperFileExt(const boost::filesystem::path &, const std::string &, const std::vector<std::string> &, HWND &);
    //returns lines in file
    std::vector<std::string> returnLinesInFile(const boost::filesystem::path &, HWND &);
    //check lines in file
    bool ifLinesInFileCorrect(const std::vector<std::string> &, const bool &, HWND &);

    bool ifCorrectPath();//*/

    void AppendText(const HWND &, const std::string &);

};

#endif