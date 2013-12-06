#ifndef PRIME_UTILS_H
#define PRIME_UTILS_H

#include <cstdlib>
bool is_prime(std::size_t x)
{
    std::size_t o = 4;
    for (std::size_t i = 5; true; i += o)
    {
        std::size_t q = x / i;
        if (q < i)
            return true;
        if (x == q * i)
            return false;
        o ^= 6;
    }
    return true;
}

std::size_t next_prime(std::size_t x)
{
    switch (x)
    {
    case 0:
    case 1:
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
    case 5:
        return 5;
    }
    std::size_t k = x / 6;
    std::size_t i = x - 6 * k;
    std::size_t o = i < 2 ? 1 : 5;
    x = 6 * k + o;
    for (i = (3 + o) / 2; !is_prime(x); x += i)
        i ^= 6;
    return x;
}
#endif
