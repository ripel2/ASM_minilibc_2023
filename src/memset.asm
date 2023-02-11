bits 64                                 ; set the register sizes to 64 bits

section .text
    global memset                       ; export memset

memset:
    enter 0, 0                          ; prelude
    add rdx, rdi                        ; (ptr + n) it is the address where we need to stop setting memory
    mov rcx, rdi                        ; we use rcx as a counter, we will increment it and check it against rdx

check_and_loop:
    cmp rcx, rdx                        ; check if we are at the last memory address to set
    je return                           ; if we are, jump to return
    mov byte [rcx], sil                 ; set one byte in the current address with value from the c argument
    add rcx, 1                          ; increment the counter by one
    jmp check_and_loop                  ; continue the loop

return:
    leave                               ; epilogue
    ret                                 ; return the value
