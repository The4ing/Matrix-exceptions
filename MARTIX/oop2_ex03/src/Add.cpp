#include "Add.h"

#include <iostream>


Operation::T Add::compute(const std::vector<T>& input) const
{
    const auto a = first()->compute(input);
    auto firstCount = first()->inputCount();

    std::vector<T> input2(input.begin() + firstCount, input.end());
    const auto b = second()->compute(input2);

    Operation::T result = a + b;

   
    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (result(i, j) < MIN_ALLOWED_VALUE || result(i, j) > MAX_ALLOWED_VALUE) {
                throw MatrixValueOutOfRange();  // ?? ????? ???????
            }
        }
    }

    return result;
}


void Add::printSymbol(std::ostream& ostr) const
{
    ostr << '+';
}
