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
    Lexer("()[]()\0").lex();
    std::cout << "HELLO";
}