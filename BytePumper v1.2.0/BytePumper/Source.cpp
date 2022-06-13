#include <windows.h>
#include <commdlg.h>
#include <fstream>
#include "resource.h"
#include "resource1.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")

using namespace std;

#define FILE_SEARCH_BUTTON 3
#define PUMP_BUTTON 2
#define PATH_VAR 1
#define BYTE_BUTTON 4
#define KILOBYTE_BUTTON 5
#define MEGABYTE_BUTTON 6
#define GIGABYTE_BUTTON 7
#define CLEAN_BUTTON 8
#define ABOUT_BUTTON 9
#define INFO_BUTTON 10

HWND hwnd;
HWND pumpButton;
HWND fileSearchButton;
HWND byteButton;
HWND kiloByteButton;
HWND megaByteButton;
HWND gigaByteButton;
HMENU hFileMenu;
HMENU hMenu;
HWND path_var;
HWND fileSize;
HWND aboutButton;
ofstream file;
HWND cleanButton;
HWND infoButton;
HWND sizeText;
HBITMAP bmp, generateImage;
HWND image;
HBRUSH hb;
HBRUSH pincel;
HWND byteText;
HWND megabyteText;
HWND kilobyteText;
HWND gigabyteText;
int tipo;

void pathVar(HWND hwnd) {
    path_var = CreateWindowEx(0, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | 0, 10, 10, 380, 20, hwnd, NULL, NULL, NULL);
    fileSize = CreateWindowEx(0, L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | 0, 140, 45, 100, 20, hwnd, NULL, NULL, NULL);
    sizeText = CreateWindowEx(0, L"Static", L"Size -> ", WS_VISIBLE | WS_CHILD | 0, 100, 47, 35, 20, hwnd, NULL, NULL, NULL);
    byteText = CreateWindowEx(0, L"Static", L"Byte", WS_VISIBLE | WS_CHILD | 0, 30, 45, 50, 20, hwnd, NULL, NULL, NULL);
    kilobyteText = CreateWindowEx(0, L"Static", L"KiloByte", WS_VISIBLE | WS_CHILD | 0, 30, 75, 60, 20, hwnd, NULL, NULL, NULL);
    megabyteText = CreateWindowEx(0, L"Static", L"MegaByte", WS_VISIBLE | WS_CHILD | 0, 30, 105, 70, 20, hwnd, NULL, NULL, NULL);
    gigabyteText = CreateWindowEx(0, L"Static", L"GigaByte", WS_VISIBLE | WS_CHILD | 0, 30, 135, 60, 20, hwnd, NULL, NULL, NULL);
    SendMessage(path_var, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(fileSize, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(sizeText, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(byteText, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(kilobyteText, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(megabyteText, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(gigabyteText, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
}

void addBottons(HWND hwnd) {
    pumpButton = CreateWindowEx(0, L"button", (L"Pump File"), WS_VISIBLE | WS_CHILD | 0, 140, 120, 100, 25, hwnd, (HMENU)PUMP_BUTTON, NULL, NULL);
    fileSearchButton = CreateWindowEx(0, L"button", L"...", WS_VISIBLE | WS_CHILD | 0, 400, 10, 30, 20, hwnd, (HMENU)FILE_SEARCH_BUTTON, NULL, NULL);
    byteButton = CreateWindowEx(0, L"button", NULL, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | 0, 10, 39, 15, 25, hwnd, (HMENU)BYTE_BUTTON, NULL, NULL);
    kiloByteButton = CreateWindowEx(0, L"button", NULL, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | 0, 10, 69, 15, 25, hwnd, (HMENU)KILOBYTE_BUTTON, NULL, NULL);
    megaByteButton = CreateWindowEx(0, L"button", NULL, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | 0, 10, 99, 15, 25, hwnd, (HMENU)MEGABYTE_BUTTON, NULL, NULL);
    gigaByteButton = CreateWindowEx(0, L"button", NULL, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | 0, 10, 129, 15, 25, hwnd, (HMENU)GIGABYTE_BUTTON, NULL, NULL);
    cleanButton = CreateWindowEx(0, L"button", L"Clean", WS_VISIBLE | WS_CHILD | 0, 140, 80, 80, 25, hwnd, (HMENU)CLEAN_BUTTON, NULL, NULL);
    aboutButton = CreateWindowEx(0, L"button", L"About", WS_VISIBLE | WS_CHILD | 0, 140, 160, 80, 25, hwnd, (HMENU)ABOUT_BUTTON, NULL, NULL);
    infoButton = CreateWindowEx(0, L"button", L"Info", WS_VISIBLE | WS_CHILD | 0, 10, 160, 80, 25, hwnd, (HMENU)INFO_BUTTON, NULL, NULL);
    SendMessage(pumpButton, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(fileSearchButton, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(cleanButton, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(aboutButton, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
    SendMessage(infoButton, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
}

void setImages(HWND hwnd) {
    bmp = reinterpret_cast<HBITMAP>(LoadImage(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE));
    image = CreateWindowEx(0, L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 265, 55, 10, 10, hwnd, (HMENU)CLEAN_BUTTON, NULL, NULL);
    SendMessageW(image, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
}

bool validateFile(wchar_t* path) {
    ifstream openFile;
    openFile.open(path);
    if (openFile.fail()) {
        openFile.close();
        return false;
    }
    else {
        file.open(path, ios::app, ios::binary);
        if (file.fail()) {
            return false;
        }
        else {
            return true;
        }
    }
}

void openFile(HWND hwnd) {
    OPENFILENAME openFileName;
    wchar_t fileName[100];

    ZeroMemory(&openFileName, sizeof(OPENFILENAME));
    openFileName.lStructSize = sizeof(OPENFILENAME);
    openFileName.hwndOwner = hwnd;
    openFileName.lpstrFile = fileName;
    openFileName.lpstrFile[0] = '\0';
    openFileName.nMaxFile = 100;
    openFileName.lpstrFilter = L"All files\0*.*\0";
    openFileName.nFilterIndex = 1;

    GetOpenFileName(&openFileName);
    SetWindowText(path_var, openFileName.lpstrFile);
}

void pumpFile(HWND hwnd, int tipo) {
    int SIZE;
    wchar_t* data = new wchar_t[GetWindowTextLength(path_var) + 1];
    wchar_t* MB_SIZE = new wchar_t[GetWindowTextLength(fileSize) + 1];
    GetWindowText(path_var, data, GetWindowTextLength(path_var) + 1);
    GetWindowText(fileSize, MB_SIZE, GetWindowTextLength(fileSize) + 1);
    SIZE = (_wtol(MB_SIZE));
    if (validateFile(data)) {
        char byte[1];
        char kiloByte[1000];
        char megaByte[999999];
        for (int i = 0; i < SIZE; i++) {
            if (tipo == 1)
                file << byte;
            if (tipo == 2)
                file << kiloByte;
            if (tipo == 3)
                file << megaByte;
            if (tipo == 4) {
                for (int pos = 0; pos < 1000; pos++) {
                    file << megaByte;
                }
            }
        }
        file.close();
        MessageBox(NULL, L"The file has been pumped!", L"Finish", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(NULL, L"Unable to open the file", L"Error", MB_ICONERROR | MB_OK);
    }
    ZeroMemory(&data, sizeof(data));
}

void clean(HWND hwnd) {
    SetWindowText(path_var, L"");
    SetWindowText(fileSize, L"");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE:
        setImages(hwnd);
        addBottons(hwnd);
        pathVar(hwnd);
        pincel = CreateSolidBrush(RGB(0, 0, 0));
        break;
    case WM_CTLCOLORSTATIC:
        SetTextColor((HDC)wParam, RGB(255, 255, 255));
        SetBkColor((HDC)wParam, RGB(0, 0, 0));
        return (INT_PTR)pincel;
    case WM_COMMAND:
        switch (wParam) {
        case BYTE_BUTTON:
            tipo = 1;
            break;
        case KILOBYTE_BUTTON:
            tipo = 2;
            break;
        case MEGABYTE_BUTTON:
            tipo = 3;
            break;
        case GIGABYTE_BUTTON:
            tipo = 4;
            break;
        case PUMP_BUTTON:
            pumpFile(hwnd, tipo);
            break;
        case FILE_SEARCH_BUTTON:
            openFile(hwnd);
            break;
        case CLEAN_BUTTON:
            clean(hwnd);
            break;
        case INFO_BUTTON:
            MessageBox(NULL, L"On low PCs GigaByte mode may \ncause windowfreeze for a few seconds,\ndon´t close the application.", L"BytePumper v1.2.0 Info", MB_OK | MB_ICONINFORMATION);
            break;
        case ABOUT_BUTTON:
            MessageBox(NULL, L"Author:\nBl4ckV - 2022\n\nDeveloped in:\nNative C++\n\nSupported OS:\nAny Windows from WinXP to Win11\n32/64 bits", L"BytePumper v1.2.0 About", MB_OK | MB_ICONINFORMATION);
            break;
        }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, L"ByteApp");
    if (!hMutex) 
    {
        hMutex = CreateMutex(0, 0, L"ByteApp");
    }
    else
    {
        MessageBox(NULL, L"There is another instance running right now", L"Instance Error", MB_OK | MB_ICONEXCLAMATION);
        return 0;
    }
    
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = {};
    hb = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadIcon(hInstance, (LPCWSTR)IDI_ICON1);
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.style = CS_DBLCLKS;
    wc.lpszMenuName = NULL;
    wc.hbrBackground = hb;

    RegisterClass(&wc);
    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"BytePumper v1.2.0",
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 445, 230,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}