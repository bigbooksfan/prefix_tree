#include "prefix_tree.h"

#include <iostream>

Prefix_tree::Prefix_tree() {
    root = new Node;
}

Prefix_tree::~Prefix_tree() {
    delete root;
}

void Prefix_tree::Add(const std::string& s) {
    // check for whitespaces
    size_t pos = s.find_first_of(" ", 0);
    if (pos != s.npos) {
        Add_text(s);
        return;
    }

    Node* runner = root;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        int letter_number = c - 'a';
        if (runner->next_nodes[letter_number] == nullptr) {
            // create node
            Node* tmp = new Node;
            runner->next_nodes[letter_number] = tmp;
            tmp->letter = c;
        }
        runner = runner->next_nodes[letter_number];
        ++runner->counter;
    }
    runner->is_word = true;
}

std::string Prefix_tree::Find(const std::string& s) {
    std::string ret;

    Node* runner = root;
    for (char c : s) {
        int letter_index = c - 'a';
        if (runner->next_nodes[letter_index] == nullptr) {
            return "";
        }
        runner = runner->next_nodes[letter_index];
        ret += c;
    }

    // check next leetters
    bool keep_going = true;
    if (runner->counter == 1) {
        // send out whole word
        while (keep_going) {
            keep_going = false;
            for (Node* node : runner->next_nodes) {
                if (node != nullptr) {
                    runner = node;
                    ret += runner->letter;
                    keep_going = true;
                }
            }
        }
    }

    return ret;
}

bool Prefix_tree::Is_in_dictionary(const std::string& s) {
    Node* runner = root;
    for (char c : s) {
        int letter_index = c - 'a';
        if (runner->next_nodes[letter_index] == nullptr) {
            return false;
        }
        runner = runner->next_nodes[letter_index];
    }
    return runner->is_word;
}

void Prefix_tree::Print_all() {
    auto all_words = Get_all();
    for (auto& s : all_words) {
        std::cout << s << std::endl;
    }
}

std::vector<std::string> Prefix_tree::Get_all() {
    std::vector<std::string> ret;
    std::string tmp;

    for (int i = 0; i < 26; ++i) {
        if (root->next_nodes[i] != nullptr) {
            Go_deeper(tmp, root->next_nodes[i], ret);
        }
    }
    return ret;
}

void Prefix_tree::Go_deeper(
    std::string s,
    Node* node,
    std::vector<std::string>& cont)
    {
    s += node->letter;
    if (node->is_word == true) {
        cont.push_back(s);
    }
    // DFS
    for (int i = 0; i < 26; ++i) {
        if (node->next_nodes[i] != nullptr) {
            Go_deeper(s, node->next_nodes[i], cont);
        }
    }
}

void Prefix_tree::Add_text(const std::string& s) {
    
}