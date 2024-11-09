#include "includes/config.h"

Lexer::Lexer(const std::string& text)
    : text(text),
      pos(0),
      currentChar(text.empty() ? '\0' : text[0]),
      numberValue(0) {}

Token Lexer::getNextToken() {
  while (currentChar != '\0') {
    if (std::isspace(currentChar)) {
      skipWhitespace();
      continue;
    }

    if (std::isdigit(currentChar)) {
      numberValue = parseNumber();
      return Token(NUMBER, numberValue);
    }

    switch (currentChar) {
      case '+':
        advance();
        return Token(PLUS);
      case '-':
        advance();
        return Token(MINUS);
      case '*':
        advance();
        return Token(MULTIPLY);
      case '/':
        advance();
        return Token(DIVIDE);
      case '(':
        advance();
        return Token(LPAREN);
      case ')':
        advance();
        return Token(RPAREN);
      default:
        advance();
        return Token(INVALID);
    }
  }

  return Token(END);
}

void Lexer::advance() {
  pos++;
  currentChar = (pos >= text.size()) ? '\0' : text[pos];
}

void Lexer::skipWhitespace() {
  while (currentChar != '\0' && std::isspace(currentChar)) {
    advance();
  }
}

int Lexer::parseNumber() {
  std::string numStr;
  while (currentChar != '\0' && std::isdigit(currentChar)) {
    numStr += currentChar;
    advance();
  }
  return std::stoi(numStr);
}