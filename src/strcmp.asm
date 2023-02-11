bits 64                                 ; set the register sizes to 64 bits

section .text
    global strcmp                       ; export strcmp

strcmp:
    enter 0, 0                          ; prelude
    mov r8, 0                           ; set address counter to 0

check_and_loop:
    movzx eax, byte [rdi + r8]          ; get the first byte of the first string in a 4 byte register
    movzx ecx, byte [rsi + r8]          ; get the first byte of the second string in a 4 byte register
    cmp al, 0                           ; check if byte of first string it is zero
    je diff_and_return                  ; if it is, return
    cmp al, cl                          ; comapre the current two bytes
    jne diff_and_return                 ; if they are different, return
    inc r8                              ; increment counter
    jmp check_and_loop                  ; continue the loop

diff_and_return:
    sub eax, ecx
    leave                               ; epilogue
    ret
