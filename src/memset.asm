bits 64                                 ; set the register sizes to 64 bits

section .text
    global memset                       ; export memset

memset:
    enter 0, 0                          ; prelude
    cmp rdx, 0                          ; check if the n argument is zero
    je return                           ; if n is zero we return
    add rdx, rdi                        ; (ptr + n) it is the address where we need to stop setting memory
    mov rcx, rdi                        ; we use rcx as a counter, we will increment it and check it against rdx

set_and_inc:
   mov byte [rcx], sil                  ; set one byte in the current address with value from the c argument
   add rcx, 1                           ; increment the counter by one
   cmp rcx, rdx                         ; check if we are at the last memory address to set
   jne set_and_inc                      ; if we are not, jump back to set the next byte

return:
    leave                               ; epilogue
    ret                                 ; return the value
