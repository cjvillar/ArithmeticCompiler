#pragma once

#include "config.h"


class CodeGenerator : public ASTVisitor {
public:
    // Constructor to initialize the output stream
    CodeGenerator(std::ostream& out);

    // Visitor methods for the AST nodes
    void visit(ExprAST& exprAST) override;
    void visit(NumExprAST& numExprAST) override;
    void visit(BinOpExprAST& binOpExprAST) override;

    // Method to start the assembly code generation
    void generateAssembly(ExprAST& root);

private:
    std::ostream& out;
};
