#include "lexer.hpp"
#include "log.hpp"
#include <iostream>

bool isAlpha(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}

bool isAlphaNumeric(char c) {
    return isAlpha(c) || isNum(c);
}

Token::Token(TokenType type, const std::string& lexeme, const std::string& value, int line){

    this->type = type;
    this->lexeme = lexeme;
    this->value = value;
    this->line = line;

}

void Lexer::addKeyword(std::string key, TokenType value) {
    
    this->keywords.insert(std::pair<std::string, TokenType>(key, value));
}

TokenType Lexer::getKeyword(std::string key) {
    auto it = this->keywords.find(key);
    if (it == this->keywords.end()) {
        return INVALID;
    }
    return it->second;
}

Lexer::Lexer(std::string code){
    this->code = code;



    this->addKeyword("and", AND);
    this->addKeyword("class", CLASS);
    this->addKeyword("else", ELSE);
    this->addKeyword("false", FALSE);
    this->addKeyword("for", FOR);
    this->addKeyword("fun", FUN);
    this->addKeyword("if", IF);
    this->addKeyword("nil", NULL_T);
    this->addKeyword("or", OR);
    this->addKeyword("print", PRINT);
    this->addKeyword("return", RETURN);
    this->addKeyword("super", SUPER);
    this->addKeyword("this", THIS);
    this->addKeyword("true", TRUE);
    this->addKeyword("var", VAR);
    this->addKeyword("while", WHILE);


}

char Lexer::advance(){
    this->current++;
    return this->code[this->current-1];
}

char Lexer::peek(int index){

    return this->code[(this->current-1) + index];
}

void Lexer::addToken(TokenType type, const std::string& value){
    std::string id = this->code.substr(this->start, this->current-this->start);
    this->data.push_back(new Token(type, id, value, this->line));
}

void Lexer::parseInt() {
    
    bool pastDecimal = false;

    while (isNum(this->peek(1)) || (!pastDecimal && this->peek(1) == '.' && isNum(this->peek(2)) )) {
        this->advance();
    }

    this->addToken(NUMBER);

}

void Lexer::parseLiteral() {
    
    while (isAlphaNumeric(this->peek(1))) {
        this->advance();
    }

    std::string key = this->code.substr(this->start, this->current-this->start);
    TokenType t = this->getKeyword(key);

    if (t == INVALID) {
        t = IDENTIFIER;
    }

    this->addToken(t);

}

void Lexer::parseString() {

    while (this->peek(1) != '"') {
        if (this->peek(1) == '\n' || this->peek(1) == '\0') {
            this->line++;
            throwError("String was not complete: " + (this->code.substr(this->start + 1, (this->current - 1) - (this->start + 1))), this->line, this->current);
            break;
        }
        this->advance();
    }
    this->advance();

    this->addToken(STRING, this->code.substr(this->start+1,(this->current-1)-(this->start+1) ));

}

void Lexer::printResults() {

    for (int i = 0; i < this->data.size(); i++) {
        std::cout << this->data[i]->lexeme << std::endl;
    }

}

bool Lexer::isAtEnd() {
    return this->current >= this->code.length();
}

void Lexer::lex(){

    std::cout << "Lexing string: " << this->code << std::endl;

    this->start = 0;
    this->current = 0;
    this->line = 0;

    bool endLex = false;

    while(!(this->isAtEnd())){
        this->start = this->current;
        char tokenChar = this->advance();
        switch(tokenChar){

            case '\0': endLex = true; break;
            case '(': this->addToken(LEFT_PAREN); break;
            case ')': this->addToken(RIGHT_PAREN); break;
            case '[': this->addToken(LEFT_BRACE); break;
            case ']': this->addToken(RIGHT_BRACE); break;
            case ';': this->addToken(EOE); break;
            case '.': this->addToken(DOT); break;
            case ',': this->addToken(COMMA); break;

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

            case '+':
                if (this->peek(1) == '+') {
                    this->addToken(ADD_ADD);
                }
                else {
                    this->addToken(ADD);
                }
                break;

            case '-':
                if (this->peek(1) == '-') {
                    this->addToken(MINUS_MINUS);
                }
                else {
                    this->addToken(MINUS);
                }
                break;

            case '>':
                if (this->peek(1) == '=') {
                    this->addToken(GREATER_EQUAL);
                }
                else {
                    this->addToken(GREATER);
                }
                break;

            case '=':
                if (this->peek(1) == '=') {
                    this->addToken(EQUAL_EQUAL);
                }
                else {
                    this->addToken(EQUAL);
                }
                break;

            case '<':
                if (this->peek(1) == '=') {
                    this->addToken(LESS_EQUAL);
                }
                else {
                    this->addToken(EQUAL);
                }
                break;

            case '!':
                if (this->peek(1) == '=') {
                    this->addToken(BANG_EQUAL);
                }
                else {
                    this->addToken(BANG);
                }
                break;

            case '"':
                this->parseString();
                break;

            case '\n':
                this->line++;
                break;

            case ' ':
                break;


            default:
                if (isNum(tokenChar)) {
                    this->parseInt();
                    break;
                }
                else if (isAlphaNumeric(tokenChar)) {
                    this->parseLiteral();
                    break;
                }

                throwError("Unknown Token " + std::string(1, tokenChar), this->line+1, this->current);
                break;

        }
    }
}

