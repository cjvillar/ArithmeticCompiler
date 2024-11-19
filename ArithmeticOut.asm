    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    mov $5, %rax
    push %rax
    mov $20, %rax
    push %rax
    mov $8, %rax
    pop %rbx
    sub %rax, %rbx
    mov %rbx, %rax
    pop %rbx
    add %rbx, %rax
    push %rax
    mov $4, %rax
    pop %rbx
    imulq %rbx, %rax

movq %rax, %rsi
lea result(%rip), %rdi
xor %rax, %rax
sub $8, %rsp     # Align stack for printf call
call _printf     # Call printf
add $8, %rsp     # Restore stack after call

xor %rdi, %rdi
call _exit
