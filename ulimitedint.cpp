/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

#include "ulimitedint.h"
#include <iostream>

UnlimitedInt::UnlimitedInt()
{
  size = 0;
  sign = 0;
  capacity = 0;
  unlimited_int = nullptr;
  return;
}

UnlimitedInt::UnlimitedInt(string s)
{
  if (s[0] == '-')
  {
    if (s[1] == 0)
    {
      sign = 0;
      size = 1;
      capacity = 1;
      unlimited_int = new int[capacity];
      unlimited_int[0] = 0;
      return;
    }
    sign = -1;
    size = s.length() - 1;
    capacity = s.length() - 1;
    unlimited_int = new int[capacity];
    int strpos = capacity;
    int arrpos = 0;
    while (arrpos < capacity)
    {
      unlimited_int[arrpos] = int(s[strpos] - '0');
      arrpos += 1;
      strpos -= 1;
    }
  }
  else if (s[0] == '0')
  {
    sign = 0;
    size = 1;
    capacity = 1;
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
    return;
  }
  else
  {
    sign = 1;
    size = s.length();
    capacity = s.length();
    unlimited_int = new int[capacity];
    int strpos = capacity - 1;
    int arrpos = 0;
    while (arrpos < capacity)
    {
      unlimited_int[arrpos] = int(s[strpos] - '0');
      arrpos += 1;
      strpos -= 1;
    }
  }
}

UnlimitedInt::UnlimitedInt(int i)
{
  string s = std::to_string(i);
  if (s[0] == '-')
  {
    if (s[1] == 0)
    {
      sign = 0;
      size = 1;
      capacity = 1;
      unlimited_int = new int[capacity];
      unlimited_int[0] = 0;
      return;
    }
    sign = -1;
    size = s.length() - 1;
    capacity = s.length() - 1;
    unlimited_int = new int[capacity];
    int strpos = capacity;
    int arrpos = 0;
    while (arrpos < capacity)
    {
      unlimited_int[arrpos] = int(s[strpos] - '0');
      arrpos += 1;
      strpos -= 1;
    }
    return;
  }
  else if (s[0] == '0')
  {
    sign = 0;
    size = 1;
    capacity = 1;
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
    return;
  }
  else
  {
    sign = 1;
    size = s.length();
    capacity = s.length();
    unlimited_int = new int[capacity];
    int strpos = capacity - 1;
    int arrpos = 0;
    while (arrpos < capacity)
    {
      unlimited_int[arrpos] = int(s[strpos] - '0');
      arrpos += 1;
      strpos -= 1;
    }
    return;
  }
}

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
  int *arr = new int[cap];
  for (int x = 0; x < cap; x++)
  {
    arr[x] = ulimited_int[x];
  }
  unlimited_int = arr;
  capacity = cap;
  sign = sgn;
  size = sz;
  return;
}

UnlimitedInt::~UnlimitedInt()
{
  delete[] unlimited_int;
}

int UnlimitedInt::get_size()
{
  return size;
}

int UnlimitedInt::get_sign()
{
  return sign;
}

int UnlimitedInt::get_capacity()
{
  return capacity;
}

