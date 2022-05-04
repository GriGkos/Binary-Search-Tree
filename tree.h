#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include "treenode.h"

using namespace std;

class Tree
{
    friend ostream &operator<<(ostream &, const Tree &);
    friend istream &operator>>(istream &, Tree &);

private:
    TreeNode *rootPtr;

    bool isEmpty() const;
    void createTreeRandomly();
    void createTreeManually();
    void insertNode(TreeNode *&, int);
    void deleteTree_helper(TreeNode *);
    void inOrder_helper(TreeNode *) const;
    void preOrder_helper(TreeNode *) const;
    void postOrder_helper(TreeNode *) const;
    void deleteElem_helper(TreeNode *&, int);
    void deleteDuplicates_helper(TreeNode *&);
    int height_helper(TreeNode *) const;
    void print_helper(TreeNode *, int = 0) const;
    void floor_by_floor_helper(TreeNode *) const;
    void inOrder_floor(TreeNode *, int, int) const;
    void copy_helper(const TreeNode *);
    TreeNode *findMaximumKey(TreeNode *) const;
    bool inLeft(TreeNode *, int) const;
    bool inRight(TreeNode *, int) const;

public:
    Tree();
    Tree &operator=(const Tree &);
    Tree(const Tree &);
    void deleteElem(int);
    void inOrder() const;
    void preOrder() const;
    void postOrder() const;
    void deleteTree();
    void print_Tree() const;
    void deleteDuplicates();
    int height() const;
    void floor_by_floor() const;
    void copy(const Tree &);
    void addElements();
    ~Tree();
};

#endif
