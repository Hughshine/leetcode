#include "bst.h"
bool BinarySearchTree::find(int v) {
    if(root == nullptr) return false;
    for(BstNode* iter = root; iter!=nullptr;) {
        if (iter->val == v) return true;
        if (iter->val < v) {
            iter = iter->right;
        } else {
            iter = iter->left;
        }
    }
    return false;
}

bool BinarySearchTree::insert(int v) {
    return insert(v, root);
}

// false: 无需执行remove操作
bool BinarySearchTree::remove(int v) {
    if(root == nullptr) return false;
    BstNode* parent = nullptr;
    BstNode* iter = root;
    for(; iter!=nullptr;) {
        if (iter->val == v) break;
        if (iter->val < v) {
            parent = iter;
            iter = iter->right;
        } else {
            parent = iter;
            iter = iter->left;
        }
    }
    if(iter == nullptr) return false;
    // 第一种情况：iter 没有孩子
    if(iter->left == nullptr && iter->right == nullptr) {
        if(parent == nullptr) {
            delete root;
            root = nullptr;
            return true;
        }
        delete iter;
        if(parent->left == iter) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        return true;
    }
    // 第二种情况：iter 有两个孩子；
    // 1.
    // if(iter->left != nullptr && iter->right != nullptr) {
    //     int val = get_min_val(iter->right);
    //     remove(val); // 这里可能做了些无用功，正常只需接续子树查找即可，不需要重根重新查找。
    //     iter->val = val;
    //     return true;
    // }
    // 2. 用于替换的后继，一定不会有两个孩子，且不用树根查找删除
    if(iter->left != nullptr && iter->right != nullptr) {
        int val = delete_min_val(iter->right);
        iter->val = val;
        return true;
    }
    // 第三种情况：iter 有一个孩子
    {
        if(parent == nullptr) {
            root = iter->left!=nullptr?iter->left:iter->right;
            delete iter;
            return true;
        }
        if(iter->left != nullptr) {
            if(parent->left == iter) {
                parent->left = iter->left;
            } else {
                parent->right = iter->left;
            }
            return true;
        }
        {
            if(parent->left == iter) {
                parent->left = iter->right;
            } else {
                parent->right = iter->right;
            }
        }
        return true;
    }
}

bool BinarySearchTree::insert(int v, BstNode*& node) {
    if(node == nullptr) {
        node = new BstNode(v);
        return true;
    }
    if(node->val == v) return false;
    if(node->val > v) {
        return insert(v, node->left);
    } else {
        return insert(v, node->right);
    }
}

int BinarySearchTree::get_min_val(BstNode *node) {
    if(node == nullptr) return -1; 
    while(node->left!=nullptr) {
        node = node->left;
    }
    return node->val;
}

int BinarySearchTree::delete_min_val(BstNode*& node) {
    if(node == nullptr) return -1;
    if(node->left == nullptr) {
        int val = node->val;
        delete node;
        node = node->right;
        return val;
    }
    BstNode* tmp = node;
    while(tmp->left->left!=nullptr) {
        tmp = tmp->left;
    }
    int val = tmp->left->val;
    BstNode* tmpl = tmp->left;
    tmp->left = tmp->left->right;
    delete tmpl;
    return val;
}