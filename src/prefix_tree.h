#pragma once

#include <vector>
#include <string>

class Prefix_tree {
private:
    // nested class
    struct Node {
        char letter;
        std::vector<Node*> next_nodes
            = std::vector<Node*>(256, nullptr);
        
        bool is_word = false;
        int counter = 0;
    };

    Node* root = nullptr;
    Node* stop_words = nullptr;

    std::vector<std::string> Get_all(Node* r);
    void Go_deeper(
        std::string s,
        Node* node,
        std::vector<std::string>& cont);
    
    void Add_word(const std::string& s, Node* r);

public:
    Prefix_tree();
    ~Prefix_tree();

    void Add(const std::string& s);
    std::string Find(const std::string& s);
    bool Is_in_dictionary(const std::string& s);
    void Add_stop_word(const std::string& s);
    void Print_all();
};