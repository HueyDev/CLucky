#include "expr.hpp"
#include "log.hpp"

template <typename T>
bool Expr::isInstance(){

        return dynamic_cast<T*>(this) != nullptr;

}


