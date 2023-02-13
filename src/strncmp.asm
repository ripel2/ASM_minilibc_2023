bits 64                                 ; set the register sizes to 64 bits

section .text
    global strncmp                      ; export strncmp

strncmp:
    enter 0, 0                          ; prelude
    mov r8, 0                           ; set counter to zero
    mov eax, 0                          ; set first byte temp to 0
    mov ecx, 0                          ; set second byte temp to 0

compare_and_inc:
    cmp edx, 0                          ; check if we still need to compare the two strings (n > 0)
    je diff_and_return                  ; if we don't need to, return
    movzx eax, byte [rdi + r8]          ; get the first byte of the first string in a 4 byte register
    movzx ecx, byte [rsi + r8]          ; get the first byte of the second string in a 4 byte register
    cmp al, 0                           ; check if byte of first string it is zero
    je diff_and_return                  ; if it is, return
    cmp al, cl                          ; comapre the current two bytes
    jne diff_and_return                 ; if they are different, return
    inc r8d                             ; increment the counter
    dec edx                             ; decrement n
    jmp compare_and_inc                 ; continue the loop

diff_and_return:
    sub eax, ecx                        ; compute diff between two last bytes
    leave                               ; epilogue
    ret
