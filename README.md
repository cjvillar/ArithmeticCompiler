## A simple compiler learning tool for the language of arithmetic 


TODO:  
   - Fix CodeGen, only works with simple expressions for now, but hey it works! 
   - Fix Division. 
   - Handle negative numbers 

Nice To Have:
   - Make Window Compatable

Test Assembly:
   ```bash
   gcc -o ArithmeticOut ArithmeticOut.asm -e _start  
   ```

### Usage:

Run math with an inFile. 

```infile.math``` example:

```bash
  (5 * 2)
```

```bash
   ./math ../infile.math
```


Output:

```bash
   Input Arithmetic Expression:
   (5 * 2)

   Lexical Analysis Output:
   LPAREN 
   NUMBER 5 
   MULTIPLY 
   NUMBER 2 
   RPAREN 

   Abstract Syntax Tree:

   (*)
   ├──5
   ├──2

   Executable generated: ./ArithmeticOut

   Assembly code generated in ./ArithmeticOut
```


Assembly Out File:

```bash
      .data
   result: .asciz "Result: %ld\n"
      .text
      .globl _start
   _start:
      mov $5, %rax
      mov %rax, %rbx
      mov $2, %rax
      imulq %rbx, %rax

   movq %rax, %rsi
   lea result(%rip), %rdi
   xor %rax, %rax
   sub $8, %rsp     # Align stack for printf call
   call _printf     # Call printf
   add $8, %rsp     # Restore stack after call

   xor %rdi, %rdi
   call _exit

```