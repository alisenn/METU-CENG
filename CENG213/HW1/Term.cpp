#include "Term.hpp"

// DO NOT CHANGE THIS FILE.

Term::Term() {

}

Term::Term(int coefficient, int exponent) {
    this->coefficient = coefficient;
    this->exponent = exponent;
}

Term::Term(const Term &obj) {
    this->coefficient = obj.coefficient;
    this->exponent = obj.exponent;
}

int Term::getCoefficient() const {
    return coefficient;
}

void Term::setCoefficient(int coefficient) {
    this->coefficient = coefficient;
}

int Term::getExponent() const {
    return exponent;
}

void Term::setExponent(int exponent) {
    this->exponent = exponent;
}

std::ostream &operator<<(std::ostream &os, const Term &obj) {
    os << "coefficient: " << obj.coefficient;
    os << " exponent: " << obj.exponent;
    os << " term: (" << obj.coefficient << ")x^" << obj.exponent;
    return os;
}

bool Term::operator==(const Term &rhs) {
    return (this->coefficient == rhs.coefficient) && (this->exponent == rhs.exponent);
}