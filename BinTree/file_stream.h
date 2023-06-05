#pragma once

#include "using_head.h"

class ReadFileStream
{
private:
    ifstream file;

public:
    ReadFileStream(const string& file_name) : file(file_name)
    {
        if (!file.is_open())
        {
            cout << file_name << " does not exist!!!\n";
            exit(-1);
        }
    };
    ~ReadFileStream()
    {
        file.close();
    }
    explicit operator bool() const
    {
        return file.eof();
    }
    template <typename T>
    ifstream& operator>>(T& value)
    {
        file >> value;
        return file;
    }
    istream& get_line(string& str)
    {
        return getline(file, str);
    }
};

class WriteFileStream
{
private:
    ofstream file;

public:
    WriteFileStream(const string& file_name,
        ios_base::openmode mode = ios_base::out)
        : file(file_name, mode) {
    };
    ~WriteFileStream()
    {
        file.close();
    }

    template <typename T>
    ofstream& operator<<(const T& value)
    {
        file << value;
        return file;
    }
};