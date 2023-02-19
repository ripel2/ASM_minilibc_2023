bits 64                                 ; set the register sizes to 64 bits

section .text
    global strpbrk                      ; export strpbrk

strpbrk:
    enter 0, 0                          ; prelude
    mov rax, rdi                        ; set rax to rdi (will be used as the address of the current string char)
    mov r8b, byte [rdi]                 ; get the first byte of the string
    cmp r8b, 0                          ; check if it is zero
    je return_null                      ; if it is we need to return null
    mov dil, byte [rsi]                 ; get the first accept char

main_loop_init:
    mov rcx, rsi                        ; set rcx to rsi (will be used as the address of the current accept char)
    mov rdx, rdi                        ; set rdx to rdi (will be used as the address of the current string char)
    cmp dil, 0                          ; check if the current accept char is zero
    je main_loop_continue               ; if it is , continue the main loop

accept_loop:
    cmp dl, r8b                         ; compare the current string char and the current accept char
    je return                           ; if they are equal return the current string char
    inc rcx                             ; increment the address of the current accept char
    mov dl, byte [rcx]                  ; get the next accept char
    cmp dl, 0                           ; check if it is zero
    jne accept_loop                     ; if its not continue the accept loop

main_loop_continue:
    inc rax                             ; increment the address of the current string char
    mov r8b, byte [rax]                 ; get the next string char
    cmp r8b, 0                          ; check if it is zero
    jne main_loop_init                  ; if its not continue the main loop

return_null:
    mov rax, 0                          ; set the result to null

return:
    leave                               ; epilogue
    ret                                 ; return
