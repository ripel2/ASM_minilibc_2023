bits 64                                 ; set the register sizes to 64 bits
    
section .text   
    global strchr                       ; export strchr

strchr:
    movzx eax, byte [rdi]               ; get the first byte of the string in a 4 byte register
    movsx edx, al                       ; move al in a 4 byte register to compare it against c (int)
    cmp esi, edx                        ; compare if the current character is c
    je return                           ; if it is, we can return
    inc rdi                             ; else, increment the address
    cmp al, 0                           ; see if we reached the end of the string
    jne strchr                          ; if not, continue the loop
    cmp esi, 0                          ; check if c is zero ('\0')
    je return                           ; if it is, we need to return the address of the '\0', so we return
    mov rax, 0                          ; else, it means that we didnt found c, so we set the return value to 0
    ret                                 ; and we return

return:
    mov rax, rdi                        ; set the return value to the last address checked
    ret                                 ; and return
