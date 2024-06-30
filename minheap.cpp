/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
#include <iostream>
// Write your code below this line
int getsize(HeapNode *root)
{
  if (root == NULL)
  {
    return 0;
  }

  int size1 = getsize(root->left);
  int size2 = getsize(root->right);

  return size1 + size2 + 1;
}

bool isbst(HeapNode *root)
{
  if (root == NULL)
  {
    return true;
  }

  int sizeleft = getsize(root->left);
  int sizeright = getsize(root->right);

  if (sizeleft == sizeright)
  {
    return true;
  }

  return false;
}

MinHeap::MinHeap()
{
}

HeapNode *getlast(HeapNode *root, bool &lor)
{
  /*
  if (root == NULL)
  {
      return NULL;
  }

  if (root->left == NULL and root->right == NULL)
  {
      if (root->par == NULL)
      {
          lor = false;
          return root;
      }

      else if (root->par->left == root)
      {
          return getlast(root->par->right, lor);
      }

      else if (root->par->right)
      {
          // HeapNode* temp = root->par;
          // while (temp->par != NULL)
          // {
          //     temp = temp->par;
          // }

          // while (temp->left != NULL)
          // {
          //     temp = temp->left;
          // }


          // lor = false;
          // return temp;

          if (root->left = NULL)
          {
              return root->left;
          }

          else{return root->right;}

      }




  }

  if (root->left != NULL and root->right == NULL)
  {
      lor = true;
      return root;
  }

  if (root->left != NULL and root->right != NULL)
  {
      if (root->left->left == NULL or root->left->right == NULL)
      {
          return getlast(root->left,lor);
      }

      if (root->right->left == NULL or root->right->right == NULL)
      {
          return getlast(root->right,lor);
      }
  }

  // HeapNode* temp = root->par;
  //         while (temp->par != NULL)
  //         {
  //             temp = temp->par;
  //         }

  //         while (temp->left != NULL)
  //         {
  //             temp = temp->left;
  //         }


  //         lor = false;
  //         return temp;

*/
  if (isbst(root) == true)
  {
    HeapNode *temp = root;
    // while (temp->par != NULL)
    // {
    //     temp = temp->par;
    // }

    while (temp->left != NULL)
    {
      temp = temp->left;
    }

    lor = false;
    return temp;
  }

  if (isbst(root->left) == true)
  {
    if (root->right == NULL)
    {
      lor = true;
      return root;
    }

    return getlast(root->right, lor);
  }

  if (isbst(root->left) == false)
  {
    return getlast(root->left, lor);
  }
}

// bool k = true;
// HeapNode* last = getlast(root,k);

HeapNode *getlastla(HeapNode *root)
{
  if (root == NULL)
  {
    return NULL;
  }

  // int sizeleft = getsize(root->left);
  // int sizeright = getsize(root->right);

  if (isbst(root) == true)
  {
    HeapNode *aux = root;
    while (aux->right != NULL)
    {
      aux = aux->right;
    }

    return aux;
  }

  // return getlastla(root->left);
  else if (isbst(root->left) == true and isbst(root->right) == true)
  {
    return getlastla(root->left);
  }

  else if (isbst(root->left) == true and isbst(root->right) == false)
  {
    return getlastla(root->right);
  }

  else if (isbst(root->left) == false)
  {
    return getlastla(root->left);
  }

  // else
  // {
  //     return root->left;
  // }

  // else
  // {return getlastla(root->left);}
}

void HeapifyUP(HeapNode *todo)
{
  if (todo->par != NULL)
  {
    if (todo->par->val > todo->val)
    {
      swap(todo->par->val, todo->val);
      HeapifyUP(todo->par);
    }
  }
}

void HeapifyDown(HeapNode *root)
{
  if (root == NULL or root->left == NULL)
  {
    return;
  }

  HeapNode *min = root->left;
  if (root->right != NULL and min->val > root->right->val)
  {
    min = root->right;
  }

  if (min->val < root->val)
  {
    swap(root->val, min->val);
    HeapifyDown(min);
  }
}

void MinHeap::push_heap(int num)
{
  bool z;

  if (size == 0)
  {
    HeapNode *newnode = new HeapNode(num);
    root = newnode;
    size++;
    // last = root;
    return;
  }
  HeapNode *last = getlast(root, z);

  if (z == false)
  {
    HeapNode *newnode = new HeapNode(num);
    last->left = newnode;
    last->left->par = last;
    HeapifyUP(last->left);
  }

  else
  {
    HeapNode *newnode = new HeapNode(num);
    last->right = newnode;
    last->right->par = last;
    HeapifyUP(last->right);
  }

  size++;
}

int MinHeap::get_min()
{
  return root->val;
}

void MinHeap::pop()
{
  HeapNode *last = getlastla(root);
  if (root == NULL)
  {
    return;
  }

  if (last == root)
  {
    delete root;
    root = NULL;
    last = NULL;
  }

  else
  {
    /*if (last->right != NULL)
    {
        swap(last->right->val,root->val);
        HeapNode* delex = last->right;

        (delex->par->right = delex)?(delex->par->right = NULL):(delex->par->left = NULL);
        delex->par = NULL;
        delete delex;
        HeapifyDown(root);
    }

    else if (last->left != NULL)
    {
        swap(last->left->val,root->val);
        HeapNode* delex = last->left;

        (delex->par->right = delex)?(delex->par->right = NULL):(delex->par->left = NULL);
        delex->par = NULL;
        delete delex;
        HeapifyDown(root);
    }
    else{


    last = lastlast;
    pop();
    size++;
    }*/

    swap(last->val, root->val);
    HeapNode *delex = last;

    (delex->par->right == delex) ? (delex->par->right = NULL) : (delex->par->left = NULL);
    delex->par = NULL;
    // free(delex);
    last->left = NULL;
    last->right = NULL;
    last->par = NULL;
    last = NULL;
    HeapifyDown(root);
  }
  size--;
}

MinHeap::~MinHeap()
{
}

// int main()
// {
//   MinHeap a;
//   for (int i = 0; i < 9; i++)
//   {
//     a.push_heap(i);
//   }

//   // a.pop();
//   a.pop();
//   a.pop();

//   cout << a.get_min();
// }