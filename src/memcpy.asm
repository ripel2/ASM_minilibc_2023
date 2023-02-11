bits 64                                 ; set the register sizes to 64 bits

section .text
    global memcpy                       ; export memcpy

memcpy:
    enter 0, 0                          ; prelude
    mov rcx, 0                          ; set rcx to 0, used as a counter for the current byte to copy
  
set_and_loop:
    mov r8b, byte [rsi + rcx]           ; store the current byte in a temporary byte register
    mov byte [rdi + rcx], r8b           ; copy the byte in the other address
    inc rcx                             ; increment the counter
    cmp rdx, rcx                        ; compare the counter and the size argument
    jne set_and_loop                    ; if we didnt reach the end we need to continue tne loop

return:
    leave                               ; epilogue
    ret                                 ; return the value
