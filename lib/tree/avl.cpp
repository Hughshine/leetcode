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