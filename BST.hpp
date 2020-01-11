#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTNode.hpp"

template <class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot();

    void insert(const T &data);
    void remove(const T &data);
    BSTNode<T> *find(const T &data);
    void printInorder();

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void printInorder(BSTNode<T> *node);
    void recursiveCopy(BSTNode<T> *root, BSTNode<T> *copy);
    void recursiveRemoveAll(BSTNode<T> *root);
    void recursiveInsert(const T &data, BSTNode<T> *current);
    void recursiveRemove(const T &data, BSTNode<T> *current, BSTNode<T> *prev);
    BSTNode<T>* recursiveFinder(const T &data, BSTNode<T> *current);
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_HPP

template <class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}

template <class T>
void BST<T>::recursiveCopy(BSTNode<T> *current, BSTNode<T> *copy){
    current->data = copy->data;
    if(copy->left){
        BSTNode<T> *newNode = new BSTNode<T>();
        current->left = newNode;
        recursiveCopy(newNode, copy->left);
    }
    if(copy->right){
        BSTNode<T> *newNode = new BSTNode<T>();
        current->right = newNode;
        recursiveCopy(newNode, copy->right);
    }
}

template <class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    root = NULL;

    if(obj.root){
        root = new BSTNode<T>();   
        recursiveCopy(root, obj.root);
    }
        
}
template <class T>
void BST<T>::recursiveRemoveAll(BSTNode<T> *root) {
    /* TODO */
    if (!root)
        return;

    if(root->left){
        recursiveRemoveAll(root->left);
    }
    if(root->right){
        recursiveRemoveAll(root->right);
    }
    delete root;
    root = NULL;
}

template <class T>
BST<T>::~BST() {
    /* TODO */
    recursiveRemoveAll(root);
}

template <class T>
BSTNode<T> *BST<T>::getRoot() {
    /* TODO */
    return root;
}



template <class T>
void BST<T>::recursiveInsert(const T &data, BSTNode<T> *current){
    if(current->data > data){
        if(current->left){
            recursiveInsert(data, current->left); 
        }
        else{
            BSTNode<T> *newNode = new BSTNode<T>(data, NULL, NULL);
            current->left = newNode;
        }
    }
    else if(current->data < data){
        if(current->right){
            recursiveInsert(data, current->right);
        }
        else{
            BSTNode<T> *newNode = new BSTNode<T>(data, NULL, NULL);
            current->right = newNode;  
        }
    }
}

template <class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    if(root){
        recursiveInsert(data, root);
    }
    else{
        root = new BSTNode<T>();
        root->data = data;
    }
}


template <class T>
void BST<T>::recursiveRemove(const T &data, BSTNode<T> *current, BSTNode<T> *prev){

    if (!current){
        return;
    }

    BSTNode<T> *to_replace;
    BSTNode<T> *second_prev;

    to_replace = second_prev = NULL; //ADDED
    
    if(current->data == data && current == prev){
        if(current->right){
            to_replace = current->right;
            while(to_replace->left){
                second_prev = to_replace;
                to_replace = to_replace->left;
            }
            if(current->right != to_replace){
                if(to_replace->right){
                    second_prev->left = to_replace->right;
                }
                else{
                    second_prev->left = NULL;
                }
                to_replace->right = current->right;
                to_replace->left = current->left;
                this->root = to_replace;
            }
            else{
                to_replace->left = current->left;
                this->root = to_replace;
                
            }
        }
        else if(current->left){
            this->root = current->left;
        }
        else if(!current->left && !current->right ){
            this->root = NULL;
        }
        delete current;
    }

    else if(current->data == data){
        if(current->right){
            to_replace = current->right;
            while(to_replace->left){
                second_prev = to_replace;
                to_replace = to_replace->left;
            }
            if(current->right == to_replace){
                if(prev->left == current){
                    prev->left = to_replace;
                }
                else if(prev->right == current){ //TYPO MADE BEFORE (prev->right == to_replace)
                    prev->right = to_replace;
                }
                if(current->left){
                    to_replace->left = current->left;
                }
            }
            else if(second_prev){
                if(to_replace->right){
                    second_prev->left = to_replace->right;
                }
                else{
                    second_prev->left = NULL;
                }
                if(prev->left == current){
                    prev->left = to_replace;
                }
                else if(prev->right == current){ //TYPO MADE BEFORE (prev->right == to_replace)
                    prev->right = to_replace;
                }
                to_replace->right = current->right;
                to_replace->left = current->left;
            }
        }

        else if(current->left){
            if(prev->right == current){
                prev->right = current->left;
            }
            else if(prev->left == current){
                prev->left = current->left;
            }
        }
        else if(!current->left && !current->right)  {
            if(prev->right == current){
                prev->right = NULL;
            }
            else if(prev->left == current){
                prev->left = NULL;
            }
        }
        delete current;
    }
    else{
        if(data < current->data){
            if(current->left){
                recursiveRemove(data, current->left, current);
            }
        }
        else if(data > current->data){
            if(current->right){
                recursiveRemove(data, current->right, current);
            }
        }
    }

}



template <class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    if (this->root){
        recursiveRemove(data, root, root);
    }
}

template <class T>
BSTNode<T>* BST<T>::recursiveFinder(const T &data, BSTNode<T> *current) {
    /* TODO */
    if(data == current->data){
        return current;
    }
    else if(data > current->data){
        if(current->right){
            return recursiveFinder(data, current->right);
        }
    }
    else {
        if(current->left){
            return recursiveFinder(data, current->left);
        }
    }
    return NULL;
}

template <class T>
BSTNode<T> *BST<T>::find(const T &data) {
    /* TODO */
    BSTNode<T> *finded =  recursiveFinder(data, root);
    return finded;
}     

template <class T>
void BST<T>::printInorder() {

    if (root == NULL) {
        std::cout << "{}" << std::endl;
    } else {
        std::cout << "{" << std::endl;
        printInorder(root);
        std::cout << std::endl << "}" << std::endl;
    }
}

template <class T>
void BST<T>::printInorder(BSTNode<T> *node) {

    if (node == NULL)
        return;

    printInorder(node->left);
    if (node->left) {
        std::cout << "," << std::endl;
    }
    std::cout << "\t" << node->data;
    if (node->right) {
        std::cout << "," << std::endl;
    }
    printInorder(node->right);
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if (this != &rhs){
        recursiveRemoveAll(root);
        root = new BSTNode<T>();
        recursiveCopy(root, rhs.root);
    }
    return *this;
}