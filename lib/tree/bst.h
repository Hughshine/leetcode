#ifndef BST_H
#define BST_H
#include "../pch.h"

struct BstNode {
    int val;
    BstNode* left;
    BstNode* right;
    BstNode(int val) : val(val), left(nullptr), right(nullptr) {}
    ~BstNode() {left=nullptr; right=nullptr;} // 析构函数应该怎么写？
};

class BinarySearchTree {
private:
    BstNode* root;
public:
    BinarySearchTree():root(nullptr) {}
    bool find(int v);
    bool insert(int v);
    bool remove(int v);
private:
    bool insert(int v, BstNode*& node);
    // bool remove(int v, BstNode*& node);
    int get_min_val(BstNode* node);
    int delete_min_val(BstNode*& node);
};


#endif