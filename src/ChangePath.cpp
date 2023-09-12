/*
** EPITECH PROJECT, 2021
** B-YEP-400-NCY-4-1-indiestudio-jean.gauthier-damioli
** File description:
** changePath
*/

#include "ChangePath.hpp"

void changePath(void)
{

#ifdef _WIN32
    HMODULE handle;
    WCHAR   path[MAX_PATH] = { 0 };

    // This error should never happen...
    handle = GetModuleHandle(nullptr);
    if (handle == nullptr)
        throw std::runtime_error((std::string(__FILE__) + ": l." + std::to_string(__LINE__)).c_str());

    GetModuleFileNameW(handle, path, MAX_PATH);
    exec_path = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(std::wstring(path).substr(0, std::wstring(path).find_last_of('\\') + 1));
#else
    char  path[PATH_MAX + 1] = { 0 };

    // Find executable path from /proc/self/exe
    if (readlink("/proc/self/exe", path, sizeof(path) - 1) == -1)
        throw std::runtime_error((std::string(__FILE__) + ": l." + std::to_string(__LINE__)).c_str());

    exec_path = std::string(path).substr(0, std::string(path).find_last_of('/') + 1);
#endif
}