#include "auronacci.h"

auronacci::auronacci()
{ cycle(100); }

void auronacci::cycle()
{
 const int temp
 { (m_first + m_second) % m_max };

 m_second = m_first;

 m_first = temp;
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
