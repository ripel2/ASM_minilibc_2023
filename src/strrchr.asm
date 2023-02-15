bits 64                                 ; set the register sizes to 64 bits
 
section .text   
    global strrchr                      ; export strrchr

strrchr:
    enter 0, 0                          ; prelude
    movzx eax, byte [rdi]               ; get the first byte of the string in a 4 byte register
    cmp al, 0                           ; check if it is zero
    je set_zero                         ; if it is, jump to set zero (reached end of string)
    mov rdx, 0                          ; initialize the result to zero

check_and_loop:
    cmp esi, eax                        ; compare the current character against c
    cmove rdx, rdi                      ; set the result to the current address if it is c
    inc rdi                             ; increment the current char address
    movzx eax, byte [rdi]               ; get the next byte of the string in a 4 byte register
    cmp al, 0                           ; check if we reached the end of the string
    jne check_and_loop                  ; if not, continue the loop

verif_null:
    cmp esi, 0                          ; if we need to return the result, we check if c is \0
    cmove rdx, rdi                      ; if it is we need to return the position of \0 so we set the result to it
    mov rax, rdx                        ; put the result in the return register
    leave                               ; epilogue
    ret                                 ; return

set_zero:
    mov rdx, 0                          ; set the result to zero
    jmp verif_null                      ; jump to check if c is \0
