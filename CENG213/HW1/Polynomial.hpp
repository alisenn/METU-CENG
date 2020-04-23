#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>
#include <cstdlib>

#include "LinkedList.hpp"
#include "Term.hpp"

// DO NOT CHANGE THIS FILE.

class Polynomial {
public:
    Polynomial();
    Polynomial(std::string expression);

    void simplifyByExponents();
    void printPolynomial();

    Polynomial operator+(const Polynomial &rhs) const;

private:
    LinkedList<Term> terms;
};

#endif //POLYNOMIAL_HPP
