#include "avl.h"

int main()
{
    AvlTree* tree = new AvlTree();
    tree->insert(9);
    tree->remove(19);
    tree->insert(14);
    tree->remove(19);
    tree->remove(9);
    tree->insert(0);
    tree->insert(3);
    cout << tree->find(3) << endl;
    // tree->insert(4);
    // tree->insert(0);
    // tree->remove(9);
}