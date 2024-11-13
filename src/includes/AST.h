//https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html

#pragma once

#include "config.h"

class ExprAST;
class NumExprAST;
class BinOpExprAST;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default; // Ensure a virtual destructor is defined
    virtual void visit(ExprAST& exprAST) = 0; // Ensure this is pure virtual
    virtual void visit(NumExprAST& numExprAST) = 0; // Pure virtual
    virtual void visit(BinOpExprAST& binOpExprAST) = 0; // Pure virtual
};

class ExprAST {
 public:
  virtual ~ExprAST() = default;

  // This function acts as a fallback mechanism to ensure that
  // all subclasses of ExprAST can print themselves with proper
  // indentation. The empty string argument `indent` allows for
  // proper formatting when recursion occurs in `BinOpExprAST`.
  virtual void print(std::string indent) = 0;

  // This is a visitor pattern method that should be implemented by
  // derived classes. It could be marked as a pure virtual function
  // to ensure that all subclasses provide an implementation.
  //codeGen is an instance of ASTVisitor class 
  virtual void accept(ASTVisitor &codeGen) = 0;
};

class NumExprAST : public ExprAST {
 public:
  NumExprAST(Token token) {
    // Assume token.getValue() returns an int directly, so just assign it
    if (token.getKind() == TokenKind::NUMBER) {
      value = token.getValue();  // No need to call value() or has_value() since
                                 // it's not an optional
    } else {
      throw std::runtime_error("Invalid token for number node.");
    }
  }

  int getValue() const { return value; }
  void print(std::string indent) override { std::cout << getValue() << "\n"; }
  void accept(ASTVisitor &codeGen) override { codeGen.visit(*this); }

 private:
  int value;
};

class BinOpExprAST : public ExprAST {
 public:
  BinOpExprAST(Token token, std::unique_ptr<ExprAST> &left,
               std::unique_ptr<ExprAST> &right)
      : kind(token.getKind()), left(std::move(left)), right(std::move(right)) {}
  
  // Returns the kind of the token associated with this binary operation.
  TokenKind getKind() const { return kind; }

  // Consider returning const pointers or references here to avoid
  // transferring ownership unintentionally.
  const std::unique_ptr<ExprAST> &getLeft() const { return left; }
  const std::unique_ptr<ExprAST> &getRight() const { return right; }

  // helper method for enum to sting operators
  std::string tokenKindToString(TokenKind kind) {
    switch (kind) {
      case TokenKind::PLUS:
        return "\033[31m(+)\033[31m"; //\033[31m ansi code for red
      case TokenKind::MINUS:
        return "\033[31m(-)\033[31m";
      case TokenKind::MULTIPLY:
        return "\033[31m(*)\033[31m";
      case TokenKind::DIVIDE:
        return "\033[31m(/)\033[31m";
      default:
        return "Unknown";
    }
  }

  //The print function displays the operation along with its two operands,
  //indented appropriately for recursive structures.
  void print(std::string indent) override {
    //returns string op instead of enum
    std::cout << indent << tokenKindToString(getKind()) << "\n";
    std::cout << indent << "├── ";
    left->print("   " + indent);
    std::cout << indent << "├── ";
    right->print("    " + indent);
  }

  // working on new tree structure here: 
//   void print(std::string indent="", bool isLast = true) override {
//     std::cout << indent;
//     if (!indent.empty()) {
//         std::cout << (isLast ? "└──" : "├──");
//     }
//     std::cout << tokenKindToString(getKind()) << "\n";

//     if (left) {
//         left->print(indent + (isLast ? "    " : "│  "), false);
//     }
//     if (right) {
//         right->print(indent + (isLast ? "    " : "│  "), true);
//     }
// }

  // This implements the visitor pattern for the binary operation node.
  void accept(ASTVisitor &codeGen) override { codeGen.visit(*this); }

 private:
  TokenKind
      kind;  // The type of binary operation (e.g., addition, subtraction).

  // Left and right operands of the binary operation.
  std::unique_ptr<ExprAST> left, right;
};
