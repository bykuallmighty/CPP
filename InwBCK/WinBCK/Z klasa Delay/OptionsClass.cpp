#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <Windows.h>

#include "OptionsClass.h"


    Options::Options():readPlace_("Sciezka do miejsca odczytu"), writePlaceOne_("Sciezka do zapisu pierwszej kopii"), 
        writePlaceTwo_("... druga kopia"), writePlaceDelay_("Sciezka do folderu tymczasowego"),writePlaceTP01_("Sciezka do TP01"),
        fileExt_(".DAT"), optionsPlace_("options.dat"), ifConfirm_(false), ifCheck_(true),ifOnlyToTP01_(false){
        std::ifstream options(optionsPlace_);
        if (options){
            std::string readPlace;
            std::getline(options, readPlace);


            std::string writePlaceOne;
            std::getline(options, writePlaceOne);


            std::string writePlaceTwo;
            std::getline(options, writePlaceTwo);

            std::string writePlaceDelay;
            std::getline(options, writePlaceDelay);

            std::string writePlaceTP01;
            std::getline(options, writePlaceTP01);


                readPlace_ = readPlace;
                writePlaceOne_ = writePlaceOne;
                writePlaceTwo_ = writePlaceTwo;
                writePlaceDelay_ = writePlaceDelay;
                writePlaceTP01_ = writePlaceTP01;
 


            std::string ifConfirm;
            std::getline(options, ifConfirm);
            if (ifConfirm == "true")
                ifConfirm_ = true;
            else
                ifConfirm_ = false;

            std::getline(options, fileExt_);

            std::string ifCheck;
            std::getline(options, ifCheck);
            if (ifCheck == "true")
                ifCheck_ = true;
            else
                ifCheck_ = false;

            std::string ifOnlyToTP01;
            std::getline(options, ifOnlyToTP01);
            if (ifOnlyToTP01 == "true")
                ifOnlyToTP01_ = true;
            else
                ifOnlyToTP01_ = false;

            while (!options.eof())
            {
                std::string exclWords;
                options >> exclWords;
                if (!exclWords.empty())
                {
                    exclWords_.push_back(exclWords);
                }
            }
            ifReadOptions_ = true;
        }
        else
        {
            ifReadOptions_ = false;
            options.close();
        }
    }

    std::string Options::returnReadPlace() const {
        return readPlace_;
    }
    std::string Options::returnReadPlace(HWND &hwnd) const {
        SetWindowText(hwnd, StringToLPSTR(readPlace_));
        return readPlace_;
    }
    std::string Options::returnWritePlaceOne() const {
        return writePlaceOne_;
    }
    std::string Options::returnWritePlaceOne(HWND &hwnd) const {
        SetWindowText(hwnd, StringToLPSTR(writePlaceOne_));
        return writePlaceOne_;
    }
    std::string Options::returnWritePlaceTwo()const{
        return writePlaceTwo_;
    }
    std::string Options::returnWritePlaceTwo(HWND &hwnd)const{
        SetWindowText(hwnd, StringToLPSTR(writePlaceTwo_));
        return writePlaceTwo_;
    }
    std::string Options::returnWritePlaceDelay()const{
        return writePlaceDelay_;
    }
    std::string Options::returnWritePlaceDelay(HWND &hwnd)const{
        SetWindowText(hwnd, StringToLPSTR(writePlaceDelay_));
        return writePlaceDelay_;
    }
    std::string Options::returnWritePlaceTP01()const{
        return writePlaceTP01_;
    }
    std::string Options::returnWritePlaceTP01(HWND &hwnd)const{
        SetWindowText(hwnd, StringToLPSTR(writePlaceTP01_));
        return writePlaceTP01_;
    }

    void Options::setReadPlace(const HWND &hwnd)
    {        
        readPlace_ = HWNDTextToString(hwnd);
        if (readPlace_.back() != '\\')
            readPlace_ += '\\';
    };
    void Options::setWritePlaceOne(const HWND &hwnd)
    {
        writePlaceOne_ = HWNDTextToString(hwnd);
        if (writePlaceOne_.back() != '\\')
            writePlaceOne_ += '\\';
    };
    void Options::setWritePlaceTwo(const HWND &hwnd)
    {
        writePlaceTwo_ = HWNDTextToString(hwnd);
        if (writePlaceTwo_.back() != '\\')
            writePlaceTwo_ += '\\';
    };
    void Options::setWritePlaceDelay(const HWND &hwnd)
    {
        writePlaceDelay_ = HWNDTextToString(hwnd);
        if (writePlaceDelay_.back() != '\\')
            writePlaceDelay_ += '\\';
    };
    void Options::setWritePlaceTP01(const HWND &hwnd)
    {
        writePlaceTP01_ = HWNDTextToString(hwnd);
        if (writePlaceTP01_.back() != '\\')
            writePlaceTP01_ += '\\';
    };    

    bool Options::returnIfConfirm()const{
        return ifConfirm_;
    }
    bool Options::returnIfConfirm(HWND &hwnd, const int &a)const{
        if (ifConfirm_)
        {
            CheckDlgButton(hwnd, a, BST_CHECKED);
        }
        else
        {
            CheckDlgButton(hwnd, a, BST_UNCHECKED);
        }
        return ifConfirm_;
    }
    void Options::setIfConfirm(const HWND &hwnd, const int &a){
        BOOL bChecked = (IsDlgButtonChecked(hwnd, a) == BST_CHECKED);
        if (bChecked)
        {
            ifConfirm_ = true;
        }
        else
        {
            ifConfirm_ = false;
        }
    }

    bool Options::returnIfCheck()const{
        return ifCheck_;
    }
    bool Options::returnIfCheck(HWND &hwnd, const int &a)const{
        if (ifCheck_)
        {
            CheckDlgButton(hwnd, a, BST_CHECKED);
        }
        else
        {
            CheckDlgButton(hwnd, a, BST_UNCHECKED);
        }
        return ifCheck_;
    }
    void Options::setIfChecked(const HWND &hwnd, const int &a){
        BOOL bChecked = (IsDlgButtonChecked(hwnd, a) == BST_CHECKED);
        if (bChecked)
        {
            ifCheck_ = true;
        }
        else
        {
            ifCheck_ = false;
        }
    }

    bool Options::returnIfOnlyToTP01()const
    {
        return ifOnlyToTP01_;
    }
    bool Options::returnIfOnlyToTP01(HWND &hwnd, const int &a)const
    {
        if (ifOnlyToTP01_)
        {
            CheckDlgButton(hwnd, a, BST_CHECKED);
        }
        else
        {
            CheckDlgButton(hwnd, a, BST_UNCHECKED);
        }
        return ifOnlyToTP01_;
    }
    void Options::setIfOnlyToTP01(const HWND &hwnd, const int &a){
        BOOL bChecked = (IsDlgButtonChecked(hwnd, a) == BST_CHECKED);
        if (bChecked)
        {
            ifOnlyToTP01_ = true;
        }
        else
        {
            ifOnlyToTP01_ = false;
        }
    }

    std::string Options::returnFileExt()const{
        return fileExt_;
    }//*/
    std::string Options::returnFileExt(HWND &hwnd)const
    {
        SetWindowText(hwnd, StringToLPSTR(fileExt_));
        return fileExt_;
    }//*/
    void Options::setFileExt(const HWND &hwnd){
        fileExt_ = HWNDTextToString(hwnd);
    }

    std::vector<std::string> Options::returnExclWords()const
    {
        return exclWords_;
    }//*/
    std::vector<std::string> Options::returnExclWords(HWND &hwnd)const
    {//BLAD! WYPISWANIE WYRAZOW ZAGROZONYCH
        std::string exclWords;
        for (auto a : exclWords_)
            exclWords += ';' + a;
        while(exclWords[0] == ';')
            exclWords.erase(0, 1);
        SetWindowText(hwnd, StringToLPSTR(exclWords));
        return exclWords_;
    }//*/
    void Options::setExclWords(const HWND &hwnd)
    {
        exclWords_.clear();
        std::string exclWords = HWNDTextToString(hwnd);
        std::stringstream ss(exclWords);
        std::string item;
        while (std::getline(ss, item, ';')){
            exclWords_.push_back(item);
        }
    }

    bool Options::returnIfReadOptions() const{
        return ifReadOptions_;
    }

    LPCSTR Options::StringToLPSTR(const std::string &str)const{
        LPCSTR lpcstr = str.c_str();
        return lpcstr;
    }
    std::string Options::HWNDTextToString(const HWND &hwnd)const{
        int memChar = GetWindowTextLength(hwnd) + 1;
        LPSTR windowText = new char[memChar + 1];
        GetWindowText(hwnd, windowText, memChar + 1);
        std::string swindowText = windowText;
        delete[] windowText;
        return swindowText;
    }

    void Options::saveOptions(){
        std::ofstream savingOptions(optionsPlace_);
        savingOptions << returnReadPlace() << std::endl <<
            returnWritePlaceOne() << std::endl << returnWritePlaceTwo() << std::endl <<
            returnWritePlaceDelay() << std::endl << returnWritePlaceTP01() << std::endl;
        savingOptions << (returnIfConfirm() == true ? "true" : "false") << std::endl;
        savingOptions << returnFileExt() << std::endl;
        savingOptions << (returnIfCheck() == true ? "true" : "false") << std::endl;
        savingOptions << (returnIfOnlyToTP01() == true ? "true" : "false") << std::endl;
        for (auto a : returnExclWords())
            savingOptions << a << ";";
        savingOptions.close();
    }
