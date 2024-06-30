/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

// Write your code below this line

Parser::Parser()
{
  symtable = new SymbolTable();
  expr_trees = vector<ExprTreeNode *>();
}

int indexsign(vector<string> code, int start, int end)
{
  int i = start, opencount = 0;
  while (code[i] == "(")
  {
    i += 1;
    opencount += 1;
  }
  int index = i;
  if (opencount != 0)
  {
    for (int idx = i; idx < end - 1; idx++)
    {
      if (opencount == 1)
      {
        break;
      }
      else if (code[idx] == ")")
      {
        opencount--;
      }
      index++;
    }
  }
  for (int idx = index; idx < end; idx++)
  {
    if (code[idx] == "+" or code[idx] == "-" or code[idx] == "*" or code[idx] == "/")
    {
      return idx;
    }
  }
  return -1;
}

ExprTreeNode *buildTree(vector<string> code, int initial, int final)
{
  int k = indexsign(code, initial, final);

  if (k == -1)
  {
    ExprTreeNode *root = new ExprTreeNode(code[initial], 0);
    return root;
  }
  else
  {
    ExprTreeNode *root = new ExprTreeNode(code[k], 0);
    root->left = buildTree(code, initial + 1, k - 1);
    root->right = buildTree(code, k + 1, final - 1);
    return root;
  }
}

void Parser::parse(vector<string> expression)
{
  ExprTreeNode *root = new ExprTreeNode(expression[1], -1);
  ExprTreeNode *lefthand = new ExprTreeNode(expression[0], -2);
  if (lefthand->type == "VAR")
  {
    if (symtable->search(expression[0]) == -2)
    {
      symtable->insert(expression[0]);
    }
  }
  root->left = lefthand;
  root->right = buildTree(expression, 2, expression.size());
  expr_trees.push_back(root);
}

Parser::~Parser()
{
}