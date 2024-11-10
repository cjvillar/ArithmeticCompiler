    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    mov $2, %rax
    mov $6, %rbx
    imulq %rbx, %rax
    mov $-1, %rbx
    add %rbx, %rax

movq %rax, %rsi
lea result(%rip), %rdi
xor %rax, %rax
sub $8, %rsp     # Align stack for printf call
call _printf     # Call printf
add $8, %rsp     # Restore stack after call

xor %rdi, %rdi
call _exit
