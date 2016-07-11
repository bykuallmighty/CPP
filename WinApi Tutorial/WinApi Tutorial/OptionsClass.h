#ifndef OPTIONCLASS_H
#define OPTIONCLASS_H

#include <string>
#include <vector>
#include <Windows.h>

class Options{
private:
    std::string readPlace_, writePlaceOne_,
        writePlaceTwo_, writePlaceTP01_,
        fileExt_;
    const std::string optionsPlace_;
    std::vector<std::string> exclWords_;

    bool ifConfirm_;
    bool ifCheck_;
    bool ifOnlyToTP01_;

    bool ifReadOptions_;
public:
    Options();

    std::string returnReadPlace() const;
    std::string returnReadPlace(HWND &) const;
    std::string returnWritePlaceOne() const;
    std::string returnWritePlaceOne(HWND &) const;
    std::string returnWritePlaceTwo()const;
    std::string returnWritePlaceTwo(HWND &)const;
    std::string returnWritePlaceTP01()const;
    std::string returnWritePlaceTP01(HWND &)const;

    void setReadPlace(const HWND &);
    void setWritePlaceOne(const HWND &);
    void setWritePlaceTwo(const HWND &);
    void setWritePlaceTP01(const HWND &);

    bool returnIfConfirm()const;
    bool returnIfConfirm(HWND &, const int &)const;
    void setIfConfirm(const HWND &, const int &);

    bool returnIfCheck()const;
    bool returnIfCheck(HWND &, const int &)const;
    void setIfChecked(const HWND &, const int &);

    bool returnIfOnlyToTP01()const;
    bool returnIfOnlyToTP01(HWND &, const int &)const;
    void setIfOnlyToTP01(const HWND &, const int &);

    std::string returnFileExt()const;
    std::string returnFileExt(HWND &)const;
    void setFileExt(const HWND &);

    std::vector<std::string> returnExclWords()const;
    std::vector<std::string> returnExclWords(HWND &)const;
    void setExclWords(const HWND &hwnd);
    


    bool returnIfReadOptions()const;

    LPCSTR StringToLPSTR(const std::string &)const;
    std::string HWNDTextToString(const HWND&)const;

    void saveOptions();
};

#endif