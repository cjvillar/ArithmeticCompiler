    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    mov $1, %rax
    push %rax
    mov $5, %rax
    pop %rbx
    add %rbx, %rax
    push %rax
    mov $2, %rax
    pop %rbx
    mov %rax, %rcx
    mov %rbx, %rax
    cqto    #Convert quadword in %rax to octoword in %rdx:%rax
    idivq %rcx
    push %rax
    mov $2, %rax
    pop %rbx
    sub %rax, %rbx
    mov %rbx, %rax

movq %rax, %rsi
lea result(%rip), %rdi
xor %rax, %rax
sub $8, %rsp     # Align stack for printf call
call _printf     # Call printf
add $8, %rsp     # Restore stack after call

xor %rdi, %rdi
call _exit
