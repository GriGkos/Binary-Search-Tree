#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using namespace std;

class TreeNode
{
    friend class Tree;
    
private:
    TreeNode *leftPtr;
    int data;
    TreeNode *rightPtr;

public:
    TreeNode(TreeNode *left = NULL, int dat = 0, TreeNode *right = NULL)
    {
        leftPtr = left;
        data = dat;
        rightPtr = right;
    }
};

#endif