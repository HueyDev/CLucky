#pragma once
#include <iostream>

void throwError(const std::string& text, int line, int character=0);

bool isError();
