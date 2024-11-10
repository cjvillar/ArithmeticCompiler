    .data
result: .asciz "Result: %ld\n"
    .text
    .globl _start
_start:
    # Step 1: Calculate (10 + 38)
    mov $10, %rax
    mov %rax, %rbx         # %rbx = 10
    mov $38, %rax
    add %rbx, %rax         # %rax = 10 + 38 = 48
    mov %rax, %rbx         # %rbx now holds 48 for use in the final multiplication

    # Step 2: Calculate (54 - 6)
    mov $54, %rax
    sub $6, %rax           # %rax = 54 - 6 = 48
    mov %rax, %rcx         # %rcx now holds 48

    # Step 3: Calculate (19 - %rcx)
    mov $19, %rax
    sub %rcx, %rax         # %rax = 19 - 48 = -29
    mov %rax, %rcx         # %rcx now holds -29

    # Step 4: Multiply %rbx (48) * %rcx (-29)
    mov %rbx, %rax         # %rax = 48
    imulq %rcx, %rax       # %rax = 48 * -29 = -1392

    # Print result
    movq %rax, %rsi        # Place result in %rsi for printf
    lea result(%rip), %rdi # Load address of format string
    xor %rax, %rax         # Clear %rax for printf call
    sub $8, %rsp           # Align stack for printf call
    call _printf           # Call printf
    add $8, %rsp           # Restore stack after call

    # Exit program
    xor %rdi, %rdi
    call _exit