int *UnlimitedInt::get_array()
{
  return unlimited_int;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
  // declaring parameters of the answer
  int sgnans, sizans, capans;
  int *arrayans;

  // extracting parameters of the premise
  int sgn1 = i1->get_sign();
  int cap1 = i1->get_capacity();
  int *arr1 = i1->get_array();
  int sgn2 = i2->get_sign();
  int cap2 = i2->get_capacity();
  int *arr2 = i2->get_array();

  int *arrf = new int[cap1];
  int *arrs = new int[cap2];
  for (int x = 0; x < cap1; x++)
  {
    arrf[x] = arr1[x];
  }
  for (int x = 0; x < cap2; x++)
  {
    arrs[x] = arr2[x];
  }

  if (sgn1 * sgn2 == 1)
  { // getting sign of anaswer
    sgnans = sgn1;
    if (cap1 < cap2)
    {
      int *temparr = arrs;
      arrs = arrf;
      arrf = temparr;
      int tempcap = cap2;
      cap2 = cap1;
      cap1 = tempcap;
    }
    int unlimitedSum[cap1 + 1];
    int pos = 0;
    int carry = 0;
    while (pos < cap2)
    {
      int temp = arrf[pos] + arrs[pos] + carry;
      unlimitedSum[pos] = (temp) % 10;
      carry = temp / 10;
      pos += 1;
    }
    while (pos < cap1)
    {
      int temp = arrf[pos] + carry;
      unlimitedSum[pos] = (temp) % 10;
      carry = temp / 10;
      pos += 1;
    }
    unlimitedSum[pos] = carry;

    if (unlimitedSum[cap1] == 0)
    {
      arrayans = new int[cap1];
      int x = 0;
      while (x < cap1)
      {
        arrayans[x] = unlimitedSum[x];
        x += 1;
      }
      capans = cap1;
    }
    else
    {
      arrayans = new int[cap1 + 1];
      int x = 0;
      while (x < cap1 + 1)
      {
        arrayans[x] = unlimitedSum[x];
        x += 1;
      }
      capans = cap1 + 1;
    }
    delete[] arrf;
    delete[] arrs;
  }
  else if (sgn1 * sgn2 == -1)
  {

    // getting sign of bigger element

    if (cap1 > cap2)
    {
      sgnans = sgn1;
    }
    else if (cap1 < cap2)
    {
      sgnans = sgn2;
      int *temparr = arrs;
      arrs = arrf;
      arrf = temparr;
      int tempcap = cap2;
      cap2 = cap1;
      cap1 = tempcap;
    }
    else
    {
      int cap = cap1 - 1;
      while (arrf[cap] == arrs[cap] && cap >= 0)
      {
        cap -= 1;
      }
      if (cap != -1)
      {
        if (arrf[cap] > arrs[cap])
        {
          sgnans = sgn1;
        }
        else
        {
          sgnans = sgn2;
          int *temparr = arrs;
          arrs = arrf;
          arrf = temparr;
          int tempcap = cap2;
          cap2 = cap1;
          cap1 = tempcap;
        }
      }
      else
      {
        sgnans = 0;
      }
    }

    int unlimitedSum[cap1];
    int pos = 0;
    while (pos < cap2)
    {
      if (arrf[pos] < arrs[pos])
      {
        int timpy = pos + 1;
        while (arrf[timpy] == 0)
        {
          arrf[timpy] = 9;
          timpy += 1;
        }
        arrf[timpy] -= 1;
        unlimitedSum[pos] = arrf[pos] + 10 - arrs[pos];
      }
      else
      {
        unlimitedSum[pos] = arrf[pos] - arrs[pos];
      }
      pos += 1;
    }
    while (pos < cap1)
    {
      unlimitedSum[pos] = arrf[pos];
      pos += 1;
    }

    int x = cap1 - 1;
    while (x >= 0 && unlimitedSum[x] == 0)
    {
      x -= 1;
    }
    capans = x + 1;
    arrayans = new int[capans];
    for (int p = 0; p < capans; p++)
    {
      arrayans[p] = unlimitedSum[p];
    }
    delete[] arrf;
    delete[] arrs;
  }
  else
  {
    if (sgn1 == 0)
    {
      sgnans = sgn2;
      capans = cap2;
      arrayans = arrs;
      delete[] arrf;
    }
    else
    {
      sgnans = sgn1;
      capans = cap1;
      arrayans = arrf;
      delete[] arrs;
    }
  }

  UnlimitedInt *sum = new UnlimitedInt(arrayans, capans, sgnans, capans);
  delete[] arrayans;
  return sum;
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
  UnlimitedInt *newi2 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), (-1) * (i2->get_sign()), i2->get_size());
  UnlimitedInt *ans = UnlimitedInt::add(i1, newi2);
  newi2->~UnlimitedInt();
  return ans;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
  int sgnans, capans, sizans;
  int *arrayans;

  int *arr1 = i1->get_array();
  int *arr2 = i2->get_array();
  int sgn1 = i1->get_sign();
  int sgn2 = i2->get_sign();
  int cap1 = i1->get_capacity();
  int cap2 = i2->get_capacity();

  if (sgn1 * sgn2 == 0)
  {
    sgnans = 0;
    capans = 0;
    sizans = 0;
    int array[1];
    array[0] = 0;
    arrayans = array;
    UnlimitedInt *ans = new UnlimitedInt(arrayans, capans, sgnans, sizans);
    return ans;
  }
  else if (sgn1 * sgn2 == 1)
  {
    sgnans = 1;
  }
  else
  {
    sgnans = -1;
  }

  int cap = cap1 + cap2;
  int ansarr[cap1 + cap2] = {0};

  for (int j = 0; j < cap2; j++)
  {
    int tempansarr[cap1 + 1] = {0};
    int carry = 0;
    int temp = 0;
    for (int i = 0; i < cap1; i++)
    {
      temp = arr1[i] * arr2[j] + carry;
      tempansarr[i] = temp % 10;
      carry = temp / 10;
    }
    tempansarr[cap1] = carry;
    carry = 0;
    temp = 0;
    for (int k = j; k < j + cap1 + 1; k++)
    {
      temp = ansarr[k] + tempansarr[k - j] + carry;
      ansarr[k] = temp % 10;
      carry = temp / 10;
    }
    int k = j + cap1 + 1;
    while (carry != 0)
    {
      temp = ansarr[k] + carry;
      ansarr[k] = temp % 10;
      carry = temp / 10;
      k += 1;
    }
  }
  if (ansarr[cap1 + cap2 - 1] == 0)
  {
    int *realansarr = new int[cap1 + cap2 - 1];
    for (int x = 0; x < cap1 + cap2 - 1; x++)
    {
      realansarr[x] = ansarr[x];
    }
    capans = cap1 + cap2 - 1;
    arrayans = realansarr;
  }
  else
  {
    int *realansarr = new int[cap1 + cap2];
    for (int x = 0; x < cap1 + cap2; x++)
    {
      realansarr[x] = ansarr[x];
    }
    capans = cap1 + cap2;
    arrayans = realansarr;
  }

  sizans = capans;
  UnlimitedInt *ans = new UnlimitedInt(arrayans, capans, sgnans, sizans);
  delete[] arrayans;
  return ans;
}

