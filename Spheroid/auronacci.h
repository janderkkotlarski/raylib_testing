#ifndef AURONACCI_H
#define AURONACCI_H

#include <chrono>

class auronacci
{
private:
  const int m_max
  { 1000000000 };

  const int m_start
  { int(std::chrono::system_clock::now().time_since_epoch().count()) % m_max };

  int m_first
  { m_start };

  int m_second
  { m_start / 2 };

public:
  auronacci();

  void cycle();

  void cycle(const int max);

  int get_number();
};

#endif // AURONACCI_H
