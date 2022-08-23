#include "util.h"

#include <fstream>
#include <iostream>
#include <string>

std::string removeChar(char character, const std::string& data)
{
    std::string newBuf;

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] != character) 
        {
            if (data[i] == '\'')
            {
                newBuf.push_back(data[i]);
                i++;
                for (; data[i] != '\''; i++)
                {
                    newBuf.push_back(data[i]);
                }
                newBuf.push_back(data[i]);
            } 
            else
            {
                newBuf.push_back(data[i]);
            }
        }
    }

    return newBuf;
}

std::string readFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::string str;

    file.seekg(0, std::ios::end);   
    str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return str;
}
