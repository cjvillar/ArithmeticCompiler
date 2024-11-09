#include "includes/config.h"

// The CodeGenerator only (almost) works for x86 assembly.
// this is a derived AST class , so that I can reuse the methods in AST but to
// generate
// x86 instead of an AST
// https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf

CodeGenerator::CodeGenerator(std::ostream& out) : out(out) {}

void CodeGenerator::visit(ExprAST& exprAST) {
  // No specific code for generic ExprAST, meant for derived classes
}

// assembly generator for a numbers
void CodeGenerator::visit(NumExprAST& numExprAST) {
  out << "    mov $" << numExprAST.getValue() << ", %rax\n";
}

// // assembly generator for a binary operations
// void CodeGenerator::visit(BinOpExprAST& binOpExprAST) {
//   //Visit the left and right subtrees and generate code
//   binOpExprAST.getLeft()->accept(*this);
//   out << "    push %rax\n";  // Save the result of the left operand to the
//   stack

//   binOpExprAST.getRight()->accept(*this);
//   out << "    pop %rbx\n";  // Retrieve the left operand from the stack

void CodeGenerator::visit(BinOpExprAST& binOpExprAST) {
  // Visit the left operand and generate code
  binOpExprAST.getLeft()->accept(*this);  // Generate code for the left operand
  out << "    mov %rax, %rbx\n";

  // Visit the right operand and generate code
  binOpExprAST.getRight()->accept(
      *this);  // Generate code for the right operand

  // Create Assembly code based on token
  switch (binOpExprAST.getKind()) {
    case TokenKind::PLUS:
      out << "    add %rbx, %rax\n";
      break;

    case TokenKind::MINUS:
      out << "    sub %rax, %rbx\n";
      out << "    mov %rbx, %rax\n";  // Move the result back to %rax
      break;

    case TokenKind::MULTIPLY:
      out << "    imulq %rbx, %rax\n";
      break;

    case TokenKind::DIVIDE:
      out << "    cqto\n";  // Convert quadword in %rax to octoword in %rdx:%rax
      out << "    idivq %rbx\n";  // Divide %rax by %rbx, quotient in %rax,
                                  // remainder in %rdx need to fix
      break;

    default:
      throw std::runtime_error("Unsupported binary operation.");
  }
}

// Method to start assembly code gen (lots of biolerplate not sure if correct)
void CodeGenerator::generateAssembly(ExprAST& root) {
  out << "    .data\n";
  out << "result: .asciz \"Result: %ld\\n\"\n";  // out str format
  out << "    .text\n";
  out << "    .globl _start\n";
  out << "_start:\n";

  // generates code by visiting the AST's root node (calc function)
  root.accept(*this);

  // returning from the function
  out << "\n";
  out << "movq %rax, %rsi\n";
  out << "lea result(%rip), %rdi\n";
  out << "xor %rax, %rax\n";

  // allign stack ( proper alignment before calling _printf )
  out << "sub $8, %rsp     # Align stack for printf call\n";
  out << "call _printf     # Call printf\n";
  out << "add $8, %rsp     # Restore stack after call\n";

  // Exit program 
  out << "\n";
  out << "xor %rdi, %rdi\n";
  out << "call _exit\n";
}
