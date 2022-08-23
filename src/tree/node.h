#pragma once

#include <optional>
#include <vector>
#include <string>
#include <iostream>

struct Node
{
    std::vector<Node> forward;
    std::string data;
    Node* back;

    Node(Node* back) { this->back = back; }
    Node() { this->back = nullptr; }
};