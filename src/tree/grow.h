#pragma once

#include <unordered_map>

#include "lexer/token.h"
#include "node.h"

Node* basicGrow(const std::string& filepath);
std::unordered_map<std::string, Token> growLexMap(const std::string& filepath);