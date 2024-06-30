
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// Write your code below this line
#include <iostream>
EPPCompiler::EPPCompiler()
{
  memory_size = 0;
  output_file = "";
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
  memory_size = mem_limit;
  output_file = out_file;
  // for (int i = mem_limit - 1; i >= 0; i--)
  // {
  //   mem_loc.push_back(i);
  // }
  for (int i = 0; i < mem_limit; i++)
  {
    least_mem_loc.push_heap(i);
  }
}

// first calculates the required size of the memory allocated by checking the lhs' of all commmands
// the maximum

void EPPCompiler::compile(vector<vector<string>> code)
{
  for (int i = 0; i < code.size(); i++)
  {
    targ.parse(code[i]);
    write_to_file(generate_targ_commands());
  }
}

// returns the targ code as a vector string of code lines

void targer(ExprTreeNode *root, vector<string> &output, SymbolTable *sym)
{
  if (root == NULL)
  {
    return;
  }

  if (root->type == "VAR")
  {
    output.push_back("PUSH mem[" + to_string(sym->search(root->id)) + "]");
  }
  else if (root->type == "VAL")
  {
    output.push_back("PUSH " + to_string(root->num));
  }
  else if (root->type == "ADD")
  {
    targer(root->right, output, sym);
    targer(root->left, output, sym);
    output.push_back("ADD");
  }
  else if (root->type == "SUB")
  {
    targer(root->right, output, sym);
    targer(root->left, output, sym);
    output.push_back("SUB");
  }
  else if (root->type == "MUL")
  {
    targer(root->right, output, sym);
    targer(root->left, output, sym);
    output.push_back("MUL");
  }
  else if (root->type == "DIV")
  {
    targer(root->right, output, sym);
    targer(root->left, output, sym);
    output.push_back("DIV");
  }
}

vector<string> EPPCompiler::generate_targ_commands()
{
  ExprTreeNode *root = targ.expr_trees.back(), *lhs = root->left, *rhs = root->right;
  vector<string> output = {};
  if (lhs->type == "DEL")
  {
    int add = targ.symtable->search(rhs->id);
    output.push_back("DEL = mem[" + to_string(add) + "]");
    targ.symtable->remove(rhs->id);
    // mem_loc.push_back(add);
    least_mem_loc.push_heap(add);
    return output;
  }
  targer(rhs, output, targ.symtable);
  if (lhs->type == "RET")
  {
    output.push_back("RET = POP");
  }
  else
  {
    int n = targ.symtable->search(lhs->id);
    if (n == -1)
    {
      // int newadd = mem_loc[mem_loc.size() - 1];
      // mem_loc.pop_back();
      int heapmin = least_mem_loc.get_min();
      least_mem_loc.pop();

      targ.symtable->assign_address(lhs->id, heapmin);
      output.push_back("mem[" + to_string(heapmin) + "] = POP");
    }
    else
    { // reassignment
      output.push_back("mem[" + to_string(n) + "] = POP");
    }
  }
  return output;
}

// recursive helper function

void EPPCompiler::write_to_file(vector<string> commands)
{
  ofstream destination(output_file, ios::app);
  if (destination.is_open())
  {
    for (string x : commands)
    {
      destination << x << "\n";
    }
    destination.close();
  }
}

EPPCompiler::~EPPCompiler()
{
}