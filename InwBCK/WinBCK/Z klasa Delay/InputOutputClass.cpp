#include <iostream>
#include <vector>
#include <string>

#include <boost/filesystem.hpp>
#include <algorithm>
#include <fstream>
#include <Windows.h>
#include <conio.h>


#include "OptionsClass.h"
#include "InputOutputClass.h"
#include "HistoryClass.h"

using namespace boost::filesystem;


    /*InputOutput::InputOutput(const Options &option) :correctPath_(true)
    {
        auto rdPl = option.returnReadPlace();
        auto ifConfirm = option.returnIfConfirm();
        auto fileExt = option.returnFileExt();
        auto exclWords = option.returnExclWords();
        auto wrPlOne = option.returnWritePlaceOne();
        auto wrPlTwo = option.returnWritePlaceTwo();
        auto wrPlTP01 = option.returnWritePlaceTP01();
        auto ifCheck = option.returnIfCheck();

        files_ = returnFilesInDir(rdPl, correctPath_);
        if (!files_.empty())
        {
            bool ifNoProperFiles = true;
            for (auto a : files_){
                if (ifConfirm){
                    if (ifProperFileExt(a, fileExt, exclWords))
                    {
                        std::cout << "\nZAIMPORTOWANY: " << a.filename();
                        ifNoProperFiles = false;
                        std::cout << "\nCZY KONTYNOWAC? T/N : ";
                        std::string toContinue;
                        std::cin >> toContinue;
                        if (toContinue == "T" || toContinue == "t")
                        {
                            manageFiles(a, rdPl, wrPlOne, wrPlTwo, wrPlTP01, exclWords, fileExt, ifCheck);
                            std::cout << "\nWYKONANO";
                        }
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                    }

                }
                else
                {
                    if (ifProperFileExt(a, fileExt, exclWords))
                    {
                        std::cout << "\nZAIMPORTOWANY: " << a.filename();
                        ifNoProperFiles = false;
                        manageFiles(a, rdPl, wrPlOne, wrPlTwo, wrPlTP01, exclWords, fileExt, ifCheck);
                        std::cout << "\nWYKONANO\n";
                    }
                }

            }
        }
        //std::cout << "BRAK PLIKOW SPELNIAJACYCH WYTYCZNE\n";
        //std::cout << "WCISNIJ DOWOLNY PRZYCISK ABY PRZERWAC\n";
        bool ifNoProperFiles = true;
        while (ifNoProperFiles)
        {
            Sleep(1000);
            files_ = returnFilesInDir(rdPl, correctPath_);
            for (auto a : files_){
                if (ifProperFileExt(a, fileExt, exclWords))
                {
                    ifNoProperFiles = false;
                }
            }
            if (_kbhit() || !correctPath_)
            {
                break;
            }
        }
    };//*/

// w czasie kopiowania numeruje pliki

InputOutput::InputOutput(const Options &option):correctPath_(true){
    
};
   

