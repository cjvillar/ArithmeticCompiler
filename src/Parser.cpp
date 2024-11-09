#include "includes/config.h"

// Init parser with input string, using the lexer to break down
// the string into tokens.
Parser::Parser(const std::string& input) : lexer(input) {}

void Parser::parse() {
  Token token;

  // Loop through tokens until (TokenKind::END).
  while ((token = lexer.getNextToken()).getKind() != TokenKind::END) {
    switch (token.getKind()) {
      case TokenKind::NUMBER:
        // Handle numeric literals by creating a NumExprAST node.
        handleNumber(token);
        break;
      case TokenKind::RPAREN:
        // Handle closing parentheses, which triggers the creation of
        // a binary expression node by combining previously parsed operands.
        handleRightParenthesis();
        break;
      default:
        // For all other tokens (assumed to be operators), push the token
        // onto the operator stack.
        handleOperator(token);
        break;
    }
  }

  // After parsing, validate that we have a valid expression result.
  validateResult();
}

void Parser::handleNumber(const Token& token) {
  // Create a NumExprAST node for the number token and add it to the partial
  // parse stack.
  std::unique_ptr<ExprAST> numExpr = std::make_unique<NumExprAST>(token);
  partialParse.push_back(std::move(numExpr));
}

void Parser::handleOperator(const Token& token) {
  // Push operator tokens onto the operator stack for later processing.
  operatorStack.push(token);

  // Potential future improvement: Here you may want to check the precedence
  // of the operator and apply operators if necessary to handle precedence
  // rules.
}

void Parser::handleRightParenthesis() {
  // Check if we have enough operators and operands to create a binary
  // expression.
  if (operatorStack.size() < 2 || partialParse.size() < 2) {
    throw std::runtime_error("Syntax error: too few operators or operands.");
  }

  // Create a BinOpExprAST node using the top operator and the last two
  // expressions.
  std::unique_ptr<ExprAST> binOpExpr = std::make_unique<BinOpExprAST>(
      operatorStack.top(), partialParse[partialParse.size() - 2],
      partialParse[partialParse.size() - 1]);

  // Remove the operator from the stack.
  operatorStack.pop();

  // Ensure that the operator just below is a left parenthesis.
  if (operatorStack.top().getKind() != TokenKind::LPAREN) {
    throw std::runtime_error("Syntax error: unbalanced parentheses.");
  }

  // Pop the left parenthesis off the operator stack.
  operatorStack.pop();

  // Remove the two operand expressions from the partial parse stack.
  partialParse.pop_back();
  partialParse.pop_back();

  // Add the newly created binary expression back onto the partial parse stack.
  partialParse.push_back(std::move(binOpExpr));
}

void Parser::validateResult() {
  // Ensure that after parsing, we only have one valid expression result.
  if (partialParse.size() != 1) {
    throw std::runtime_error("Syntax error. Parse failed.");
  }

  // Move the result from the partial parse stack to the result variable.
  result = std::move(partialParse[0]);
}

std::unique_ptr<ExprAST>& Parser::getResult() {
  // Return the final parsed expression.
  return result;
}
