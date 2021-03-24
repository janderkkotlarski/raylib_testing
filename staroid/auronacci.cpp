#include "auronacci.h"

#include <iostream>

auronacci::auronacci()
{ cycle(100); }

void auronacci::cycle()
{
 const int temp
 { (m_first + m_second) % m_max };

 m_second = m_first;

 m_first = abs(temp);
}

void auronacci::cycle(const int max)
{
  for (int count{ 0 }; count < max; ++count)
  { cycle(); }
}

int auronacci::get_number()
{
  cycle();

  return m_first;
}

float auronacci::get_fraction()
{
  cycle(get_number() % 100 + 11);

  const float fraction
  { float(m_first)/float(m_max) };

  return fraction;
}
