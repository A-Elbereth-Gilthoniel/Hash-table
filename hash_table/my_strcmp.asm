global my_strcmp
section .text

my_strcmp:
    cycle:
        cmp byte [rel rdi], 0x00
        je check_equal
        mov dl, byte [rel rsi]
        cmp byte [rel rdi], dl
        jne not_equal
        add rdi, 1
        add rsi, 1
    jmp cycle

    not_equal:
        mov rax, 0x01
        ret

    check_equal:
        cmp byte [rel rsi], 0x00
        jne not_equal
        xor rax, rax
        ret


; debug_print:
;     push rax
;     push rdi
;     push rsi
;     push rdx
;
;     mov rax, 0x01
;     mov rdi, 0x01
;     mov rdx, 1
;     syscall
;
;     pop rdx
;     pop rsi
;     pop rdi
;     pop rax
;     ret
;
; debug_print3:
;     push rax
;     push rdi
;     push rsi
;     push rdx
;
;     mov rax, 0x01
;     mov rsi, rdi
;     mov rdi, 0x01
;     mov rdx, 1
;     syscall
;
;     pop rdx
;     pop rsi
;     pop rdi
;     pop rax
;     ret
;
;
; debug_print2:
;     push rax
;     push rdi
;     push rsi
;     push rdx
;
;     mov rax, 0x01
;     mov rdi, 0x01
;     mov rdx, 1
;     lea rsi, [rel ddd]
;     syscall
;
;     pop rdx
;     pop rsi
;     pop rdi
;     pop rax
;     ret
