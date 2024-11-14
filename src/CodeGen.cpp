#include "includes/config.h"

// The CodeGenerator only (almost) works for x86 assembly.
// this is a derived AST class , so that I can reuse the methods in AST but to
// generate
// x86 instead of an AST
// https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf
// https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture
// https://www.tutorialspoint.com/assembly_programming/assembly_arithmetic_instructions.htm

CodeGenerator::CodeGenerator(std::ostream& out) : out(out) {}

void CodeGenerator::visit(ExprAST& exprAST) {
  // No specific code for generic ExprAST, meant for derived classes
}

// Assembly generator for a numbers
void CodeGenerator::visit(NumExprAST& numExprAST) {
  static bool firstNum = true;
  if (firstNum) {
    out << "    mov $" << numExprAST.getValue() << ", %rax\n";
    firstNum = false;
  } else {
    out << "    mov $" << numExprAST.getValue() << ", %rbx\n";
    firstNum = true;  // reset back to first num
  }
}


void CodeGenerator::visit(BinOpExprAST& binOpExprAST) {
  // Visit the left operand and generate code
  binOpExprAST.getLeft()->accept(*this);  // Generate code for the left operand
  //out << "    mov %rax, %rcx\n";

  // Visit the right operand and generate code
  binOpExprAST.getRight()->accept(
      *this);  // Generate code for the right operand
  //out << "    mov %rcx, %rax\n";

  // Create Assembly code based on token
  switch (binOpExprAST.getKind()) {
    case TokenKind::PLUS:
      out << "    add %rax, %rbx\n";
      out << "    mov %rbx, %rax\n"; //move result to rax 
      break;

    case TokenKind::MINUS:
      out << "    sub %rbx, %rax\n";
      break;

    case TokenKind::MULTIPLY:
      out << "    imulq %rbx, %rax\n";
      break;

    case TokenKind::DIVIDE:
      out << "    cqto    #Convert quadword in %rax to octoword in %rdx:%rax\n";  // Convert quadword in %rax to octoword in %rdx:%rax
      out << "    idivq %rbx\n";  // Divide %rax by %rbx, quotient in %rax,
                                  // remainder in %rdx need to fix
      break;

    default:
      throw std::runtime_error("Unsupported binary operation.");
  }
}


// Method to start assembly code gen (lots of biolerplate)
void CodeGenerator::generateAssembly(ExprAST& root) {
  out << "    .data\n";
  out << "result: .asciz \"Result: %ld\\n\"\n";  // out str format
  out << "    .text\n";
  out << "    .globl _start\n";
  out << "_start:\n";

  // Generates code by visiting the AST's root node (calc function)
  root.accept(*this);

  // Returning from the function (more boilerplate)
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