
#include "bstree.h"
#include <cassert>
#include <string>

using namespace std;

// create node
Node::Node(Account *acc)
    : accountInNodeClass{acc}, right{nullptr}, left{nullptr} {}

// Create BST
BSTree::BSTree() { root = nullptr; }

// Destructor for tree
BSTree::~BSTree() { delete_Tree(); }

// delete tree
void BSTree::delete_Tree() { deleteTree(root); }

// Insert new account
bool BSTree::insert(Account *account) { return recInsert(root, account); }

// recursively delete all the elements(node) of a tree
void BSTree::deleteTree(Node *root) {
  if (root != nullptr) {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root->accountInNodeClass;
    delete root;
  }
}

// recursively insert new account
bool BSTree::recInsert(Node *&root, Account *account) {
  if (isEmpty(root)) {
    root = new Node(account);
    return true;
  }
  if (root->accountInNodeClass->getID() == account->getID()) {
    return false;
  }

  if (root->accountInNodeClass->getID() > account->getID()) {
    return recInsert(root->left, account);
  }
  return recInsert(root->right, account);
}

// Retrieve account
// returns true if successful AND *Account points to account
bool BSTree::retrieve(const int &accountNumber, Account *&account) const {
  // assert(account!=nullptr);
  Node *curr = root;
  while (curr != nullptr) {
    if (curr->accountInNodeClass->getID() == accountNumber) {
      account = curr->accountInNodeClass;
      return true;
    }
    if (curr->accountInNodeClass->getID() > accountNumber) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  account = nullptr;
  return false;
}

// display information for accounts in BSTree
void BSTree::display() const { recDisplay(root); }

// recursive display information for accounts in Bstree
void BSTree::recDisplay(Node *root) const {
  if (isEmpty(root)) {
    return;
  }
  Node *curr = root;
  assert(curr != nullptr);
  recDisplay(curr->left);
  cout << "Account Name: " << curr->accountInNodeClass->getName()
       << " Id: " << curr->accountInNodeClass->getID() << endl;
  for (int i = 0; i < 10; i++) {
    cout << curr->accountInNodeClass->getFundName(i) << ": "
         << curr->accountInNodeClass->getFund(i) << endl;
  }
  cout << endl;
  recDisplay(curr->right);
}

// check if root is empty
bool BSTree::isEmpty(Node *root) const { return root == nullptr; }
