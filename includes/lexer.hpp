#pragma once
#include <iostream>
#include <vector>

#undef EOF

enum TokenType{
  
    //Single character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, EOE, DOT, COMMA,

    //BANG = !
    // 1-2 character tokens
    GREATER, GREATER_EQUAL, EQUAL, EQUAL_EQUAL, LESS,
    LESS_EQUAL, BANG, BANG_EQUAL, SLASH_SLASH, SLASH, STAR_STAR, STAR, MINUS, ADD, MINUS_MINUS, ADD_ADD,

    //literals
    IDENTIFIER, STRING, NUMBER,

    //keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NULL_T, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    EXTENDS, SWITCH, FOREACH, DO, IMPORT, INCLUDE,

    //Other
    EOF

};

struct Token{

  TokenType type;
  std::string lexeme;
  std::string value;
  int line;

  Token(TokenType type, const std::string& lexeme, const std::string& value, int line);

  

};


class Lexer{

    std::vector<Token*> data;

    int current;
    int start;
    int line;

    std::string code;
public:
    Lexer(std::string code);

    char advance();
    char peek(int index);
    void lex();

    void addToken(TokenType type, const std::string &value=std::string());


};





