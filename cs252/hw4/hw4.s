# Zachary Thompson
# November 8, 2013

# Stack frame
        .equ    ch, -1
        .equ    localSize, -16

# Read only data

        .section .rodata
instructions:
        .string "A single numeral, N, is echoed N+1 times, other characters are echoed once. 'q' ends program.\n"
prompt:
        .string "Enter a single character: "
getData:
        .string " %c"               # the space before %c causes scanf to ignore whitespace
display:
        .string "You entered: %c\n"
end:
        .string "End of program.\n"

# main.s
        .text
        .globl  main
        .type main, @function
main:
        pushq   %rbp                # save calling function's frame pointer
        movq    %rsp, %rbp          # establish our frame pointer
        addq    $localSize, %rsp    # for local vars

        movl    $instructions, %edi       # load instructions
        movl    $0, %eax            # no floats
        call    printf

        jmp     promptUser

displayResults:
        movq    $1, %r12            # set counter to 1
        cmpb    $'0', ch(%rbp)
        jl      charPrint           # print if char is lower than a  number

        cmpb    $'9', ch(%rbp)
        jg      charPrint           # print if char is higher than a number

        movzbq  ch(%rbp), %r12      # move ch into r12 and sign extend 0
        subq    $'0', %r12          # subtract the char 0
        incq    %r12                # add 1 to counter

charPrint:
        movb    ch(%rbp), %sil      # load byte to print
        movl    $display, %edi      # load display
        movl    $0, %eax            # no floats
        call    printf

        decq    %r12                # counter--
        cmpq    $0, %r12            # counter at 0
        jne     charPrint           # print again 

promptUser:
        movl    $prompt, %edi       #load prompt
        movl    $0, %eax            # no floats
        call    printf

        leaq    ch(%rbp), %rsi      # &ch
        movl    $getData, %edi      # get user data
        movl    $0, %eax            # no floats
        call    scanf

        cmpb    $'q', ch(%rbp)      # was it 'q'
        jne     displayResults      # show results

finish:
        movl    $end, %edi          # ending prompt
        movl    $0, %eax            # no floats
        call    printf

        movq    %rbp, %rsp          # delete local variables and reg. save area
        popq    %rbp                # restor calling function's frame pointer

        ret
