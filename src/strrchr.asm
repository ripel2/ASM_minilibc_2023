bits 64                                 ; set the register sizes to 64 bits
 
section .text   
    global strrchr                      ; export strrchr

strrchr:
    movzx eax, byte [rdi]
    cmp al, 0
    je set_zero
    mov edx, 0

check_and_loop:
    cmp esi, eax
    cmove rdx, rdi
    inc rdi
    movzx eax, byte [rdi]
    cmp al, 0
    jne check_and_loop

verif_null:
    cmp esi, 0
    cmove rdx, rdi
    mov rax, rdx
    ret

set_zero:
    mov edx, 0
    jmp verif_null
