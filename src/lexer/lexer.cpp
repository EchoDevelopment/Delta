#include "lexer.h"

#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

#include "error/error.h"

#define DIGITS "0123456789"
#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
#define ALPHANUMERIC "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

std::vector<Token> lex(std::unordered_map<std::string, Token> map, const std::string& data)
{
    std::vector<Token> tokens;

    for (size_t i = 0; i < data.size(); i++)
    {
        if (map.contains(std::string(1, data[i]))) tokens.emplace_back(map[std::string(1, data[i])]);
        else
        {
            if (strchr(ALPHABET, data[i]) != nullptr) 
            {
                std::string str;

                while (data[i] != '\0')
                {
                    if (strchr(ALPHANUMERIC, data[i]) == nullptr)
                    {
                        std::stringstream sstr;
                        sstr << "Invalid character \'" << data[i] << "\' in identifier at " << i; 
                        throw std::runtime_error(sstr.str());
                    }
                    str.push_back(data[i]);
                    if (map.contains(std::string(1, data[i + 1])) || data[i + 1] == ' ') break;                
                    i++;
                }

                if (map.contains(str)) tokens.emplace_back(map[str]);
                else {
                    tokens.emplace_back(map["[alphanumeric]"].type, str);
                }
            } 
            else if (strchr(DIGITS, data[i]) != nullptr) 
            {
                tokens.emplace_back(map["[integer]"]);
                tokens.back().value = "";

                while (data[i] != '\0')
                {
                    if (strchr(DIGITS, data[i]) == nullptr)
                    {
                        std::stringstream sstr;
                        sstr << "Invalid character \'" << data[i] << "\' in numeric literal at " << i; 
                        throw std::runtime_error(sstr.str());
                    }
                    tokens.back().value.push_back(data[i]);
                    if (map.contains(std::string(1, data[i + 1])) || data[i + 1] == ' ') break;
                    i++;
                }
            }
        }
    }

    return tokens;
}