#pragma once

#include <vector>
#include <string>

class Prefix_tree {
private:
    struct Node {
        char letter;
        std::vector<Node*> next_nodes
            = std::vector<Node*>(26, nullptr);
        
        bool is_word = false;
        int counter = 0;
    };

    Node* root = nullptr;
public:
    Prefix_tree();
    ~Prefix_tree();

    void Add(const std::string& s);
    std::string Find(const std::string& s);
    bool Is_in_dictionary(const std::string& s);

};