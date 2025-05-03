#include "Scalar.h"

#include <iostream>


Scalar::Scalar(int scalar)
 : m_scalar(scalar)
{
}


Operation::T Scalar::compute(const std::vector<T>& input) const
{
    Operation::T result = input.front() * m_scalar;

    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (result(i, j) < MIN_ALLOWED_VALUE || result(i, j) > MAX_ALLOWED_VALUE) {
                throw MatrixValueOutOfRange();
            }
        }
    }

    return result;
}


void Scalar::print(std::ostream& ostr, bool first_print) const
{
    (void)first_print; // Cast to void to avoid unused parameter warning
    ostr << "scal " << m_scalar;
}
