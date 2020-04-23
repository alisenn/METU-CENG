#include <iostream>

#include "Polynomial.hpp"

int main() {
    Polynomial p1("(1)x^1 + (-1)x^1 + (3)x^2 + (-3)x^2 + (4)x^5 + (4)x^5");

    p1.simplifyByExponents();

    p1.printPolynomial();

    return 0;
}
