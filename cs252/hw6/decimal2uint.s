# Zachary Thompson
# November 22, 2013

# Calling sequence
#       rdi <- address of string
#       esi <- address of place to store uint
#       call decimal2uint
#       returns 0

# Constants
        .equ    MASK, 0xf

# Stack frame
        .equ    sofar, -4
        .equ    localSize, -16

# decimal2uint.s
        .text
        .global decimal2uint
        .type   decimal2uint, @function

decimal2uint:
        pushq   %rbp
        movq    %rsp, %rbp
        addq    $localSize, %rsp

        movl    $0, sofar(%rbp)         # sofar = 0

        jmp     enterLoop

convertChar:
        movl    $10, %eax               # will be multiplying by 10
        mull    sofar(%rbp)             # sofar * 10
        movl    %eax, sofar(%rbp)       # store new value in sofar

        andl    $MASK, %r13d            # char -> int
        addl    %r13d, sofar(%rbp)      # add to sofar

        incq    %rdi                    # pointer to next char

enterLoop:
        movb    (%rdi), %r13b           # load character
        cmpb    $0, %r13b               # end of string?
        jne     convertChar

finish:
        movl    sofar(%rbp), %r12d      # load result
        movl    %r12d, (%rsi)           # store result in given address
        
        movq    %rbp, %rsp
        popq    %rbp

        movl    $0, %eax
        ret
