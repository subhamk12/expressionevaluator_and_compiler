
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
  if (t == "+")
  {
    type = "ADD";
  }
  else if (t == "-")
  {
    type = "SUB";
  }
  else if (t == "*")
  {
    type = "MUL";
  }
  else if (t == "/")
  {
    type = "DIV";
  }
  else if (isdigit(t[0]))
  {
    type = "VAL";
    num = stoi(t);
  }
  else if (t == "del")
  {
    type = "DEL";
  }
  else if (t == "ret")
  {
    type = "RET";
  }
  else if (t == ":=")
  {
    type = "EQL";
  }
  else
  {
    type = "VAR";
    id = t;
  }
}

ExprTreeNode::~ExprTreeNode()
{
  delete left;
  delete right;
}