string quotientgetter(UnlimitedInt *i1, UnlimitedInt *i2)
{
  UnlimitedInt first(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
  UnlimitedInt second(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
  if (UnlimitedInt::sub(&first, &second)->get_sign() < 0)
  {
    return "0";
  }
  string remainder = second.to_string();
  int capk = 0;
  for (int i = 0; i < i1->get_size() - i2->get_size() - 1; i++)
  {
    remainder += "0";
  }
  UnlimitedInt secondnew(remainder);
  while (UnlimitedInt::sub(&first, &secondnew)->get_sign() >= 0)
  {
    string subbed = UnlimitedInt::sub(&first, &secondnew)->to_string();
    capk += 1;
    UnlimitedInt *firstnew = new UnlimitedInt(subbed);
    first = *firstnew;
  }

  string remaindernew = std::to_string(capk);
  for (int i = 0; i < i1->get_size() - i2->get_size() - 1; i++)
  {
    remaindernew += "0";
  }

  UnlimitedInt auxfirst(remaindernew);
  UnlimitedInt auxsecond(quotientgetter(&first, &second));
  if (UnlimitedInt::sub(&first, &second)->get_sign() >= 0)
  {
    return UnlimitedInt::add(&auxfirst, &auxsecond)->to_string();
  }
  return remaindernew;
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
  int sgn1 = i1->get_sign();
  int sgn2 = i2->get_sign();
  if (sgn1 == 0)
  {
    UnlimitedInt *q = new UnlimitedInt("0");
    return q;
  }
  UnlimitedInt firstpos(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
  UnlimitedInt secondpos(i2->get_array(), i2->get_capacity(), 1, i2->get_size());

  if (sgn1 * sgn2 == 1)
  {
    string quotientstr = quotientgetter(&firstpos, &secondpos);
    UnlimitedInt *uiquotient = new UnlimitedInt(quotientstr);
    return uiquotient;
  }
  else
  {
    string first = quotientgetter(&firstpos, &secondpos);
    UnlimitedInt *modfirst = UnlimitedInt::mod(&firstpos, &secondpos);
    if (modfirst->get_sign() == 0)
    {
      modfirst->~UnlimitedInt();
      string second = "-" + first;
      UnlimitedInt *uiquotient = new UnlimitedInt(second);
      return uiquotient;
    }
    else
    {
      modfirst->~UnlimitedInt();
      UnlimitedInt cf(first);
      UnlimitedInt cs("1");
      string end = "-" + UnlimitedInt::add(&cf, &cs)->to_string();
      UnlimitedInt *uiquotient = new UnlimitedInt(end);
      return uiquotient;
    }
  }
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
  if (i1->get_sign() == 0 || i2->get_sign() == 0)
  {
    return new UnlimitedInt(0);
  }
  UnlimitedInt first(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
  UnlimitedInt second(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
  UnlimitedInt *quotient = UnlimitedInt::div(&first, &second);
  if (i1->get_sign() * i2->get_sign() == 1)
  {
    return UnlimitedInt::sub(&first, UnlimitedInt::mul(&second, quotient));
  }
  else
  {
    UnlimitedInt *subtractedpos = UnlimitedInt::sub(&first, UnlimitedInt::mul(&second, quotient));
    return UnlimitedInt::sub(&second, subtractedpos);
  }
}

string UnlimitedInt::to_string()
{
  string ansstr = "";
  if (sign == 0)
  {
    ansstr = "0";
    return ansstr;
  }
  if (sign == -1)
  {
    ansstr += "-";
    for (int i = capacity - 1; i >= 0; i--)
    {
      ansstr += std::to_string(unlimited_int[i]);
    }
    return ansstr;
  }
  for (int i = capacity - 1; i >= 0; i--)
  {
    ansstr += std::to_string(unlimited_int[i]);
  }
  return ansstr;
}

// int main()
// {
//   UnlimitedInt a("665");
//   UnlimitedInt b("1");
//   std::cout << UnlimitedInt::div(&a, &b)->to_string() << endl;
// }