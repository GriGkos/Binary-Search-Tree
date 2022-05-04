#include "tree.h"

//class constructor
Tree::Tree()
{
    rootPtr = NULL;
}

//class destructor
Tree::~Tree()
{
    deleteTree_helper(rootPtr);
}

//copy constructor
Tree::Tree(const Tree &original)
{
    rootPtr = NULL;
    copy(original);
}

//the output operator overload
ostream &operator<<(ostream &output, const Tree &T)
{
    T.printTree(T.rootPtr);

    return output;
}

//the input operator overload
istream &operator>>(istream &input, Tree &T)
{
    T.addElements();

    return input;
}

//the assignment operator overload
Tree &Tree::operator=(const Tree &rightTree)
{
    copy(rightTree);

    return *this;
}

//checking for emptiness
bool Tree::isEmpty() const
{
    if (rootPtr == NULL)
        cout << "\nTree is empty!\n\n";

    return rootPtr == NULL;
}

//adding elements to the tree
void Tree::addElements()
{
    int choice;

    cout << "How to add elements to the tree? (1 - Manually / 2 - Random): ";

    do
    {
        cin >> choice;
        if ((choice != 1) && (choice != 2))
            cout << "Enter 1 or 2: ";

    } while ((choice != 1) && (choice != 2));

    switch (choice)
    {
    case 1:
        createTreeManually();
        break;

    case 2:
        createTreeRandomly();
        break;
    }

    cout << "\nTree:\n"
         << *this << endl;
}

//inserting a node to the tree
void Tree::insertNode(TreeNode *&treePtr, int value)
{
    if (treePtr == NULL)
    {
        treePtr = new TreeNode;
        if (treePtr != NULL)
        {
            treePtr->data = value;

            treePtr->leftPtr = NULL;
            treePtr->rightPtr = NULL;
        }
        else
            cout << value << " not inserted. No memory available. \n";
    }

    else if (value < treePtr->data)
        insertNode(treePtr->leftPtr, value);
    else if (value >= treePtr->data)
        insertNode(treePtr->rightPtr, value);
}

//creating tree randomly
void Tree::createTreeRandomly()
{
    srand(time(NULL));

    int count, item, from, to;

    cout << "How much numbers do you want to place in tree? : ";
    cin >> count;

    cout << "Random range from ... to ... : ";
    cin >> from >> to;

    cout << "The numbers being placed in the tree are: \n";
    for (int i = 1; i <= count; i++)
    {
        item = rand() % (abs(from - to) + 1) + min(from, to);
        cout << setw(5) << item;
        insertNode(rootPtr, item);
    }
    cout << endl;
}

//creating tree manually
void Tree::createTreeManually()
{
    int count, item;

    cout << "How much numbers do you want to place in tree? : ";
    cin >> count;

    for (int i = 1; i <= count; i++)
    {
        cout << "Enter " << i << " number: ";
        cin >> item;
        insertNode(rootPtr, item);
    }
}

//in order traversal
void Tree::inOrder() const
{
    if (!isEmpty())
    {
        cout << "\nIn order traversal: ";
        inOrder_helper(rootPtr);
        cout << "\n\n";
    }
}

void Tree::inOrder_helper(TreeNode *treePtr) const
{
    if (treePtr != NULL)
    {
        inOrder_helper(treePtr->leftPtr);
        cout << setw(5) << treePtr->data;
        inOrder_helper(treePtr->rightPtr);
    }
}

//pre order traversal
void Tree::preOrder() const
{
    if (!isEmpty())
    {
        cout << "\nPre order traversal: ";
        preOrder_helper(rootPtr);
        cout << "\n\n";
    }
}

void Tree::preOrder_helper(TreeNode *treePtr) const
{
    if (treePtr != NULL)
    {
        cout << setw(5) << treePtr->data;
        preOrder_helper(treePtr->leftPtr);
        preOrder_helper(treePtr->rightPtr);
    }
}

//post order traversal
void Tree::postOrder() const
{
    if (!isEmpty())
    {
        cout << "\nPost order traversal: ";
        postOrder_helper(rootPtr);
        cout << "\n\n";
    }
}

void Tree::postOrder_helper(TreeNode *treePtr) const
{
    if (treePtr != NULL)
    {
        postOrder_helper(treePtr->leftPtr);
        postOrder_helper(treePtr->rightPtr);
        cout << setw(5) << treePtr->data;
    }
}

//tree delition
void Tree::deleteTree()
{
    deleteTree_helper(rootPtr);
    rootPtr = NULL;
}

void Tree::deleteTree_helper(TreeNode *treePtr)
{
    if (treePtr != NULL)
    {
        deleteTree_helper(treePtr->leftPtr);
        deleteTree_helper(treePtr->rightPtr);

        delete treePtr;
    }
}

