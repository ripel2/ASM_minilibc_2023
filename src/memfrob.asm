bits 64                                 ; set the register sizes to 64 bits

section .text
    global memfrob                       ; export memset

memfrob:
    enter 0, 0                          ; prelude
    mov rax, rdi                        ; set return value of memset to the original pointer
    add rsi, rdi                        ; (ptr + n) it is the address where we need to stop setting memory
    mov rcx, rdi                        ; we use rcx as a counter, we will increment it and check it against rdx

check_and_loop:
    cmp rcx, rsi                        ; check if we are at the last memory address to set
    je return                           ; if we are, jump to return
    xor byte [rcx], 42                  ; xor the current byte with 42
    inc rcx                             ; increment the counter by one
    jmp check_and_loop                  ; continue the loop

return:
    leave                               ; epilogue
    ret                                 ; return the value
