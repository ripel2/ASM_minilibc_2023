bits 64 ; set the register sizes to 64 bits

section .text
    global strlen ; export strlen

strlen:
    enter 0, 0 ; prologue
    mov rcx, -1 ; repne stops if rcx is 0, we set it to -1 so that it never reaches zero
    mov rsi, rdi ; rdi will be modified by scasb so we save it
    mov al, 0 ; scasb checks the current byte against the value stored in al
    repne scasb ; repeat scasb while the zf flag is not set
    sub rdi, rsi ; subtract the start pointer from the current pointer to get the length
    dec rdi ; remove one fron the length (the null terminator)
    mov rax, rdi ; move the result to rax
    leave ; epilogue
    ret ; return the value
