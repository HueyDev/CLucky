#pragma once
#include "lexer.hpp"


class Expr{

public:

    virtual ~Expr(){}

    template <typename T>
    bool isInstance();


};


class Binary : public Expr{

public:

    Expr* left;
    Token* op;
    Expr* right;

    Binary(Expr* left, Token* op, Expr* right);
    ~Binary();

}

class Grouping : public Expr{

public:

    Expr* expression;

    Grouping(Expr* exp);
    ~Grouping();

}

class Literal : public Expr{

public:

    std::string value;

    Literal(std::string value);
    ~Literal();

}

class Unary : public Expr{

public:

    Token* op;
    Expr* expression;

    Unary(Token* op, Expr* exp);
    ~Unary();
}











