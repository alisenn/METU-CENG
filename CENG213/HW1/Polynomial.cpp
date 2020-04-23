#include "Polynomial.hpp"

Polynomial::Polynomial() {
    // Does nothing.
}

Polynomial::Polynomial(std::string expression) {
    // expression = (c_1)x^n_1 + (c_2)x^n_2 + ... + (c_k)x^n_k
    // c's are integer coefficients, n's are non-negative integer exponents.

    std::string delimiter = " + ";

    std::string term;
    std::string coefficient;
    std::string exponent;
    size_t pos = 0;

    while (true) {
        pos = expression.find(delimiter);

        bool breakTheLoop = (pos == std::string::npos);

        term = expression.substr(0, pos);
        expression.erase(0, pos + delimiter.length());

        pos = term.find("x");

        coefficient = term.substr(1, pos - 2);
        exponent = term.substr(pos + 2, term.length() - pos);

        terms.insertAtTheEnd(Term(std::atoi(coefficient.c_str()), std::atoi(exponent.c_str())));

        if (breakTheLoop) break;
    }
}

void Polynomial::printPolynomial() {
    // prints the polynomial in expression format.
    // expression = (c_1)x^n_1 + (c_2)x^n_2 + ... + (c_k)x^n_k

    Node<Term> *node = terms.getFirstNode();

    while (node) {
        std::cout << "(" << node->element.getCoefficient() << ")x^" << node->element.getExponent();
        if (node->next) std::cout << " + ";
        node = node->next;
    }

    std::cout << std::endl;
}

void Polynomial::simplifyByExponents() {

  Node<Term> *node1 = terms.getFirstNode();
  Node<Term> *node2 = terms.getFirstNode();
Node<Term> *temp12 ;
Node<Term> *temp13;
    int girdi=0;
  int sonuc=-1;
  while(node1){
    while (node2) {
        if((node1 != node2) && node1->element.getExponent() == node2->element.getExponent()){
            sonuc = node1->element.getCoefficient() + node2->element.getCoefficient();
            node1->element.setCoefficient(sonuc);
            if(sonuc ==0){
                temp12 = node2->next;
                temp13 = node1->next;
                if(node1->next == node2){
                  temp13 = node2->next;
                }
                terms.removeNode(node1);
                node1=temp13;
                terms.removeNode(node2);
                node2=temp12;
                girdi =1;

            }
            else{
                temp12 = node2->next;
                terms.removeNode(node2);
                node2=temp12;
            }
        }
        else{
            node2 = node2->next;
        }
    }
    if(girdi == 0)node1 = node1->next;
    girdi =0;
    node2 = node1 ;
  }

    /* TODO */
}

Polynomial Polynomial::operator+(const Polynomial &rhs) const {
    Polynomial res;
    Node<Term> *temp = terms.getFirstNode();
    if(temp){
    Node<Term>* r = rhs.terms.getFirstNode();
    while (temp) {
        res.terms.insertAtTheEnd(temp->element);
       temp = temp->next;
    }
    while (r) {
        res.terms.insertAtTheEnd(r->element);
       r = r->next;
    }
  }

  return res;
    /* TODO */
}
