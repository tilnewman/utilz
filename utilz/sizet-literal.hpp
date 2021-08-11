#ifndef UTILZ_SIZET_LITERAL_HPP_INCLUDED
#define UTILZ_SIZET_LITERAL_HPP_INCLUDED
//
// sizet-literal.hpp
//
#include <cstddef>

constexpr std::size_t operator"" _st(unsigned long long number)
{
    return static_cast<std::size_t>(number);
}

#endif // UTILZ_SIZET_LITERAL_HPP_INCLUDED