bool InputOutput::start(const Options &option, HWND &hwnd, HWND &hwndMainWindow)
{
        auto rdPl = option.returnReadPlace();
        auto ifConfirm = option.returnIfConfirm();
        auto fileExt = option.returnFileExt();
        auto exclWords = option.returnExclWords();
        auto wrPlOne = option.returnWritePlaceOne();
        auto wrPlTwo = option.returnWritePlaceTwo();
        auto wrPlTP01 = option.returnWritePlaceTP01();
        auto ifCheck = option.returnIfCheck();
        auto ifOnlyTP01 = option.returnIfOnlyToTP01();

        start_ = true;        

        fileChanges_ = FindFirstChangeNotification(option.StringToLPSTR(rdPl), false, FILE_NOTIFY_CHANGE_FILE_NAME);
        if (fileChanges_ == INVALID_HANDLE_VALUE)
        {
            AppendText(hwnd, "NIEPRAWID£OWA ŒCIE¯KA - RD.");
            return false;
        }
        else
        {
            AppendText(hwnd, "PRAWID£OWA ŒCIE¯KA! WYSZUKUJE.");
        }


        numberOfFiles_ = (returnFilesInDir(wrPlOne, correctPath_, hwnd).size() < returnFilesInDir(wrPlTwo, correctPath_, hwnd).size() ? 
            returnFilesInDir(wrPlTwo, correctPath_, hwnd).size() : returnFilesInDir(wrPlOne, correctPath_, hwnd).size()) + 1;



        files_ = returnFilesInDir(rdPl, correctPath_, hwnd);
        if (!files_.empty())
        {
            bool ifNoProperFiles = true;
            for (auto a : files_){
                if (ifConfirm){
                    if (ifProperFileExt(a, fileExt, exclWords, hwnd))
                    {
                        AppendText(hwnd, "---ZAIMPORTOWANO:");
                        AppendText(hwnd, a.filename().string());
                        ifNoProperFiles = false;
                        std::string pytanie = "Czy przekopiowaæ?\r\n" + a.filename().string();
                        if(MessageBox(hwnd, pytanie.c_str(), "Inwentaryzacja BZK", MB_OKCANCEL | MB_ICONWARNING)!= IDCANCEL)
                            manageFiles(a, rdPl, wrPlOne, wrPlTwo, wrPlTP01, exclWords, fileExt, ifCheck, hwnd, ifOnlyTP01);
                        else
                            AppendText(hwnd,"---ANULOWANO IMPORT PLIKU");
                        
                    }

                }
                else
                {
                    if (ifProperFileExt(a, fileExt, exclWords, hwnd))
                    {
                        AppendText(hwnd, "---ZAIMPORTOWANO:");
                        AppendText(hwnd, a.filename().string());
                        ifNoProperFiles = false;
                        manageFiles(a, rdPl, wrPlOne, wrPlTwo, wrPlTP01, exclWords, fileExt, ifCheck, hwnd, ifOnlyTP01);
                        AppendText(hwnd, "---WYKONANO");
                    }
                }

            }
        }
     
        

        //AppendText(hwnd, "CZEKAMY NA POWIADOMIENIE.");
        //przeniesc na zewnatrz
            while (start_)
            {
                dwWaitStatus_ = WaitForSingleObject(fileChanges_, INFINITE);
                switch (dwWaitStatus_)
                {
                case WAIT_OBJECT_0:
                    if (start_)
                    {
                        AppendText(hwnd, "ZAKTUALIZOWANO KATALOG.");
                        files_ = returnFilesInDir(rdPl, correctPath_, hwnd);
                        if (!files_.empty())
                        {
                            bool ifNoProperFiles = true;
                            for (auto a : files_){
                                if (ifConfirm){
                                    if (ifProperFileExt(a, fileExt, exclWords, hwnd))
                                    {
                                        AppendText(hwnd, "---ZAIMPORTOWANO:");
                                        AppendText(hwnd, a.filename().string());
                                        ifNoProperFiles = false;
                                        //std::cout << "\nCZY KONTYNOWAC? T/N : ";
                                        //std::string toContinue;
                                        //std::cin >> toContinue;
                                        //if (toContinue == "T" || toContinue == "t")
                                        //{
                                        manageFiles(a, rdPl, wrPlOne, wrPlTwo, wrPlTP01, exclWords, fileExt, ifCheck, hwnd, ifOnlyTP01);
                                        //    std::cout << "\nWYKONANO";
                                        //}
                                        //std::cin.clear();
                                        //std::cin.ignore(INT_MAX, '\n');
                                        AppendText(hwnd, "---WYKONANO");
                                    }

                                }
                                else
                                {
                                    if (ifProperFileExt(a, fileExt, exclWords, hwnd))
                                    {
                                        AppendText(hwnd, "---ZAIMPORTOWANO:");
                                        AppendText(hwnd, a.filename().string());
                                        ifNoProperFiles = false;
                                        manageFiles(a, rdPl, wrPlOne, wrPlTwo, wrPlTP01, exclWords, fileExt, ifCheck, hwnd, ifOnlyTP01);
                                        AppendText(hwnd, "---WYKONANO");
                                    }
                                }

                            }
                        }

                    }
                    break;
                case WAIT_ABANDONED:
                    AppendText(hwnd, "WAIT_ABANDONED");
                    break;
                case WAIT_TIMEOUT:
                    AppendText(hwnd, "WAIT_TIMEOUT");
                    break;
                case WAIT_FAILED:
                    AppendText(hwnd, "WAIT_FAILED");
                    break;
                default:
                    AppendText(hwnd, "UNHANDLED DWWAITSTATUS");
                    break;
                }
                if (start_)
                    if (FindNextChangeNotification(fileChanges_) == FALSE)
                        AppendText(hwnd, "FindNextChangeNotification FAILED");
            }
            //if (FindCloseChangeNotification(fileChanges) == FALSE)
            //    AppendText(hwnd, "FindCloseChangeNotification FAILED");

        //AppendText(hwnd, "ZATRZYMANO WATEK");
        return true;
};//*/

bool InputOutput::stop()
{
    start_ = false;
    FindCloseChangeNotification(fileChanges_);    
    return false;
}

