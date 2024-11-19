    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    mov $41, %rax
    push %rax
    mov $378, %rax
    pop %rbx
    add %rbx, %rax
    push %rax
    mov $19, %rax
    push %rax
    mov $54, %rax
    push %rax
    mov $6, %rax
    pop %rbx
    sub %rax, %rbx
    mov %rbx, %rax
    pop %rbx
    mov %rax, %rcx
    mov %rbx, %rax
    cqto    #Convert quadword in %rax to octoword in %rdx:%rax
    idivq %rcx
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
