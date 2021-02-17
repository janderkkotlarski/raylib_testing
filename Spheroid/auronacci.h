#ifndef AURONACCI_H
#define AURONACCI_H

#include <vector>
#include <chrono>

class auronacci
{
private:
  const int m_max
  { 1000000000 };

  const int m_start
  { int(std::chrono::system_clock::now().time_since_epoch().count()) % m_max };

  std::vector <int> m_numbers
  { m_start, m_start / 2 };

public:
  auronacci();

  void cycle();
};

#endif // AURONACCI_H
