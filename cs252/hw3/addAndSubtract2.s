# Zachary Thompson
# October 25, 2013

#Stack frame
        .equ    w, -8
        .equ    x, -4
        .equ    localSize, -16

#Read only data
        .section .rodata
prompt:
        .string "Enter two integers: "
getData:
        .string "%i %i"
display:
        .string "sum = %i, difference = %i\n"
warning:
        .string "Overflow has occured.\n"
#code
        .text
        .globl  main
        .type   main, @function
main:
        pushq   %rbp                #save caller's base pointer
        movq    %rsp, %rbp          #establish our base pointer
        addq    $localSize, %rsp    #for local vars

        movl    $prompt, %edi       #prompt user
        movl    $0, %eax            #no floats
        call    printf

        leaq    x(%rbp), %rdx       # &x
        leaq    w(%rbp), %rsi       # &w
        movl    $getData, %edi      #get user data
        movl    $0, %eax            #no floats
        call    scanf

        movl    w(%rbp), %esi       #y = w
        addl    x(%rbp), %esi       #y += x
        movl    %esi, %r12d         # save result1
        jno     noOver1             #skip warning if no OF
        movl    $warning, %edi
        movl    $0, %eax
        call    printf
noOver1:
        movl    w(%rbp), %edx       #z = w
        subl    x(%rbp), %edx       #z -= x
        movl    %edx, %r13d          #save result2
        jno     nOver2              #skip warning if no OF
        movl    $warning, %edi
        movl    $0, %eax
        call    printf
nOver2:
        movl    %r12d, %esi         #load result1 for printf
        movl    %r13d, %edx         #load result2 for printf
        movl    $display, %edi      #display results
        movl    $0, %eax            #no floats
        call    printf

        movl    $0, %eax            #return 0 to OS
        movq    %rbp, %rsp          #restore stack pointer
        popq    %rbp                #restore caller's base pointer
        ret
