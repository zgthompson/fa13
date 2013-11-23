# Zachary Thompson
# November 22, 2013

# Stack frame
        .equ    theString, -11
        .equ    theInt, -16
        .equ    localSize, -16

# read only data

prompt:
        .string "Enter a number(less than 4294967295):\n"

message:
        .string "Your number plus one is: %u\n"

# main.s
        .text
        .globl  main
        .type   main, @function
main:
        pushq   %rbp
        movq    %rsp, %rbp
        addq    $localSize, %rsp

        movl    $prompt, %edi           # load prompt
        movl    $0, %eax                # no floats
        call    printf

        leaq    theString(%rbp), %rdi   # load address of theString
        movl    $11, %esi               # max size
        call    readLine

        leaq    theString(%rbp), %rdi   # load address of theString
        leaq    theInt(%rbp), %rsi      # load address of theInt
        call    decimal2uint

        addl    $1, theInt(%rbp)        # add one to user input

        movl    $message, %edi          # load message
        movl    theInt(%rbp), %esi      # load theInt
        movl    $0, %eax                # no floats
        call    printf

        movl    $0, %eax                # return 0
        movq    %rbp, %rsp
        popq    %rbp
        ret
