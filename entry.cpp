/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
#include <iostream>

SymEntry::SymEntry()
{
  key = "NULL";
  val = nullptr;
  left = nullptr;
  right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational *v)
{
  key = k;
  val = v;
  left = nullptr;
  right = nullptr;
}

SymEntry::~SymEntry()
{
  val->~UnlimitedRational();
  delete left;
  delete right;
}