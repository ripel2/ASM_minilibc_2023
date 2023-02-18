bits 64                                 ; set the register sizes to 64 bits

section .text
    global memmove                      ; export memmove

memmove:
    enter 0, 0                          ; prelude
    mov rax, rdi                        ; set return value of memmove to the original pointer
    cmp rdi, rsi                        ; compare the two memory address
    jge overlap                         ; if rsi >= rdi we need to handle the overlap
    mov rcx, 0                          ; else, we can start copying like with memcpy

check_and_loop:
    cmp rdx, rcx                        ; compare the counter and the size argument
    je return                           ; if we didnt reach the end we need to continue tne loop
    mov r8b, byte [rsi + rcx]           ; store the current byte in a temporary byte register
    mov byte [rdi + rcx], r8b           ; copy the byte in the other address
    inc rcx                             ; increment the counter
    jmp check_and_loop                  ; continue the loop

overlap:
    mov rcx, rdx                        ; set the counter to the size argument
    dec rcx                             ; decrement the counter to start from the last byte
    cmp rdx, 0                          ; check if the size argument is 0
    je return                           ; if it is, we can just return like normal                  

overlap_loop:
    cmp rcx, -1                         ; check if the counter is -1 (in overlap we decrement the counter)
    je return                           ; if it is, we can just return like normal
    mov r8b, byte [rsi + rcx]           ; store the current byte in a temporary byte register
    mov byte [rax + rcx], r8b           ; copy the byte in the other address
    dec rcx                             ; decrement the counter
    jmp overlap_loop                    ; continue the loop

return:
    leave                               ; epilogue
    ret                                 ; return the value
