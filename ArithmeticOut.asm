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
