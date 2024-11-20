    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    mov $2, %rax
    push %rax
    mov $3, %rax
    pop %rbx
    imulq %rbx, %rax
    push %rax
    mov $4, %rax
    push %rax
    mov $5, %rax
    pop %rbx
    imulq %rbx, %rax
    pop %rbx
    add %rbx, %rax

movq %rax, %rsi
lea result(%rip), %rdi
xor %rax, %rax
sub $8, %rsp     # Align stack for printf call
call _printf     # Call printf
add $8, %rsp     # Restore stack after call

xor %rdi, %rdi
call _exit
