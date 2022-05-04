#include "tree.h"

//конструктор класса
Tree::Tree()
{
    rootPtr = NULL;
}

//деструктор класса
Tree::~Tree()
{
    deleteTree_helper(rootPtr);
}

//конструктор копирования
Tree::Tree(const Tree &original)
{
    rootPtr = NULL;
    copy(original);
}

// перегрузка оператора вывода
ostream &operator<<(ostream &output, const Tree &T)
{
    T.print_Tree();

    return output;
}

//перегрузка оператора ввода
istream &operator>>(istream &input, Tree &T)
{
    T.addElements();

    return input;
}

//перегрузка оператора присваивания
Tree &Tree::operator=(const Tree &rightTree)
{
    copy(rightTree);

    return *this;
}

bool Tree::isEmpty() const
{
    if (rootPtr == NULL)
        cout << "\nTree is empty!\n\n";

    return rootPtr == NULL;
}

//добавление элементов в дерево
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

//функция добавления элемента в дерево
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

//создание дерева рандомно
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

//создание дерева вручную
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

//порядковый обход
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

//предварительный обход
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

//отложенный обход
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

//удаление дерева
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

//высота дерева
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

//печать дерева
void Tree::print_Tree() const
{
    if (!isEmpty())
        print_helper(rootPtr);
}

void Tree::print_helper(TreeNode *treePtr, int indent) const
{
    if (treePtr != NULL)
    {
        if (treePtr->rightPtr != NULL)
            print_helper(treePtr->rightPtr, indent + 4);

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
            print_helper(treePtr->leftPtr, indent + 4);
        }
    }
}

//поэтажный обход дерева
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

//копирование дерева
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

//удаление элемента
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

//функция-помощник для удаления элемента
//поиск узла с максимальным значением
TreeNode *Tree::findMaximumKey(TreeNode *treePtr) const
{
    TreeNode *current = treePtr;
    while (current && current->rightPtr != NULL)
        current = current->rightPtr;

    return current;
}

//удаление дубликатов
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

bool Tree::inRight(TreeNode *treePtr, int value) const
{
    if (treePtr == NULL)
        return false;

    TreeNode *current = treePtr;
    while (current && current->leftPtr != NULL)
        current = current->leftPtr;

    return (current->data == value);
}

bool Tree::inLeft(TreeNode *treePtr, int value) const
{
    if (treePtr == NULL)
        return false;

    TreeNode *current = treePtr;
    while (current && current->rightPtr != NULL)
        current = current->rightPtr;

    return (current->data == value);
}