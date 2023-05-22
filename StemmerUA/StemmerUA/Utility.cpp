#include "Utility.h"

#include <windows.h>

std::string Utils::wstring_to_string(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string str_to(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &str_to[0], size_needed, NULL, NULL);
    return str_to;
}

std::wstring Utils::string_to_wstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstr_to(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr_to[0], size_needed);
    return wstr_to;
}

bool Utils::GraterWstringBySize::operator()(const std::wstring& l, const std::wstring& r) const
{
    return (l.size() > r.size());
}