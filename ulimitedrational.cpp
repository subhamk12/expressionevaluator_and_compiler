/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include <iostream>

UnlimitedInt *hcf(UnlimitedInt *i1, UnlimitedInt *i2)
{
  if (UnlimitedInt::sub(i1, i2)->get_sign() >= 0)
  {
    if (i2->get_sign() == 0)
    {
      return i1;
    }
    return hcf(i2, UnlimitedInt::mod(i1, i2));
  }
  else
  {
    if (i2->get_sign() == 0)
    {
      return i1;
    }
    return hcf(i1, UnlimitedInt::mod(i2, i1));
  }
}

UnlimitedRational::UnlimitedRational()
{
  p = new UnlimitedInt("0"), q = new UnlimitedInt("0");
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
  if (den->get_sign() == 0)
  {
    p = new UnlimitedInt("0");
    q = new UnlimitedInt("0");
    return;
  }
  if (num->get_sign() == 0)
  {
    p = new UnlimitedInt("0");
    q = new UnlimitedInt("1");
    return;
  }
  if (num->get_sign() == -1 && den->get_sign() == -1)
  {
    UnlimitedInt *newnum = new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size());
    UnlimitedInt *newden = new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size());
    UnlimitedInt *commonfactor = hcf(newnum, newden);
    p = UnlimitedInt::div(newnum, commonfactor);
    q = UnlimitedInt::div(newden, commonfactor);
  }
  else if (num->get_sign() == -1)
  {
    UnlimitedInt *newnum = new UnlimitedInt(num->get_array(), num->get_capacity(), 1, num->get_size());
    UnlimitedInt *commonfactor = hcf(newnum, den);
    p = UnlimitedInt::div(num, commonfactor);
    q = UnlimitedInt::div(den, commonfactor);
  }
  else if (den->get_sign() == -1)
  {
    UnlimitedInt *newden = new UnlimitedInt(den->get_array(), den->get_capacity(), 1, den->get_size());
    UnlimitedInt *commonfactor = hcf(num, newden);
    UnlimitedInt *numf = UnlimitedInt::div(num, commonfactor);
    p = new UnlimitedInt(numf->get_array(), numf->get_capacity(), -1, numf->get_size());
    q = UnlimitedInt::div(newden, commonfactor);
  }
  else
  {
    UnlimitedInt *commonfactor = hcf(num, den);
    // std::cout << num->to_string() << endl;
    // std::cout << den->to_string() << endl;
    // std::cout << "pos hcf is " << commonfactor->to_string() << endl;
    p = UnlimitedInt::div(num, commonfactor);
    // std::cout << p->to_string() << endl;
    q = UnlimitedInt::div(den, commonfactor);
    // std::cout << q->to_string() << endl;
  }
}

UnlimitedRational::~UnlimitedRational()
{
  delete p;
  delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
  return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
  return q;
}

string UnlimitedRational::get_p_str()
{
  return p->to_string();
}

string UnlimitedRational::get_q_str()
{
  return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
  return p->to_string() + "/" + q->to_string();
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
  UnlimitedInt *x1 = UnlimitedInt::mul(i1->get_p(), i2->get_q()), *x2 = UnlimitedInt::mul(i2->get_p(), i1->get_q());
  UnlimitedInt *num = UnlimitedInt::add(x1, x2), *den = UnlimitedInt::mul(i1->get_q(), i2->get_q());
  delete x1;
  delete x2;
  UnlimitedRational *res = new UnlimitedRational(num, den);
  return res;
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
  UnlimitedInt *x1 = UnlimitedInt::mul(i1->get_p(), i2->get_q()), *x2 = UnlimitedInt::mul(i2->get_p(), i1->get_q());
  UnlimitedInt *num = UnlimitedInt::sub(x1, x2), *den = UnlimitedInt::mul(i1->get_q(), i2->get_q());
  delete x1;
  delete x2;
  UnlimitedRational *res = new UnlimitedRational(num, den);
  return res;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
  UnlimitedInt *num = UnlimitedInt::mul(i1->p, i2->p), *den = UnlimitedInt::mul(i1->q, i2->q);
  UnlimitedRational *res = new UnlimitedRational(num, den);
  return res;
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
  UnlimitedRational *divisor = new UnlimitedRational(i2->q, i2->p);
  UnlimitedRational *res = UnlimitedRational::mul(i1, divisor);
  delete divisor;
  return res;
}

// int main()
// {
//   UnlimitedInt a("665");
//   UnlimitedInt b("51");
//   // std::cout << hcf(&a, &b)->to_string() << endl;
//   UnlimitedRational *f = new UnlimitedRational(&a, &b);
//   // std::cout << a.to_string() << endl;
//   std::cout << f->get_frac_str() << endl;
//   // UnlimitedInt c("2");
//   // UnlimitedInt d("51");
//   // UnlimitedRational *s = new UnlimitedRational(&c, &d);
//   // std::cout << s->get_frac_str() << endl;
//   // UnlimitedRational *sum = UnlimitedRational::add(f, s);
//   // std::cout << sum->get_frac_str() << endl;

//   // std::cout << UnlimitedInt::add(&a, &b)->to_string() << endl;
// }