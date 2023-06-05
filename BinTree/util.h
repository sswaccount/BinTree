#pragma once
#include "using_head.h"

inline int randomInt(int l, int r)
{
    return rand() % (r - l) + l;
}

inline void create_file(const string& filename)
{
    try {
        fs::path path(filename);
        if (!fs::exists(path)) {
            fs::create_directories(path.parent_path());
            ofstream file(path);
            file.close();
        }
    }
    catch (const std::exception& e) {
        cout << "文件创建失败："
            << e.what() << endl;
    }
} 

inline void create_dir(const string& dirname)
{
    try {
        fs::path path(dirname);
        if (!fs::exists(path))
            fs::create_directories(path);
    }
    catch (const std::exception& e) {
        cout << "文件夹创建失败："
            << e.what() << endl;
    }
}

inline int count_dir_num(const string& dirname)
{
    try {
        fs::path path(dirname);
        int count = 0;
        for (auto entry : fs::directory_iterator(path)){
            ++count;
        }
        return count;
    }
    catch (const std::exception& e) {
        cout << "文件夹统计失败："
            << e.what() << endl;
    }
}

inline void remove_dir(const string& dirname)
{
    try {
        fs::path path(dirname);
        fs::remove_all(path);
    }
    catch (const std::exception& e) {
        cout << "文件夹统计失败："
            << e.what() << endl;
    }
}