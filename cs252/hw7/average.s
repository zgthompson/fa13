# Zachary Thompson
# December 2, 2013

# Stack frame
        .equ    intArray, -40
        .equ    localSize, -48

# read only data

prompt:
        .string "Enter 10 integers:\n"

oneInt:
        .string "%d"

message:
        .string "The average is: %f\n"

# main.s
        .text
        .globl  main
        .type   main, @function

main:
        pushq   %rbp
        movq    %rsp, %rbp
        addq    $localSize, %rsp

        movl    $prompt, %edi               #load prompt
        movl    $0, %eax                    # no floats
        call    printf

        movq    $0, %r12                    # counter = 0
        leaq    intArray(%rbp), %r13        # pointer to array
        jmp     readCheck

readInt:
        leaq    (%r13, %r12, 4), %rsi       # load current array address
        movl    $oneInt, %edi               # get one int
        movl    $0, %eax                    # no floats
        call    scanf

        incq    %r12                        # counter++

readCheck:
        cmpq    $10, %r12                   # counter < 10 ?
        jl      readInt

        movq    $0, %r12                    # reset counter
        movl    $0, %eax                    # accumulater = 0
        jmp     sumCheck

sumInt:
        addl    (%r13, %r12, 4), %eax       # add current index to accumulator
        incq    %r12                        # counter++
        
sumCheck:
        cmpq    $10, %r12                   # counter < 10 ?
        jl      sumInt

        movl    $10, %ebx                   # divisor = 10

        cvtsi2sd    %eax, %xmm0             # convert to double
        cvtsi2sd    %ebx, %xmm1             # convert to double

        divsd   %xmm1, %xmm0                # divide 

        movl    $message, %edi              # load message
        movl    $1, %eax                    # 1 float
        call    printf

        movl    $0, %eax                    # return 0
        movq    %rbp, %rsp
        popq    %rbp
        ret
        

