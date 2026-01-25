#include <iostream>
#include <vector>
#include <stdexcept>

class Expression {
public:
    virtual ~Expression() {}
    virtual int eval() const = 0;
    virtual void print() const = 0;
};

class Constant : public Expression {
    int val;
public:
    Constant(int v) : val(v) {}
    int eval() const { return val; }
    void print() const { std::cout << val; }
};

class UnaryMinus : public Expression {
    const Expression& e;
public:
    UnaryMinus(const Expression& expr) : e(expr) {}
    int eval() const { return -e.eval(); }
    void print() const { e.print(); std::cout << " -"; }
};

class Plus : public Expression {
    const Expression &g, &d;
public:
    Plus(const Expression& gauche, const Expression& droite) : g(gauche), d(droite) {}
    int eval() const { return g.eval() + d.eval(); }
    void print() const { g.print(); std::cout << " "; d.print(); std::cout << " +"; }
};

class Minus : public Expression {
    const Expression &g, &d;
public:
    Minus(const Expression& gauche, const Expression& droite) : g(gauche), d(droite) {}
    int eval() const { return g.eval() - d.eval(); }
    void print() const { g.print(); std::cout << " "; d.print(); std::cout << " -"; }
};

class Divide : public Expression {
    const Expression &g, &d;
public:
    Divide(const Expression& gauche, const Expression& droite) : g(gauche), d(droite) {}
    int eval() const {
        int div = d.eval();
        if (div == 0) throw std::runtime_error("zero divide error");
        return g.eval() / div;
    }
    void print() const { g.print(); std::cout << " "; d.print(); std::cout << " /"; }
};

int main()
{
    try
    {
        Constant c1(12), c2(87), c3(75);

        c1.print();
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl;

        UnaryMinus u1(c1);
        u1.print();
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl;

        Plus p1(c2, u1);
        p1.print();
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl;

        Minus m1(p1, c3);
        m1.print();
        std::cout << std::endl;
        std::cout << "eval " << m1.eval() << std::endl;

        std::vector<Expression*> expr;
        expr.push_back(&c1);
        expr.push_back(&u1);
        expr.push_back(&p1);
        expr.push_back(&m1);

        std::cout << std::endl;
        for (size_t i = 0; i < expr.size(); ++i) {
            expr[i]->print();
            std::cout << " = " << expr[i]->eval() << std::endl;
        }

        Divide d1(p1, m1);
        std::cout << std::endl;
        std::cout << d1.eval() << std::endl;
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}