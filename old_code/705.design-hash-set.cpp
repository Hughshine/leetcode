/*
 * @lc app=leetcode id=705 lang=cpp
 *
 * [705] Design HashSet
 *
 * https://leetcode.com/problems/design-hashset/description/
 *
 * algorithms
 * Easy (57.79%)
 * Likes:    221
 * Dislikes: 55
 * Total Accepted:    36.9K
 * Total Submissions: 63.8K
 * Testcase Example:  '["MyHashSet","add","add","contains","contains","add","contains","remove","contains"]\n[[],[1],[2],[1],[3],[2],[2],[2],[2]]'
 *
 * Design a HashSet without using any built-in hash table libraries.
 * 
 * To be specific, your design should include these functions:
 * 
 * 
 * add(value): Insert a value into the HashSet. 
 * contains(value) : Return whether the value exists in the HashSet or not.
 * remove(value): Remove a value in the HashSet. If the value does not exist in
 * the HashSet, do nothing.
 * 
 * 
 * 
 * Example:
 * 
 * 
 * MyHashSet hashSet = new MyHashSet();
 * hashSet.add(1);         
 * hashSet.add(2);         
 * hashSet.contains(1);    // returns true
 * hashSet.contains(3);    // returns false (not found)
 * hashSet.add(2);          
 * hashSet.contains(2);    // returns true
 * hashSet.remove(2);          
 * hashSet.contains(2);    // returns false (already removed)
 * 
 * 
 * 
 * Note:
 * 
 * 
 * All values will be in the range of [0, 1000000].
 * The number of operations will be in the range of [1, 10000].
 * Please do not use the built-in HashSet library.
 * 
 * 
 */

// @lc code=start
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
    static void lrotate(AvlNode *&left, AvlNode *&parent);
    static void rrotate(AvlNode *&parent, AvlNode *&right);

    static int get_new_height(AvlNode* node);
    static int max(int a, int b);
    static int diff(AvlNode* l, AvlNode* r);
};

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
    bool ret = remove(v, root);
    if(ret == true) 
        balance(root);
    return ret;
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
            get_new_height(node);   // 可能是不需要的
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
    if(node == nullptr) {
        return false;
    }
    if(node->val == v) {
        AvlNode* l=node->left, *r=node->right;
        if(l == nullptr && r == nullptr) { // 没有孩子
            delete node;
            node = nullptr;
            return true;
        }

        if(l != nullptr && r != nullptr) { // 两个孩子
            int val = get_min_val(node->right);
            remove(val); // 这个被删除节点一定是单孩子情况
            node->val = val;
            return true;
        }

        {   // 一个孩子
            auto child = node->left!=nullptr?node->left:node->right;
            delete node;
            node = child;
            return true;
        }
    }
    if(node->val < v) {
        bool ret = remove(v, node->right);
        if(ret == true) {
            get_new_height(node); // 可能是不需要的，balance时不需要保证根的计数正确
            balance(node);
        }
        return ret;
    } else { // node->val > v
        bool ret = remove(v, node->left);
        if(ret == true) {
            get_new_height(node);
            balance(node);
        }
        return ret;
    }
}

/**
 * 这个节点的右子树层数最高为1，删除这个节点，一定造成其父节点左子树高度减少1。
 * 删除这个结点可能造成全树结构改变，单独写一个函数比较麻烦。
 */
int AvlTree::get_min_val(AvlNode *node) {
    if(node == nullptr) return -1;
    while(node->left!=nullptr) {
        node = node->left;
    }
    return node->val;
}

void AvlTree::balance(AvlNode*& node) {
    if(node == nullptr) return;
    AvlNode*& left = node->left;
    AvlNode*& right = node->right;
    if(diff(left, right) == 2) {
        if(diff(left->left, left->right) > 0) { // LL
            cout << "LL rotate" << endl;
            lrotate(left, node);
        } else if (diff(left->left, left->right) < 0) { // LR
            cout << "LR rotate" << endl;
            rrotate(left, left->right);
            lrotate(left, node);
        } else {
            cerr << "balance error" << endl;
            return;
        }
    } else if(diff(left, right)== -2) {
        if(diff(right->left, right->right) < 0) { // RR
            rrotate(node, right);
        } else if (diff(right->left, right->right) > 0) { // RL
            lrotate(right->left, right);
            rrotate(node, right);
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
class MyHashSet {
private:
    AvlTree* avl;
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        avl = new AvlTree();
    }
    
    void add(int key) {
        avl->insert(key);
    }
    
    void remove(int key) {
        avl->remove(key);
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return avl->find(key);
    }
};
// @lc code=end

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
    bool find(int v, BstNode* node, BstNode* parent);
    bool insert(int v, BstNode*& node);
    bool remove(int v, BstNode*& node);
    int get_min_val(BstNode* node);
    int delete_min_val(BstNode *&node);
};

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
    // 第二种情况：iter 有两个孩子
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
    return remove(v, root);
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
    int val = tmpl->val;
    BstNode* tmpl = tmp->left;
    tmp->left = tmpl->right;
    delete tmpl;
    return val;
}

class MyHashSet {
private:
    BinarySearchTree* bst;
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        bst = new BinarySearchTree();
    }
    
    void add(int key) {
        bst->insert(key);
    }
    
    void remove(int key) {
        bst->remove(key);
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return bst->find(key);
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

