# Zachary Thompson
# October 25, 2013
# pushq experiment
#code
        .text
        .globl  main
        .type   main, @function
main:
        pushq   %rbp                #save caller's base pointer
        movq    %rsp, %rbp          #establish our base pointer

        pushq   %rax
        pushq   %rbx
        pushq   %rcx
        pushq   %rdx
        pushq   %rsp
        pushq   %rbp
        pushq   %rdi
        pushq   %rsi
        pushq   %r8
        pushq   %r9
        pushq   %r10
        pushq   %r11
        pushq   %r12
        pushq   %r13
        pushq   %r14
        pushq   %r15

        movl    $0, %eax            #return 0 to OS
        movq    %rbp, %rsp          #restore stack pointer
        popq    %rbp                #restore caller's base pointer
        ret
