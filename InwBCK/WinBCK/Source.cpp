#include <windows.h>
#include <windowsx.h>
#include <string>
#include <process.h>

#include "OptionsClass.h"
#include "InputOutputClass.h"



#define G_HBUTTON 100
#define G_HBUTTONINFO 109
#define G_HCHECKBOX1 101
#define G_HCHECKBOX2 102
#define G_HCHECKBOX3 103
#define G_RESULTS 110


LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;
HWND hwnd;
HWND g_hButton;
HWND g_hButtonInfo;
bool ifStart = true;

HWND g_hCheckBox1;
HWND g_hCheckBox2;
HWND g_hCheckBox3;

HWND g_tFileExt;
HWND g_NamesToOmit;
HWND g_Results;


HWND g_readPlace;
HWND g_writePlaceOne;
HWND g_writePlaceTwo;
HWND g_writePlaceTP01;

HWND g_textRd;
HWND g_textWr1;
HWND g_textWr2;
HWND g_textWrTP01;

Options options;
InputOutput inputOutput;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void AppendText(const HWND &hwnd, const std::string &winText);

//--- testujemy mt
void start(void *arg);
//bool threadTest = true;

//kiedys w przysz³osci: zabiezpieczenie przed zbyt duzym stringiem



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    
    // WYPE£NIANIE STRUKTURY
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // REJESTROWANIE KLASY OKNA
    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Wysoka Komisja odmawia rejestracji tego okna!", "Niestety...",
            MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // TWORZENIE OKNA


    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        NazwaKlasy,
        "Inwentaryzacja BCK",
        WS_OVERLAPPEDWINDOW | WS_BORDER,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        626,
        469,
        NULL,
        NULL,
        hInstance,
        NULL
        );

    if (hwnd == NULL)
    {
        MessageBox(NULL, "Okno odmówi³o przyjœcia na œwiat!", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    g_hButton = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "BUTTON",
        "START",
        WS_CHILD | WS_VISIBLE,
        0,
        220,
        610,
        30,
        hwnd, //uchwyt do okna g³ównego
        (HMENU)G_HBUTTON,  //identyfikator okna
        hInstance,  //uchwyt do naszego procesu okna w sys windows
        NULL
        );

    if (g_hButton == NULL)
    {
        MessageBox(NULL, "Okno odmówi³o przyjœcia na œwiat!", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }    

    g_hButtonInfo = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "BUTTON",
        "POMOC",
        WS_CHILD | WS_VISIBLE,
        550,
        310,
        60,
        30,
        hwnd, //uchwyt do okna g³ównego
        (HMENU)G_HBUTTONINFO,  //identyfikator okna
        hInstance,  //uchwyt do naszego procesu okna w sys windows
        NULL
        );

    if (g_hButtonInfo == NULL)
    {
        MessageBox(NULL, "Okno odmówi³o przyjœcia na œwiat!", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    g_hCheckBox1 = CreateWindowEx(
        0,
        "BUTTON",
        "Rzadanie potwierdzenia",
        WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
        350,
        250,
        150,
        30,
        hwnd,
        (HMENU)G_HCHECKBOX1,
        hInstance,
        NULL);

    if (g_hCheckBox1 == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }   

    g_hCheckBox2 = CreateWindowEx(
        0,
        "BUTTON",
        "Sprawdzanie poprawnoœci",
        WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
        350,
        280,
        150,
        30,
        hwnd,
        (HMENU)G_HCHECKBOX2,
        hInstance,
        NULL);

    if (g_hCheckBox2 == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    

    g_tFileExt = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "Wczytaj pliki z WYRAZEM w tytule(³¹cznie z roszerzeniem)",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL,
        350,
        340,
        260,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_tFileExt == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }
    

    g_NamesToOmit = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "Pomiñ pliki z wyrazami w tytule, wpisz wyrazy oddzielaj¹c poprzez ';'",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL,
        350,
        385,
        260,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_NamesToOmit == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }   

    g_Results = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE | ES_AUTOHSCROLL
        | ES_AUTOVSCROLL,
        0,
        0,
        610,
        220,
        hwnd,
        (HMENU)G_RESULTS,
        hInstance,
        NULL);

    if (g_Results == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    Edit_SetReadOnly(g_Results, true);

   


    g_readPlace = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "Sciezka odczytu",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL,
        0,
        250,
        300,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_readPlace == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }
    

    g_writePlaceOne = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "Sciezka zapisu - 1",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL,
        0,
        295,
        300,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_writePlaceOne == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }
    

    g_writePlaceTwo = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "Sciezka zapisu - 2",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL,
        0,
        340,
        300,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_writePlaceTwo == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }
   

    g_writePlaceTP01 = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "EDIT",
        "Sciezka do TP01",
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | ES_MULTILINE | ES_AUTOHSCROLL,
        0,
        385,
        300,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_writePlaceTP01 == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }
    

    g_hCheckBox3 = CreateWindowEx(
        0,
        "BUTTON",
        "Kopiuj tylko do TP01",
        WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
        350,
        310,
        150,
        30,
        hwnd,
        (HMENU)G_HCHECKBOX3,
        hInstance,
        NULL);

    if (g_hCheckBox3 == NULL)
    {
        MessageBox(NULL, "g_hCheckBox kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }
    

    g_textRd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "STATIC",
        "RD",
        WS_CHILD | WS_VISIBLE | BS_CENTER,
        300,
        250,
        35,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_textRd == NULL)
    {
        MessageBox(NULL, "g_textRd kicha", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    g_textWr1 = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "STATIC",
        "WR1",
        WS_CHILD | WS_VISIBLE | BS_CENTER,
        300,
        295,
        35,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_textWr1 == NULL)
    {
        MessageBox(NULL, "g_textWr1", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    g_textWr2 = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "STATIC",
        "WR2",
        WS_CHILD | WS_VISIBLE | BS_CENTER,
        300,
        340,
        35,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_textWr2 == NULL)
    {
        MessageBox(NULL, "g_textWr2", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }

    g_textWrTP01 = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        "STATIC",
        "TP01",
        WS_CHILD | WS_VISIBLE | BS_CENTER,
        300,
        385,
        35,
        45,
        hwnd,
        NULL,
        hInstance,
        NULL);

    if (g_textWrTP01 == NULL)
    {
        MessageBox(NULL, "g_textWrTP01", "Ale kicha...", MB_ICONEXCLAMATION);
        return 1;
    }


    if (options.returnIfReadOptions())
    {
        options.returnIfCheck(hwnd, G_HCHECKBOX2);
        options.returnIfConfirm(hwnd, G_HCHECKBOX1);
        options.returnFileExt(g_tFileExt);
        options.returnExclWords(g_NamesToOmit);
        options.returnReadPlace(g_readPlace);
        options.returnWritePlaceOne(g_writePlaceOne);
        options.returnWritePlaceTwo(g_writePlaceTwo);
        options.returnWritePlaceTP01(g_writePlaceTP01);
        options.returnIfOnlyToTP01(hwnd, G_HCHECKBOX3);
    }

    SendMessage(g_hButton, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_hButtonInfo, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_hCheckBox1, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_hCheckBox2, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_hCheckBox3, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_NamesToOmit, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_tFileExt, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_readPlace, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_writePlaceOne, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_writePlaceTwo, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_writePlaceTP01, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_Results, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_textRd, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_textWr1, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_textWr2, WM_SETFONT, (WPARAM)hNormalFont, 0);
    SendMessage(g_textWrTP01, WM_SETFONT, (WPARAM)hNormalFont, 0);


    ShowWindow(hwnd, nCmdShow); // Poka¿ okienko...
    UpdateWindow(hwnd);

    // Pêtla komunikatów
    while (GetMessage(&Komunikat, NULL, 0, 0))
    {
        TranslateMessage(&Komunikat);
        DispatchMessage(&Komunikat);
    }
    return Komunikat.wParam;




}

// OBS£UGA ZDARZEÑ
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        //before main window is created
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_COMMAND:
        switch (wParam)
        {
        case G_HBUTTON:
        {   
            if (ifStart)
            {
                options.setReadPlace(g_readPlace);
                options.setWritePlaceOne(g_writePlaceOne);
                options.setWritePlaceTwo(g_writePlaceTwo);
                options.setWritePlaceTP01(g_writePlaceTP01);
                options.setFileExt(g_tFileExt);
                options.setExclWords(g_NamesToOmit);

                

                options.saveOptions();
                SetWindowText(g_hButton, "STOP");
                SetWindowText(g_Results, "---------PROGRAM URUCHOMIONY---------\r\n");

                ifStart = false;
                _beginthread(start, 0, (void*)12);
                
            }
            else
            {
                SetWindowText(g_hButton, "START(czysci okno)");
                AppendText(g_Results, "----------PROGRAM ZATRZYMANY----------\r\n");                
                ifStart = true;
                inputOutput.stop();
            }
        }
            break;
        case G_HBUTTONINFO:
            MessageBox(hwnd, "Witaj w Inwentaryzacji BCK 1.07\r\n"
                "\r\nRD - miejsce odczytu\r\nWR1 - miejsce zapisu kopii"
                "\r\nWR2 - miejsce zapisu drugiej kopii"
                "\r\nTP01 - miejsce zapisu do TP01"
                "\r\nMiejsca do wpisania tekstu pod ikonka pomoc:"
                "\r\nPierwsze - pliki ktore musz¹ posiadaæ dany wyraz"
                "\r\naby by³y brane pod uwagê, mo¿na wpisaæ tylko jedn¹ cechê"
                "\r\nDrugie - pomija pliki które maj¹ w tytule wyrazy podane w"
                "\r\noknie tekstowym. Nale¿y je oddzieliæ u¿ywaj¹c ';', bierze pod uwagê spacjê."
                "\r\n\r\nUWAGA: Pliki które z powodzeniem zosta³y skopiowanie, zostan¹"
                "\r\nusuniête z miejsca Ÿród³owego"
                "\r\n\r\nUWAGA: Sprawdzanie poprawnoœci dzia³a tylko dla plików INV"
                "\r\n\r\nKlikniecie start zapisuje opcje!", "Krótka pomoc - autor: Przemys³aw £ybyk", MB_OK | MB_ICONINFORMATION);
            break;
        case G_HCHECKBOX1:
        {
            BOOL bChecked = (IsDlgButtonChecked(hwnd, G_HCHECKBOX1) == BST_CHECKED);
            if (bChecked){
                CheckDlgButton(hwnd, G_HCHECKBOX1, BST_UNCHECKED);
            }
            else
            {
                CheckDlgButton(hwnd, G_HCHECKBOX1, BST_CHECKED);
            }
            options.setIfConfirm(hwnd, G_HCHECKBOX1);

        }
            break;
        case G_HCHECKBOX2:
        {
            BOOL bChecked = (IsDlgButtonChecked(hwnd, G_HCHECKBOX2) == BST_CHECKED);
            if (bChecked){
                CheckDlgButton(hwnd, G_HCHECKBOX2, BST_UNCHECKED);
            }
            else
            {
                CheckDlgButton(hwnd, G_HCHECKBOX2, BST_CHECKED);
            }
            options.setIfChecked(hwnd, G_HCHECKBOX2);
        }
            break;
        case G_HCHECKBOX3:
        {
            BOOL bChecked = (IsDlgButtonChecked(hwnd, G_HCHECKBOX3) == BST_CHECKED);
            if (bChecked){
                CheckDlgButton(hwnd, G_HCHECKBOX3, BST_UNCHECKED);
            }
            else
            {
                CheckDlgButton(hwnd, G_HCHECKBOX3, BST_CHECKED);
            }
            options.setIfOnlyToTP01(hwnd, G_HCHECKBOX3);
        }
            break;
        }            
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void AppendText(const HWND &hwnd, const std::string &winText)
{
    int memChar = GetWindowTextLength(hwnd) + 1;
    LPSTR windowText = new char[memChar+1];
    GetWindowText(hwnd,windowText,memChar +1);
    std::string old = windowText;
    delete[] windowText;
    old += winText + "\r\n";
    SetWindowText(hwnd, old.c_str());    
}

void start(void *arg)
{
    inputOutput.start(options, g_Results, hwnd);
}