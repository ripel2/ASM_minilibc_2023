bits 64                                 ; set the register sizes to 64 bits

section .text
    global memcpy                       ; export memcpy

memcpy:
    enter 0, 0
    mov rdi, rax
    cmp rdx, 0
    je return
    mov rcx, 0
set_and_loop:
    mov r8b, byte [rsi + rcx]
    mov byte [rdi + rcx], r8b
    inc rcx
    cmp rdx, rcx
    jne set_and_loop
return:
    leave
    ret