//tree printing
void Tree::printTree(TreeNode *treePtr, int indent) const
{
    if (treePtr != NULL)
    {
        if (treePtr->rightPtr != NULL)
            printTree(treePtr->rightPtr, indent + 4);

        if (indent != 0)
            cout << setw(indent) << ' ';

        if (treePtr->rightPtr != NULL)
            cout << " /" << endl
                 << setw(indent) << ' ';

        cout << treePtr->data << endl
             << " ";

        if (treePtr->leftPtr)
        {
            cout << setw(indent) << ' ' << " \\" << endl;
            printTree(treePtr->leftPtr, indent + 4);
        }
    }
}

//tree height
int Tree::height() const
{
    return height_helper(rootPtr);
}

int Tree::height_helper(TreeNode *treePtr) const
{
    if (treePtr == NULL)
        return 0;

    else
        return 1 + max(height_helper(treePtr->leftPtr), height_helper(treePtr->rightPtr));
}

//floor-by-floor tree traversal
void Tree::floor_by_floor() const
{
    floor_by_floor_helper(rootPtr);
}

void Tree::floor_by_floor_helper(TreeNode *treePtr) const
{
    int floor = 0;
    for (int i = 1; i <= height_helper(treePtr); i++)
    {
        cout << i << " Floor: ";
        inOrder_floor(treePtr, floor, i);
        cout << endl;
    }
    cout << endl;
}

//assistant function for floor-by-floor traversal
void Tree::inOrder_floor(TreeNode *treePtr, int floor, int i) const
{
    if (treePtr != NULL)
    {
        inOrder_floor(treePtr->leftPtr, ++floor, i);

        if (i == floor)
            cout << treePtr->data << " ";

        floor--;
        inOrder_floor(treePtr->rightPtr, ++floor, i);
    }
}

//tree copying
void Tree::copy(Tree const &original)
{
    if (rootPtr != NULL)
        deleteTree_helper(rootPtr);

    copy_helper(original.rootPtr);
}

void Tree::copy_helper(TreeNode const *treePtr)
{
    if (treePtr != NULL)
    {
        insertNode(rootPtr, treePtr->data);
        copy_helper(treePtr->leftPtr);
        copy_helper(treePtr->rightPtr);
    }
}

//element deletion
void Tree::deleteElem(int data)
{
    deleteElem_helper(rootPtr, data);
}

void Tree::deleteElem_helper(TreeNode *&treePtr, int value)
{
    if (treePtr == NULL)
        return;

    if (value < treePtr->data)
        deleteElem_helper(treePtr->leftPtr, value);

    else if (value > treePtr->data)
        deleteElem_helper(treePtr->rightPtr, value);

    else
    {
        if (treePtr->leftPtr == NULL && treePtr->rightPtr == NULL)
        {
            delete treePtr;
            treePtr = NULL;
        }

        else if (treePtr->leftPtr && treePtr->rightPtr)
        {
            TreeNode *predecessor = findMaximumKey(treePtr->leftPtr);

            treePtr->data = predecessor->data;

            deleteElem_helper(treePtr->leftPtr, predecessor->data);
        }

        else
        {
            TreeNode *child = (treePtr->leftPtr) ? treePtr->leftPtr : treePtr->rightPtr;
            TreeNode *curr = treePtr;

            treePtr = child;

            delete curr;
            curr = NULL;
        }
    }
}

//finding the node with a max value
TreeNode *Tree::findMaximumKey(TreeNode *treePtr) const
{
    TreeNode *current = treePtr;
    while (current && current->rightPtr != NULL)
        current = current->rightPtr;

    return current;
}

//duplicates deletion
void Tree::deleteDuplicates()
{
    deleteDuplicates_helper(rootPtr);
}

void Tree::deleteDuplicates_helper(TreeNode *&treePtr)
{
    if (treePtr != NULL)
    {
        while (inRight(treePtr->rightPtr, treePtr->data) || inLeft(treePtr->leftPtr, treePtr->data))
            deleteElem_helper(rootPtr, treePtr->data);

        deleteDuplicates_helper(treePtr->leftPtr);
        deleteDuplicates_helper(treePtr->rightPtr);
    }
}

//finding the min value of the subtree
bool Tree::inRight(TreeNode *treePtr, int value) const
{
    if (treePtr == NULL)
        return false;

    TreeNode *current = treePtr;
    while (current && current->leftPtr != NULL)
        current = current->leftPtr;

    return (current->data == value);
}

//finding the max value of the subtree
bool Tree::inLeft(TreeNode *treePtr, int value) const
{
    if (treePtr == NULL)
        return false;

    TreeNode *current = treePtr;
    while (current && current->rightPtr != NULL)
        current = current->rightPtr;

    return (current->data == value);
}
