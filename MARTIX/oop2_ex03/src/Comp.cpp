#include "Comp.h"

#include <iostream>


int Comp::inputCount() const
{
    return first()->inputCount() + second()->inputCount() - 1;
}


Operation::T Comp::compute(const std::vector<T>& input) const
{
    const auto resultOfFirst = first()->compute(input);
    auto firstCount = first()->inputCount();

    std::vector<T> input2(input.begin() + firstCount, input.end());
    input2.insert(input2.begin(), resultOfFirst);

    const auto result = second()->compute(input2);

   
    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (result(i, j) < MIN_ALLOWED_VALUE || result(i, j) > MAX_ALLOWED_VALUE)
            {
                throw MatrixValueOutOfRange();
            }
        }
    }

    return result;
}



void Comp::printSymbol(std::ostream& ostr) const
{
    ostr << " -> ";
}
