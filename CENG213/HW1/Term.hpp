#ifndef TERM_HPP
#define TERM_HPP

#include <ostream>

// DO NOT CHANGE THIS FILE.

class Term {
public:
    Term();
    Term(int coefficient, int exponent);
    Term(const Term &obj);

    int getCoefficient() const;
    void setCoefficient(int coefficient);
    int getExponent() const;
    void setExponent(int exponent);

    friend std::ostream &operator<<(std::ostream &os, const Term &obj);

    bool operator==(const Term &rhs);

private:
    int coefficient;
    int exponent;
};

#endif //TERM_HPP
