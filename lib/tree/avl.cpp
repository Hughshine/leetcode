#include "avl.h"
bool AvlTree::find(int v) {
    if(root == nullptr) return false;
    for(AvlNode* iter = root; iter!=nullptr;) {
        if (iter->val == v) return true;
        if (iter->val < v) {
            iter = iter->right;
        } else {
            iter = iter->left;
        }
    }
    return false;
}

bool AvlTree::insert(int v) {
    bool ret = insert(v, root);
    if(ret == true) {
        get_new_height(root);
        balance(root);
    }
    return ret;
}

bool AvlTree::remove(int v) {

}

bool AvlTree::insert(int v, AvlNode*& node) {
    if(node == nullptr) {
        node = new AvlNode(v);
        return true;
    } 
    if(node->val == v) {
        return false;
    }
    if(node->val < v) {
        bool ret = insert(v, node->right);
        if(ret) {
            get_new_height(node);
            balance(node->right);
            return true;
        }
        return false;
    }
    if(node->val > v) {
        bool ret = insert(v, node->left);
        if(ret) {
            get_new_height(node);
            balance(node->left);
            return true;
        }
        return false;
    }
    return false;
}


bool AvlTree::remove(int v, AvlNode*& node) {

}

void AvlTree::balance(AvlNode*& node) {
    AvlNode* left = node->left;
    AvlNode* right = node->right;
    if(diff(left, right) == 2) {
        if(diff(left, right) > 0) { // LL
            lrotate(left, node);
        } else if (diff(left, right) < 0) { // LR
            rrotate(left->right, left);
            lrotate(left, node);
        } else {
            cerr << "balance error" << endl;
            return;
        }
    } else if(diff(left, right)== -2) {
        if(diff(left, right) < 0) { // RR
            lrotate(node, right);
        } else if (diff(left, right) > 0) { // RL
            rrotate(right, right->left);
            lrotate(node, right);
        } else {
            cerr << "balance error" << endl;
        }
    }
}

// 注意，这里传入的left和parent是耦合的。。
void AvlTree::lrotate(AvlNode*& left, AvlNode*& parent) {
    AvlNode* new_parent = left;
    AvlNode* lr = left->right;
    left->right = parent;
    left = lr;
    parent = new_parent;
    get_new_height(parent->right);
    get_new_height(parent);
}

void AvlTree::rrotate(AvlNode*& parent, AvlNode*& right) {
    AvlNode* new_parent = right;
    AvlNode *rl = right->left;
    right->left = parent;
    right = rl;
    parent = new_parent;
    get_new_height(parent->left);
    get_new_height(parent);
}

inline int AvlTree::max(int a, int b) {
    return a > b ? a : b;
}

inline int AvlTree::get_new_height(AvlNode* node) {
    auto l = node->left;
    auto r = node->right;
    int lh, rh;
    if(l == nullptr) lh = 0;
    else lh = l->height;

    if(r == nullptr) rh = 0;
    else rh = r->height;
    
    node->height = max(lh, rh) + 1;
    return node->height;
}

inline int AvlTree::diff(AvlNode* l, AvlNode* r) {
    int lh, rh;
    if(l == nullptr) lh = 0;
    else lh = l->height;

    if(r == nullptr) rh = 0;
    else rh = r->height;
    
    return lh - rh;
}