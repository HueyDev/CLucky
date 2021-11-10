#pragma once
#include "lexer.hpp"


class Expr {
public:
  virtual ~Expr() = default;

  virtual Value *codegen() = 0;
};


class Primary : public Expr{
public:
    const char* value;

    Primary(const char* v);

    Value *codegen() override;

    ~Primary() override;
}


class Unary : public Expr{

public:

    const char* op;
    Expr* primary;

    Unary(Expr* l, const char* o, Expr* r);

    Value *codegen() override;

    ~Unary() override;

}


class Factor : public Expr{

public:

    Expr* left;
    const char* op;
    Expr* right;

    Factor(Expr* l, const char* o, Expr* r);

    Value *codegen() override;

    ~Factor() override;

}


class Term : public Expr{

public:

    Expr* left;
    const char* op;
    Expr* right;

    Term(Expr* l, const char* o, Expr* r);

    Value *codegen() override;

    ~Term() override;

}


class Comparison : public Expr{

public:

    Expr* left;
    const char* op;
    Expr* right;

    Comparison(Expr* l, const char* o, Expr* r);

    Value *codegen() override;

    ~Comparison() override;

}


class Equality : public Expr{

public:

    Expr* left;
    const char* op;
    Expr* right;

    Equality(Expr* l, const char* o, Expr* r);

    Value *codegen() override;

    ~Equality() override;

}


class Expression : public Expr{

public:
    Expr* exp;

    ~Expression();
}










