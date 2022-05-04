#include <iostream>
#include <ctime>
#include "tree.h"
using namespace std;

void instructions();

int main()
{
    srand(time(NULL));
    Tree Tree, copyTree;
    int choice;
    cin >> Tree;

    do
    {
        instructions();
        cin >> choice;
        switch (choice)
        {
        case 1:
            cin >> Tree;
            break;
        case 2:
            cout << Tree;
            break;
        case 3:
            Tree.inOrder();
            break;
        case 4:
            Tree.preOrder();
            break;
        case 5:
            Tree.postOrder();
            break;
        case 6:
            cout << "\nInput the element to be deleted: ";
            int element;
            cin >> element;
            Tree.deleteElem(element);
            cout << Tree;
            break;
        case 7:
            Tree.deleteTree();
            cout << "\nThe tree has been deleted!\n\n";
            break;
        case 8:
            Tree.deleteDuplicates();
            cout << "The tree with no duplicates: \n" << Tree;
            break;
        case 9:
            cout << "\nTree height: " << Tree.height() << endl << endl;
            break;
        case 10:
            Tree.floor_by_floor();
            break;
        case 11:
            copyTree = Tree;
            cout << "Copied tree:\n" << Tree;
            break;
        }

    } while (choice != 12);
}

void instructions()
{
    cout << "Choose:" << endl
         << "1 - Add elements into the tree" << endl
         << "2 - Print tree" << endl
         << "3 - In order traversal" << endl
         << "4 - Pre order traversal" << endl
         << "5 - Post order traversal" << endl
         << "6 - Remove element" << endl
         << "7 - Remove tree " << endl
         << "8 - Delete dublicates" << endl
         << "9 - Tree height" << endl
         << "10 - Floor-by-floor traversal" << endl
         << "11 - Copy the tree" << endl
         << "12 - Finish" << endl
         << "?- ";
}
