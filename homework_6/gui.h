#pragma once
#include <windows.h>
#include <commdlg.h>
#include <string>

std::wstring openFileDialog(); // 注意回傳型別改為 wstring

std::wstring openFileDialog() {
    wchar_t filename[MAX_PATH] = L"";

    OPENFILENAMEW ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";  // English filter
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    ofn.lpstrTitle = L"Select a Parameter File";  // <<< English Title

    if (GetOpenFileNameW(&ofn)) {
        return std::wstring(filename);
    }
    else {
        return L"";
    }
}
