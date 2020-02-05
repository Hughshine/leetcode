#ifndef BST_H
#define BST_H
#include "../pch.h"
using namespace std;
struct AvlNode {
    int val;
    AvlNode* left;
    AvlNode* right;
    int height;
    AvlNode(int val) : val(val), left(nullptr), right(nullptr), height(1) {}
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
    void balance(AvlNode*& node);
    static int get_new_height(AvlNode* node);
    static int max(int a, int b);
    static int diff(AvlNode* l, AvlNode* r);
    static void lrotate(AvlNode*& left, AvlNode*& parent);
    static void rrotate(AvlNode*& parent, AvlNode*& right);
};


#endif