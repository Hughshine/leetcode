#ifndef BST_H
#define BST_H
#include "../pch.h"

struct AvlNode {
    int val;
    AvlNode* left;
    AvlNode* right;
    int height;
    AvlNode(int val) : val(val), left(nullptr), right(nullptr), height(0) {}
    ~AvlNode() {left=nullptr; right=nullptr;} 
};

class AvlTree {
private:
    AvlNode* root;
public:
    AvlTree():root(nullptr) {}
    bool find(int v);
    bool insert(int v);
    bool remove(int v);
private:
    bool find(int v, AvlNode* node, AvlNode* parent);
    bool insert(int v, AvlNode*& node);
    bool remove(int v, AvlNode*& node);
    int get_min_val(AvlNode* node);
};


#endif