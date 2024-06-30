/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// Write your code below this line

SymbolTable::SymbolTable()
{
  size = 0;
  root = NULL;
}

// helper functions for remove and delete
int getHeight(SymNode *node)
{
  if (node != NULL)
  {
    return node->height;
  }
  return -1;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

SymNode *getSuccessor(SymNode *node)
{
  SymNode *successor = node->right;
  while (successor->left != NULL)
  {
    successor = successor->left;
  }
  return successor;
}

int getBalance(SymNode *node)
{
  if (node == NULL)
  {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

SymNode *getPredecessor(SymNode *node)
{
  if (node->left == NULL)
  {
    return NULL;
  }
  node = node->left;
  while (node->right != NULL)
  {
    node = node->right;
  }
  return node;
}

SymNode *rightrotate(SymNode *root)
{
  SymNode *grandpa = root->par;
  SymNode *firstChild = root->left;
  SymNode *grandChild = firstChild->right;
  firstChild->right = root;
  firstChild->par = root->par;
  root->left = grandChild;
  root->par = firstChild;
  if (grandChild != NULL)
  {
    grandChild->par = root;
  }
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  firstChild->height = 1 + max(getHeight(firstChild->left), getHeight(firstChild->right));
  if (grandpa != NULL)
  {
    if (grandpa->left == root)
    {
      grandpa->left = firstChild;
    }
    else
    {
      grandpa->right = firstChild;
    }
  }
  return firstChild;
}

SymNode *leftrotate(SymNode *root)
{
  SymNode *grandpa = root->par;
  SymNode *firstChild = root->right;
  SymNode *grandChild = firstChild->left;
  firstChild->left = root;
  firstChild->par = root->par;
  root->right = grandChild;
  root->par = firstChild;
  if (grandChild != NULL)
  {
    grandChild->par = root;
  }
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  firstChild->height = 1 + max(getHeight(firstChild->left), getHeight(firstChild->right));
  // root = firstChild;
  if (grandpa != NULL)
  {
    if (grandpa->left == root)
    {
      grandpa->left = firstChild;
    }
    else
    {
      grandpa->right = firstChild;
    }
  }
  return firstChild;
}

void SymbolTable::insert(string k)
{
  SymNode *created = new SymNode(k);
  size += 1;
  if (root == NULL)
  {
    root = created;
    return;
  }
  SymNode *temp = root;
  while (temp != NULL)
  {
    if (k < temp->key)
    {
      if (temp->left == NULL)
      {
        temp->left = created;
        created->par = temp;
        break;
      }
      temp = temp->left;
    }
    else
    {
      if (temp->right == NULL)
      {
        temp->right = created;
        created->par = temp;
        break;
      }
      temp = temp->right;
    }
  }
  while (temp != NULL)
  {
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));
    temp = temp->par;
  }
  int balanceFactor;
  SymNode *iterator = created;
  while (iterator != NULL)
  {
    balanceFactor = getHeight(iterator->left) - getHeight(iterator->right);
    if (balanceFactor > 1 || balanceFactor < -1)
    {
      if (balanceFactor > 1)
      {
        if (getHeight(iterator->left->left) > getHeight(iterator->left->right))
        {
          iterator = rightrotate(iterator);
        }
        else
        {
          iterator->left = leftrotate(iterator->left);
          iterator = rightrotate(iterator);
        }
      }
      else
      {
        if (getHeight(iterator->right->right) > getHeight(iterator->right->left))
        {
          iterator = leftrotate(iterator);
        }
        else
        {
          iterator->right = rightrotate(iterator->right);
          iterator = leftrotate(iterator);
        }
      }
      break;
    }
    iterator = iterator->par;
  }
  // root = iterator;
  while (iterator != NULL)
  {
    iterator->height = 1 + max(getHeight(iterator->left), getHeight(iterator->right));
    iterator = iterator->par;
  }

  while (root->par != NULL)
  {
    root = root->par;
  }

  return;
}

void SymbolTable::remove(string k)
{
  if (search(k) == -2)
  { // key exists, so size is decremented. otherwise, nothing to do
    return;
  }
  size -= 1;
  SymNode *sacrifice;
  SymNode *node = root;
  while (node != NULL)
  {
    if (node->key == k)
    {
      sacrifice = node;
      break;
    }
    else
    {
      k > node->key ? node = node->right : node = node->left;
    }
  }
  // leaf node case
  if (sacrifice->left == NULL && sacrifice->right == NULL)
  {
    if (sacrifice->par == NULL)
    {
      delete sacrifice;
      sacrifice = NULL;
      return;
    }
    else
    {
      node = sacrifice->par;
    }
    node->left == sacrifice ? node->left = NULL : node->right = NULL;
    while (node != NULL)
    {
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
      node = node->par;
    }
    node = sacrifice->par;
  }
  else if (sacrifice->left == NULL)
  {
    SymNode *successor = getSuccessor(sacrifice);
    sacrifice->key = successor->key;
    sacrifice->address = successor->address;
    SymNode *succparent = successor->par;
    succparent->left == successor ? succparent->left = NULL : succparent->right = NULL;
    node = succparent;
    while (node != NULL)
    {
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
      node = node->par;
    }
    node = succparent;
    delete successor;
    successor = NULL;
  }
  else if (sacrifice->right == NULL)
  {
    SymNode *predecessor = getPredecessor(sacrifice);
    sacrifice->key = predecessor->key;
    sacrifice->address = predecessor->address;
    SymNode *predParent = predecessor->par;
    predParent->left == predecessor ? predParent->left = NULL : predParent->right = NULL;
    node = predParent;
    while (node != NULL)
    {
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
      node = node->par;
    }
    node = predParent;
    delete predecessor;
    predecessor = NULL;
  }
  else
  {
    SymNode *successor = getSuccessor(sacrifice);
    sacrifice->key = successor->key;
    sacrifice->address = successor->address;
    SymNode *succparent = successor->par;
    succparent->left == successor ? succparent->left = NULL : succparent->right = NULL;
    node = succparent;
    while (node != NULL)
    {
      node->height = 1 + max(getHeight(node->left), getHeight(node->right));
      node = node->par;
    }
    node = succparent;
    delete successor;
    successor = NULL;
  }
  while (node->par != NULL)
  {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    if (getBalance(node) > 1)
    {
      if (getHeight(node->left->left) > getHeight(node->left->right))
      {
        node = rightrotate(node);
      }
      else
      {
        node->left = leftrotate(node->right);
        node = rightrotate(node);
      }
    }
    if (getBalance(node) < -1)
    {
      if (getHeight(node->right->right) > getHeight(node->right->left))
      {
        node = leftrotate(node);
      }
      else
      {
        node->right = rightrotate(node->right);
        node = leftrotate(node);
      }
    }
    node = node->par;
  }
}

int SymbolTable::search(string k)
{
  SymNode *iterator = root;
  while (iterator)
  {
    if (iterator->key == k)
    {
      return iterator->address;
    }
    else if (iterator->key > k)
    {
      iterator = iterator->left;
    }
    else
    {
      iterator = iterator->right;
    }
  }
  return -2;
}

void SymbolTable::assign_address(string k, int idx)
{
  SymNode *iterator = root;
  while (iterator)
  {
    if (iterator->key == k)
    {
      iterator->address = idx;
      return;
    }
    else if (iterator->key > k)
    {
      iterator = iterator->left;
    }
    else
    {
      iterator = iterator->right;
    }
  }
  return;
}

int SymbolTable::get_size()
{
  // inorder(root);
  return size;
}

SymNode *SymbolTable::get_root()
{
  return root;
}

// tree destructor helper function

void deleter(SymNode *node)
{
  if (node->left != NULL)
  {
    deleter(node->left);
  }
  if (node->right != NULL)
  {
    deleter(node->right);
  }
  delete node;
  node = NULL;
}

SymbolTable::~SymbolTable()
{
  deleter(root);
  root = NULL;
}
