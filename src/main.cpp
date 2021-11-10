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


/*
NOTES

Use llvm for backend 
https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl03.html
https://llvm.org/doxygen/classllvm_1_1IRBuilder.html

TODO build parser (start with single statement to test)
TODO install llvm
TODO build ast to ir for llvm
TODO build file reader
TODO setup argparser








*/