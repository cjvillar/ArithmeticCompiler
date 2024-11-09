#pragma once

#include "config.h"

class Parser {
 public:
  // constructor inits parser
  Parser(const std::string& input);

  // main func starts parsing process
  void parse();

  // returns result (root of the AST)
  std::unique_ptr<ExprAST>& getResult();

 private:
  Lexer lexer;  //instanciate lexerfor tokenizing input
  std::stack<Token> operatorStack;  //a stack to hold operators during parsing
  std::vector<std::unique_ptr<ExprAST> > partialParse;  // a stackto hold partial ASTs
  std::unique_ptr<ExprAST> result;  // result AST 

  // method to handle number tokens NumExprAST nodes
  void handleNumber(const Token& token);

  // method to handle operator tokens (pushes them onto the operator stack)
  void handleOperator(const Token& token);

  // method to handle right parentheses and builds BinOpExprAST from the last two expressions
  void handleRightParenthesis();

  // method to validate final result.
  void validateResult();

  // TODO: Add operator precedence and associativity handling in future improvements
};
