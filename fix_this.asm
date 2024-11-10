
    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    mov $10, %rax
    mov %rax, %rbx #moves 10 to rbx

    mov $38, %rax 
    add %rbx, %rax #add 10 + 38 = 48

    mov %rax, %rbx

    mov $19, %rax
    mov %rax, %rbx
    mov $54, %rax
    mov %rax, %rbx
    mov $6, %rax
    sub %rax, %rbx #sub 54 - 6 = 48 #Example ((10 + 38) * (19 - (54 - 6))), 19 - 48 = -29 
    mov %rbx, %rax 
    sub %rax, %rbx #its having a problem with neg num
    mov %rbx, %rax
    #imulq %rbx, %rax

movq %rax, %rsi
lea result(%rip), %rdi
xor %rax, %rax
sub $8, %rsp     # Align stack for printf call
call _printf     # Call printf
add $8, %rsp     # Restore stack after call

xor %rdi, %rdi
call _exit
