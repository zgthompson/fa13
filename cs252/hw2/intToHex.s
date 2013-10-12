# Stack frame
        .equ    anInt,-4
        .equ    localSize,-16

# Read only data
        .section .rodata
prompt:
        .string "Enter an integer number: "
scanFormat:
        .string "%i"
printFormat:
        .string "You entered: %x\n"

testFormat:
        .string "%x\n"

#Code
        .text
        .globl  main
        .type   main, @function

main:
        pushq   %rbp                # save caller's frame pointer
        movq    %rsp, %rbp          # establish frame pointer
        addq    $localSize, %rsp    # allocate space for local variable

        movl    $prompt, %edi       # load prompt as first argument
        movq    $0, %rax            # no floating point args
        call    printf              # invoke printf function

        movl    $scanFormat, %edi   # load format as first argument
        leaq    anInt(%rbp), %rsi   # address to store location as second argument
        movq    $0, %rax            # no floating point args
        call    scanf               # invoke scanf function

        movl    $printFormat, %edi  # load format as first argument
        movl    anInt(%rbp), %esi   # value of anInt as second argument
        movq    $0, %rax            # not floating point args
        call    printf              # invoke printf function

        movl    $0, %eax            # load 0 for return value
        movq    %rbp, %rsp          # delete local variables
        popq    %rbp                #restore caller's frame pointer
        ret

