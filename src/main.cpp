#include <iostream>
#include "log.hpp"
#include "lexer.hpp"

void interactiveScript(){
  while(true){
    std::string input;
    std::cin >> input;

  }
}

int main() {
    Lexer* l = new Lexer("()[]()\"HELLO\"; TEST [[[]] ]; 127.98");
    l->lex();
    delete l;
}