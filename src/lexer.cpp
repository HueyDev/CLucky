#include "lexer.hpp"
#include "log.hpp"
#include <iostream>

Token::Token(TokenType type, const std::string& lexeme, const std::string& value, int line){

    this->type = type;
    this->lexeme = lexeme;
    this->value = value;
    this->line = line;

}

Lexer::Lexer(std::string code){
    this->code = code;
}

char Lexer::advance(){
    this->current++;
    return this->code[this->current];
}

char Lexer::peek(int index){

    return this->code[this->current + index];
}

void Lexer::addToken(TokenType type, const std::string& value){
    std::string id = this->code.substr(this->start, this->current);
    this->data.push_back(new Token(type, id, value, this->line));
}


void Lexer::lex(){
    this->start = 0;
    this->current = 0;
    this->line = 0;

    bool endLex = false;

    while(!endLex){
        char tokenChar = this->advance();
        switch(tokenChar){

            case '\0': endLex = true; break;
            case '(': this->addToken(LEFT_PAREN); break;
            case ')': this->addToken(RIGHT_PAREN); break;
            case '[': this->addToken(LEFT_BRACE); break;
            case ']': this->addToken(RIGHT_BRACE); break;
            case '/':
                if(this->peek(1) == '/'){
                    this->addToken(SLASH_SLASH);
                }
                else{
                    this->addToken(SLASH);
                }
                break;
            
            case '*':
                if(this->peek(1) == '*'){
                    this->addToken(STAR_STAR);
                }
                else{
                    this->addToken(STAR);
                }
                break;



            default:
                throwError("UNKNOWN TOKEN " + tokenChar, this->line+1); break;

        }
    }
}

