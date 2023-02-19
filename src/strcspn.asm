bits 64                                 ; set the register sizes to 64 bits

section .text
    global strcspn                      ; export strcspn

strcspn:
    enter 0, 0                          ; prelude
    mov cl, byte [rdi]                  ; get the first byte of the string in cl
    cmp cl, 0                           ; check if the string is empty
    je return_zero                      ; if it is, return zero
    mov r8d, 0                          ; set r8d to zero (will be used as the main loop counter and as result)

main_loop_init:
    mov rdx, rsi                        ; set rdx to the reject string pointer (set it back each time)
    mov al, byte [rsi]                  ; get the first reject char
    cmp al, 0                           ; check if it is zero
    je main_loop_continue               ; if it is, we can continue the main loop (it will act like strlen)

reject_loop:
    cmp al, cl                          ; compare the current reject char with the current char of the string
    je return                           ; if they are equal, we need to return
    inc rdx                             ; increment the reject string pointer
    mov al, byte [rdx]                  ; get the next reject char
    cmp al, 0                           ; check if it is zero
    jne reject_loop                     ; if it is not, continue the loop

main_loop_continue:
    inc r8                              ; increment the length (r8)
    mov cl, byte [rdi + r8]             ; get the next byte of the string
    cmp cl, 0                           ; check if it is zero
    jne main_loop_init                  ; if it is not, continue the loop
    jmp return                          ; else, jump to return to return the current result

return_zero:
    mov r8d, 0                          ; set the result to zero

return:
    mov eax, r8d                        ; get the result in eax (function return register)
    leave                               ; epilogue
    ret