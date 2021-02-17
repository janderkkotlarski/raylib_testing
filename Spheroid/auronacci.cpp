#include "auronacci.h"

auronacci::auronacci()
{

}


void auronacci::cycle()
{
 const int temp
 { (m_numbers[0] + m_numbers[1]) % m_max };

 m_numbers[1] = m_numbers[0];

 m_numbers[0] = temp;
}
