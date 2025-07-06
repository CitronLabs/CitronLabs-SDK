BITS 64

extern fiberNext
global fiberYield


;System V calling convention 
; return : rax
; arg1 : rdi
; arg2 : rsi
; arg3 : rdx
; arg4 : rcx
; arg5 : r8
; arg6 : r9

section .text 

fiberYield:
	push rdi
        push rbp
        push rbx
        push r12
        push r13
        push r14
        push r15
        mov rdi, rsp    
        jmp fiberNext
	
