# Zachary Thompson
# November 15, 2013

# Stack frame
        .equ    theString, -256
        .equ    localSize, -256
# read only data
        .section .rodata
prompt:
        .string "Enter a text string:\n"
message:
        .string "You entered:\n"
newLine:
        .string "\n"

# main.s
        .text
        .globl main
        .type main, @function
main:
        pushq   %rbp
        movq    %rsp, %rbp
        addq    $localSize, %rsp

        movl    $prompt, %edi           # load prompt
        movl    $0, %eax                # no floats
        call    printf

        leaq    theString(%rbp), %rdi   # load address of theString
        movl    $10, %esi                # max size 2 chars
        call    readLine

        movl    $message, %edi          # load message
        movl    $0, %eax                # no floats
        call    printf

        leaq    theString(%rbp), %rdi   # load theString
        movl    $0, %eax                # no floats
        call    printf

        movl    $newLine, %edi          # load newLine
        movl    $0, %eax                # no floats
        call    printf

        movl    $0, %eax                # return 0
        movq    %rbp, %rsp
        popq    %rbp
        ret
