bits 64                                 ; set the register sizes to 64 bits

section .text
    global memcpy                       ; export memcpy

memcpy:
    enter 0, 0                          ; prelude
    mov rax, rdi                        ; set return value of memcpy to the original pointer
    mov rcx, 0                          ; set rcx to 0, used as a counter for the current byte to copy

check_and_loop:
    cmp rdx, rcx                        ; compare the counter and the size argument
    je return                           ; if we didnt reach the end we need to continue tne loop
    mov r8b, byte [rsi + rcx]           ; store the current byte in a temporary byte register
    mov byte [rdi + rcx], r8b           ; copy the byte in the other address
    inc rcx                             ; increment the counter
    jmp check_and_loop                  ; continue the loop

return:
    leave                               ; epilogue
    ret                                 ; return the value
