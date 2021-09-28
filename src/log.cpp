#include <iostream>

bool errorThrown = false;

void throwError(std::string text, int line, int character=0){

  std::cout << "Compile error on line " << line << " character " << character << " \"" << text << "\"" << std::endl;

  errorThrown = true;

}


bool isError(){
  return errorThrown;
}