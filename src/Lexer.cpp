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

    if (currentChar == '-' && std::isdigit(peek())) {
      numberValue = parseNumber();
      return Token(NUMBER, numberValue);
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
      case '#':
        handleComment();
        advance();
        return Token(COMM);
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

void Lexer::handleComment() {
  // Comments must have format: # this is a comment #
  if (currentChar == '#') {
    advance(); // Move past initial '#'
    while (currentChar != '#' && currentChar != '\0') { // Handle until closing '#' or EOF
      advance();
    }
    if (currentChar == '#') { // Get closing '#' 
      advance();
    } else {
      throw std::invalid_argument("Comment Missing Closing '#' ");
    }
  }
}

int Lexer::parseNumber() {
  std::string numStr;

  // Handle negative numbers
  if (currentChar == '-') {
    numStr += currentChar;
    advance();
  }

  // Parse digits
  while (currentChar != '\0' && std::isdigit(currentChar)) {
    numStr += currentChar;
    advance();
  }

  // Check if numStr is valid before converting
  if (numStr.empty() || (numStr == "-")) {
    throw std::invalid_argument("parseNumber() called with no valid digits.");
  }

  return std::stoi(numStr);
}
// Check for - followed by number
char Lexer::peek() const {
  return (pos + 1 >= text.size()) ? '\0' : text[pos + 1];
}
