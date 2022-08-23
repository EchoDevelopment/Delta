#pragma once

#include <unordered_map>
#include <vector> 
#include "token.h"

std::vector<Token> lex(std::unordered_map<std::string, Token> map, const std::string& data);