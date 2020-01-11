#include <iostream>

#include "BST.hpp"

int main() {

    // Testing BSTNode ...
    std::cout << "Testing BSTNode ..." << std::endl;

    BSTNode<int> node(11, NULL, NULL);

    std::cout << "node : " << node << std::endl;

    // Testing BST ...
    std::cout << "Testing BST ..." << std::endl;

    BST<int> tree;

    tree.insert(10);
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    tree.insert(13);
    tree.insert(12);
    tree.insert(11);
    tree.insert(9);
    tree.insert(6);
    tree.insert(4);
    tree.printInorder();



    tree.remove(10);
    tree.remove(11);
    tree.remove(12);
    tree.remove(13);
    tree.remove(6);
    tree.remove(7);
    tree.remove(9);
    tree.printInorder();
    tree.remove(5);
    tree.printInorder();
    tree.remove(4);
    tree.printInorder();
    
    return 0;
}
