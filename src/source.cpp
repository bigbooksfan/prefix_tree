#include <iostream>

#include "prefix_tree.h"

void Check_dict(Prefix_tree& tree, const std::string& s) {
    bool ans1 = tree.Is_in_dictionary(s);
    std::cout << s << ": ";
    if (ans1 == true) std::cout << "+; ";
    else std::cout << "-; ";
}

int main() {
    Prefix_tree tree;

    tree.Add("class");
    tree.Add("classic");
    tree.Add("clang");
    tree.Add("day");
    tree.Add("daydream");

{
    std::string request = "da";
    std::string ans = tree.Find(request);

    std::cout << request << ": " << ans << std::endl;

    request = "clas"; ans = tree.Find(request);
    std::cout << request << ": " << ans << std::endl;
    request = "clan"; ans = tree.Find(request);
    std::cout << request << ": " << ans << std::endl;
    request = "qwerty"; ans = tree.Find(request);
    std::cout << request << ": " << ans << std::endl;
    request = "doom"; ans = tree.Find(request);
    std::cout << request << ": " << ans << std::endl;
    request = "d"; ans = tree.Find(request);
    std::cout << request << ": " << ans << std::endl;
    request = "dayd"; ans = tree.Find(request);
    std::cout << request << ": " << ans << std::endl;
}

    Check_dict(tree, "day");
    Check_dict(tree, "d");
    Check_dict(tree, "class");
    Check_dict(tree, "clas");
    Check_dict(tree, "classi");
    std::cout << std::endl;

    return 0;
}