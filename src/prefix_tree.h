#pragma once

#include <vector>
#include <string>

class Prefix_tree {
private:
    // nested class
    struct Node {
        char letter;
        std::vector<Node*> next_nodes
            = std::vector<Node*>(26, nullptr);
        
        bool is_word = false;
        int counter = 0;
    };

    Node* root = nullptr;

    std::vector<std::string> Get_all();
    void Go_deeper(
        std::string s,
        Node* node,
        std::vector<std::string>& cont);
    void Add_text(const std::string& s);

public:
    Prefix_tree();
    ~Prefix_tree();

    void Add(const std::string& s);
    std::string Find(const std::string& s);
    bool Is_in_dictionary(const std::string& s);
    void Add_stop_word(const std::string& s);
    void Print_all();
};