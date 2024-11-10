#pragma once

#include "config.h"

class Lexer {
 public:
  Lexer(const std::string& text);

  Token getNextToken();
  std::string getTokenKindString(TokenKind kind) {
    switch (kind) {
      case TokenKind::NUMBER:
        return "NUMBER";
      case TokenKind::PLUS:
        return "PLUS";
      case TokenKind::MINUS:
        return "MINUS";
      case TokenKind::MULTIPLY:
        return "MULTIPLY";
      case TokenKind::DIVIDE:
        return "DIVIDE";
      case TokenKind::LPAREN:
        return "LPAREN";
      case TokenKind::RPAREN:
        return "RPAREN";
      case TokenKind::INVALID:
        return "INVALID";
      case TokenKind::END:
        return "END";
    }
    return "UNKNOWN";
  }

 private:
  std::string text;
  int pos;
  char currentChar;
  int numberValue;

  void advance();
  void skipWhitespace();
  int parseNumber();
  char peek() const;
};