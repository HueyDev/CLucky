#include <iostream>

bool errorThrown = false;

void throwError(const std::string& text, int line, int character){

  std::cout << "Compile error on line " << line << " character " << character << " \"" << text << "\"" << std::endl;

  errorThrown = true;

}


bool isError(){
  return errorThrown;
}