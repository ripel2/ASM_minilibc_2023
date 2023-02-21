bits 64                                 ; set the register sizes to 64 bits
 
section .text   
    global strstr                       ; export strstr

strstr:
    enter 0, 0                          ; prelude
    cmp byte [rsi], 0                   ; see if the needle is an empty string (needle[0] = '\0')
    je found_empty_needle               ; if it is, return str, else we can start the search
    cmp byte [rdi], 0                   ; see if the string is empty
    je return_zero                      ; if it is, return null
    mov rax, 0                          ; set rax to 0 (will be used as a counter for the current string of str)

main_loop:
    mov rdx, 0                          ; set rdx to 0 (will be used as a counter for the current string of needle)
    mov rcx, rdi                        ; set rcx to the start of the string
    add rcx, rax                        ; add the current string counter to the start of the string

needle_loop:
    movzx r8d, byte [rsi + rdx]         ; get the first byte of the needle in r8
    cmp byte [rcx + rdx], r8b           ; compare the current byte of the needle with the current byte of the string
    jne not_match                       ; if they dont match go to not_match
    inc rdx                             ; if they do match, increment the needle counter
    cmp byte [rsi + rdx], 0             ; check if the current byte of the needle is \0
    jne needle_loop                     ; if its not, continue the search
    add rax, rdi                        ; else, we found the needle so we return the pointer to the start of the needle
    leave                               ; epilogue
    ret

found_empty_needle:
    mov rax, rdi                        ; if needle is empty we need to return the pointer to the start of the string
    leave                               ; epilogue
    ret

return_zero:
    mov rax, 0                          ; set the result to zero
    leave                               ; epilogue
    ret

not_match:
    inc rax                             ; if no match is found increment the string start counter
    cmp byte [rdi + rax], 0             ; check if the current byte is \0
    jne main_loop                       ; if it is not, continue the search
    jmp return_zero                     ; else, we didn't find the needle, so we return zero