void InputOutput::AppendText(const HWND &hwnd, const std::string &winText)
{
    int memChar = GetWindowTextLength(hwnd) + 1;
    LPSTR windowText = new char[memChar + 1];
    GetWindowText(hwnd, windowText, memChar + 1);
    std::string old = windowText;
    delete[] windowText;
    old += winText + "\r\n";
    SetWindowText(hwnd, old.c_str());
}


    void InputOutput::manageFiles(const path& a, const std::string &rdPl, const std::string&wrPlOne, const std::string&wrPlTwo,
        const std::string&wrPlTP01, const std::vector<std::string> &exclWords, const std::string &fileExt, const bool &ifCheck, HWND &hwnd, const bool &ifOnlyToTP01){

        lines_ = returnLinesInFile(a, hwnd);
        int copyPass = 0;
        if (ifLinesInFileCorrect(lines_, ifCheck, hwnd))
        {
            if (!ifOnlyToTP01)
            {
                std::ofstream writeCopyOne(wrPlOne + std::to_string(numberOfFiles_) + " " + a.filename().string());
                if (writeCopyOne)
                {
                    for (auto a : lines_)
                    {
                        writeCopyOne << a << std::endl;
                        copyPass += 1;
                    }
                    AppendText(hwnd, "---PRZEKOPIOWANO DO WR1");
                }
                else
                {
                    AppendText(hwnd, "---BRAK SCIE¯KI");
                    AppendText(hwnd, wrPlOne);
                }
                writeCopyOne.close();
            }

            if (!ifOnlyToTP01)
            {
                std::ofstream writeCopyTwo(wrPlTwo + std::to_string(numberOfFiles_) + " " + a.filename().string());
                if (writeCopyTwo)
                {
                    for (auto a : lines_)
                    {
                        writeCopyTwo << a << std::endl;
                        copyPass += 1;
                    }
                    AppendText(hwnd, "---PRZEKOPIOWANO DO WR2");
                }
                else
                {
                    AppendText(hwnd, "---BRAK SCIE¯KI");
                    AppendText(hwnd, wrPlTwo);
                }
                writeCopyTwo.close();
            }

            std::ofstream writeCopyTP01(wrPlTP01 + a.filename().string());
            if (writeCopyTP01)
            {

                for (auto a : lines_)
                {
                    writeCopyTP01 << a << std::endl;
                    copyPass += 1;
                }
                History history(lines_, a.filename().string());
                if (boost::filesystem::exists(a))
                    boost::filesystem::remove(a);
                AppendText(hwnd, "---PRZEKOPIOWANO DO TP01 I USUNIÊTO");

            }
            else
            {
                AppendText(hwnd, "---BRAK SCIE¯KI");
                AppendText(hwnd, wrPlTP01);
            }
            writeCopyTP01.close();
        }
        else
        {
            std::cout << "\nPLIK " << a.filename().string() << " NIE ZOSTAL ZAIMPORTOWANY";
        }//copies and deletes file       
    }
    //reads all files in directory and returns names
    std::vector<path> InputOutput::returnFilesInDir(const path &dirpath, bool &correctPath, HWND &hwnd) //to nie moze byc referencja O.o
    {
        //wprowadzic zabezpieczenia przed brakiem danych do wczytania!!!
        std::vector<path> dirFiles;
        if (is_directory(dirpath))
        {
            for (auto a = directory_iterator(dirpath); a != directory_iterator(); a++){
                dirFiles.push_back(*a);
            }
        }
        else
        {
            //std::cout << "Podany adres do przeszukiwania plikow nie istnieje\n";
            correctPath = false;
        }
        return dirFiles;
    }
    //checks if file passes certain checks, and also if it doesn't containe excludedNames in title
    bool InputOutput::ifProperFileExt(const path &file, const std::string &fileExt, const std::vector<std::string> &excludedNames, HWND &hwnd){
        std::string fileName = file.string();
        if (fileName.find(fileExt) != std::string::npos && std::none_of(excludedNames.begin(), excludedNames.end(), [fileName]
            (const std::string &a){ return fileName.find(a) != std::string::npos; }))
        {
            //std::cout << "\nZAIMPORTOWANY: "<< file.filename();
            return true;
        }
        else{
            //AppendText(hwnd, "NIEPOPRAWNA SCIEZKA");
            return false;
        }
        return false;
    }//*/
    //returns lines in file
    std::vector<std::string> InputOutput::returnLinesInFile(const path &file, HWND &hwnd)
    {
        std::ifstream fileToOpen(file.string(), std::ios_base::in);
        std::vector<std::string> linesInFile;

        if (fileToOpen)
        {
            for (std::string lines; std::getline(fileToOpen, lines);){
                linesInFile.push_back(lines);
                //std::cout << lines << "\n";
            }
        }
        return linesInFile;
    }
    //check lines in file
    bool InputOutput::ifLinesInFileCorrect(const std::vector<std::string> &linesInFile, const bool &ifCheck, HWND &hwnd)
    {
        if (!ifCheck)
            return true;
        bool isCorrect = true;
        int i = 1;
        for (auto a : linesInFile)
        {
            if (a.length() != 48)
            {
                isCorrect = false;
                AppendText(hwnd, "LINIA " + std::to_string(i) + " - bledna dlugosc lini");
            }
            if (a[0] != 'M')
            {
                isCorrect = false;
                AppendText(hwnd, "LINIA " + std::to_string(i) + " - brak 'M'");
            }
            std::string item_number(a.begin() + 12, a.begin() + 15);
            if (std::stoi(item_number) != i)
            {
                isCorrect = false;
                AppendText(hwnd, "LINIA " + std::to_string(i) + " - z³y numer porz¹dkowy");
            }
            ++i;
        }
        return isCorrect;
    }

    bool InputOutput::ifCorrectPath()
    {
        return correctPath_;
    }//*/


