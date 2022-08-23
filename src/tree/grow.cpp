#include "grow.h"

#include "util.h"
#include "node.h"

#include <iostream>

std::unordered_map<std::string, Token> createMapEntry(std::unordered_map<std::string, Token>& map, std::string from)
{
    size_t pos = from.find(':');
    std::string input = from.substr(0, pos);
    from.erase(0, pos + 1);

    pos = from.find(',');
    std::string tType = from.substr(0, pos);
    from.erase(0, pos + 1);

    map.insert({input, Token(tType, from)});

    return map;
}

std::unordered_map<std::string, Token> growLexMap(const std::string& filepath)
{
    Node* headNode = basicGrow(filepath);

    std::unordered_map<std::string, Token> toTokenMap;

    // Check if nodes are proper for a map based lexer
    if (headNode->data.find("lexer") < headNode->data.find("group")) throw std::runtime_error("Bad lexer file");

    headNode = &headNode->forward[0];
    if (headNode->data.find("map") == std::string::npos) throw std::runtime_error("Lexer file not valid to create a map");

    headNode = &headNode->forward[0];

    for (size_t i = 0; i < headNode->forward.size(); i++)
    {
        createMapEntry(toTokenMap, headNode->forward[i].data);
    }

    delete headNode;
    return toTokenMap;
} 

Node* basicGrow(const std::string& filepath)
{
    std::string file = readFile(filepath);
    file = removeChar(' ', file);
    file = removeChar('\n', file);
    file = removeChar('\r', file);

    unsigned int groupCount = 0;

    Node* node = new Node(nullptr);
    if (file[0] != '{') 
    {
        node->data = std::string("\0");
        node->forward.resize(1);
        node->forward[0] = nullptr;
        return node;
    }

    groupCount++;

    for (size_t i = 1; ; i++)
    {
        if (file[i] == '{') 
        {
            groupCount++;
            node->forward.emplace_back(node);
            node = &node->forward.back();
        }
        else if (file[i] == '}') 
        {
            groupCount--;
            if (groupCount == 0) break;
            node = node->back;
        }
        else if (file[i] == '\'')
        {
            i++;
            for (; file[i] != '\''; i++)
            {
                node->data.push_back(file[i]);
            }
        }
        else {
            node->data.push_back(file[i]);
        }
    }

    return node;
}