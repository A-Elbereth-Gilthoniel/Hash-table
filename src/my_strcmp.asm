global my_strcmp
section .text

SSE42Support equ 0x00180000   ; проверяем биты 19 и 20
AVXSupport equ 0x10000000     ; проверяем бит 28
AVX2Support equ 0x20

my_strcmp:
        push    rbp
        mov     rbp, rsp
        and     rsp, -32
        sub     rsp, 200
        mov     QWORD  [rsp-112], rdi
        mov     QWORD  [rsp-120], rsi
        mov     DWORD  [rsp+196], 0
        vpxor   xmm0, xmm0, xmm0
        vmovdqa   [rsp+136], ymm0
.L11:
        mov     rax, QWORD  [rsp-112]
        mov     QWORD  [rsp-104], rax
        mov     rax, QWORD  [rsp-104]
        vmovdqu ymm0,   [rax]
        vmovdqa   [rsp+104], ymm0
        mov     rax, QWORD  [rsp-120]
        mov     QWORD  [rsp-96], rax
        mov     rax, QWORD  [rsp-96]
        vmovdqu ymm0,   [rax]
        vmovdqa   [rsp+72], ymm0
        vmovdqa ymm0,   [rsp+104]
        vmovdqa   [rsp-56], ymm0
        vmovdqa ymm0,   [rsp+72]
        vmovdqa   [rsp-88], ymm0
        vmovdqa ymm1,   [rsp-56]
        vmovdqa ymm0,   [rsp-88]
        vpcmpeqb        ymm0, ymm1, ymm0
        vmovdqa   [rsp+40], ymm0
        vmovdqa ymm0,   [rsp+40]
        vmovdqa   [rsp-24], ymm0
        vmovdqa ymm0,   [rsp-24]
        vpmovmskb       eax, ymm0
        nop
        not     eax
        mov     DWORD  [rsp+196], eax
        cmp     DWORD  [rsp+196], 0
        je      .L7
        mov     eax, DWORD  [rsp+196]
        tzcnt   eax, eax
        dec     eax
        mov     DWORD  [rsp+36], eax
        mov     eax, DWORD  [rsp+36]
        cdqe
        mov     rdx, QWORD  [rsp-112]
        add     rax, rdx
        movzx   eax, BYTE  [rax]
        test    al, al
        jne     .L8
        mov     eax, DWORD  [rsp+36]
        cdqe
        mov     rdx, QWORD  [rsp-120]
        add     rax, rdx
        movzx   eax, BYTE  [rax]
        test    al, al
        jne     .L8
        mov     eax, 0
        jmp     .L10
.L8:
        mov     eax, -1
        jmp     .L10
.L7:
        add     QWORD  [rsp-112], 32
        add     QWORD  [rsp-120], 32
        jmp     .L11
.L10:
        leave
        ret
