
#ifndef BSTREE_H
#define BSTREE_H
#include "account.h"
#include <iostream>
 
//node class
class Node {
 //BStree has access to node
 friend class BSTree;
 
 public:
 explicit Node(Account* account);
 Account *accountInNodeClass;
 Node *right;
 Node *left;
 
};

//BSTree class
class BSTree {
public:
 // Create BST
 BSTree();
 
 // Delete all nodes in BST
 ~BSTree();
 
 // Insert new account
 bool insert(Account *account);
 
 // Retrieve account
 // returns true if successful AND *Account points to account
 bool retrieve(const int &accountNumber, Account *&account) const;
 
//The public version of delete recursion at the root node
 void delete_Tree();

//copy not allowed
BSTree(const BSTree &other) = delete;

//move not allowed
BSTree(BSTree &&other)=delete;

//assingment not allowed
BSTree &operator=(const BSTree &other)=delete;

//move assignment not allowed
BSTree &operator=(BSTree &&other)=delete;

//display information on all accounts
void display() const;

//check if BSTree root is empty
bool isEmpty(Node* root) const;

private:
 
Node *root;
//recursively display account information in BSTree
void recDisplay(Node *root) const;

//recursively insert an account into BStree
bool recInsert(Node *&root, Account* account);

//clear tree
void deleteTree(Node *root);
 };
#endif // BSTREE_H
