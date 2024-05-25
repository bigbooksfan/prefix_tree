#include "prefix_tree.h"

#include <iostream>

Prefix_tree::Prefix_tree() {
    root = new Node;
    stop_words = new Node;
}

Prefix_tree::~Prefix_tree() {
    delete root;
    delete stop_words;
}

void Prefix_tree::Add(const std::string& s) {
    // check for whitespaces
    size_t letter_pos = s.find_first_not_of(" ", 0);
    size_t whitespace_pos = s.find_first_of(" ", letter_pos);

    while (whitespace_pos != s.npos) {
        std::string tmp = s.substr(letter_pos, whitespace_pos - letter_pos);
        Add_word(tmp, root);

        letter_pos = s.find_first_not_of(" ", whitespace_pos);
        if (letter_pos == s.npos) break;
        whitespace_pos = s.find_first_of(" ", letter_pos);
    }

    if (letter_pos != s.npos) {
        std::string tmp = s.substr(letter_pos, whitespace_pos - letter_pos);
        Add_word(tmp, root);
    }
}

std::string Prefix_tree::Find(const std::string& s) {
    std::string ret;

    Node* runner = root;
    for (char c : s) {
        size_t letter_number = (size_t)c;
        if (runner->next_nodes[letter_number] == nullptr) {
            return "";
        }
        runner = runner->next_nodes[letter_number];
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
        size_t letter_number = (size_t)c;
        if (runner->next_nodes[letter_number] == nullptr) {
            return false;
        }
        runner = runner->next_nodes[letter_number];
    }
    return runner->is_word;
}

void Prefix_tree::Add_stop_word(const std::string &s) {
    // check for whitespaces
    size_t letter_pos = s.find_first_not_of(" ", 0);
    size_t whitespace_pos = s.find_first_of(" ", letter_pos);

    while (whitespace_pos != s.npos) {
        std::string tmp = s.substr(letter_pos, whitespace_pos - letter_pos);
        Add_word(tmp, stop_words);

        letter_pos = s.find_first_not_of(" ", whitespace_pos);
        if (letter_pos == s.npos) break;
        whitespace_pos = s.find_first_of(" ", letter_pos);
    }

    if (letter_pos != s.npos) {
        std::string tmp = s.substr(letter_pos, whitespace_pos - letter_pos);
        Add_word(tmp, stop_words);
    }
}

void Prefix_tree::Print_all() {
    // stop_words
    auto all_words = Get_all(stop_words);
    std::cout << "Stop-words: ";
    for (auto& s : all_words) {
        std::cout << s << " ";
    }
    std::cout << std::endl << "Dictionary:\n";

    // words in dict
    all_words = Get_all(root);
    for (auto& s : all_words) {
        std::cout << s << ";" << std::endl;
    }
}

std::vector<std::string> Prefix_tree::Get_all(Node* r) {
    std::vector<std::string> ret;
    std::string tmp;

    for (int i = 0; i < 256; ++i) {
        if (r->next_nodes[i] != nullptr) {
            Go_deeper(tmp, r->next_nodes[i], ret);
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
    for (int i = 0; i < 256; ++i) {
        if (node->next_nodes[i] != nullptr) {
            Go_deeper(s, node->next_nodes[i], cont);
        }
    }
}

void Prefix_tree::Add_word(const std::string& s, Node* r) {
    Node* runner = r;
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        size_t letter_number = (size_t)c;
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