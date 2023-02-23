bits 64                                 ; set the register sizes to 64 bits

section .text
    global ffs                       ; export memcpy

ffs:
    enter 0, 0
	mov eax, edi
	cmp rdi, 0
	je return
	and eax, 1
	jne return_one

check_and_loop:
	sar rdi, 1
	inc eax
	test dil, 1
	je check_and_loop
    inc eax

return:
    leave
	ret

return_one:
	mov eax, 1
	leave
    ret
