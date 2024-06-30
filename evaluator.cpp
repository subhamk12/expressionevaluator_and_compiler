/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
#include <iostream>
Evaluator::Evaluator()
{
  expr_trees = vector<ExprTreeNode *>();
  symtable = new SymbolTable();
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

ExprTreeNode *build_tree(vector<string> code, int initial, int final)
{
  UnlimitedInt zero("0");
  int k = indexsign(code, initial, final);

  if (k == -1)
  {
    ExprTreeNode *root = new ExprTreeNode(code[initial], &zero);
    return root;
  }
  else
  {
    ExprTreeNode *root = new ExprTreeNode(code[k], &zero);
    root->left = build_tree(code, initial + 1, k - 1);
    root->right = build_tree(code, k + 1, final - 1);
    return root;
  }
}

void Evaluator::parse(vector<string> code)
{
  UnlimitedInt zero(0);
  ExprTreeNode *root = new ExprTreeNode(":=", &zero);
  ExprTreeNode *var = new ExprTreeNode(code[0], &zero);
  root->left = var;
  root->right = build_tree(code, 2, code.size() - 1);
  expr_trees.push_back(root);
}

UnlimitedRational *solver(ExprTreeNode *exprtree, SymbolTable *symtable)
{
  if (exprtree->type == "VAL")
  {
    return exprtree->evaluated_value;
  }
  else if (exprtree->type == "VAR")
  {
    UnlimitedRational *a = symtable->search(exprtree->id);
    exprtree->evaluated_value = a;
    return a;
  }
  if (exprtree->type == "ADD")
  {
    UnlimitedRational *a = UnlimitedRational::add(solver(exprtree->left, symtable), solver(exprtree->right, symtable));
    exprtree->evaluated_value = a;
    return a;
  }
  else if (exprtree->type == "MUL")
  {
    UnlimitedRational *a = UnlimitedRational::mul(solver(exprtree->left, symtable), solver(exprtree->right, symtable));
    exprtree->evaluated_value = a;
    return a;
  }
  else if (exprtree->type == "SUB")
  {
    UnlimitedRational *a = UnlimitedRational::sub(solver(exprtree->left, symtable), solver(exprtree->right, symtable));
    exprtree->evaluated_value = a;
    return a;
  }
  else if (exprtree->type == "DIV")
  {
    UnlimitedRational *a = UnlimitedRational::div(solver(exprtree->left, symtable), solver(exprtree->right, symtable));
    exprtree->evaluated_value = a;
    return a;
  }
  else
  {
    return nullptr;
  }
}

void Evaluator::eval()
{
  ExprTreeNode *root = expr_trees[expr_trees.size() - 1];
  string varname = root->left->id;
  UnlimitedRational *varval = solver(root->right, symtable);
  symtable->insert(varname, varval);
}

Evaluator::~Evaluator()
{
  symtable->~SymbolTable();
}
