#include "avl.h"

int main()
{
    AvlTree* tree = new AvlTree();
    tree->insert(100);
    tree->insert(101);
    tree->insert(102);
    // tree->insert(103);
    tree->insert(104);
    cout << tree->find(104) << endl;
}