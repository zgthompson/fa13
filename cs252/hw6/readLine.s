# Zachary Thompson
# November 15, 2013

# Calling sequence:
#       rdi <- address of place to store string
#       esi <- maximum size of string (must be 1 or greater)
#       call readLine
#       returns number of characters read (not including NUL)

# Constants
        .equ    STDIN,0
# Stack frame
        .equ    str, -16
        .equ    dummyChar, -4
        .equ    count, -4
        .equ    localSize,-16

# Read only data
        .section .rodata
readChar:
        .string "%c"

# readLine.s
        .text
        .globl  readLine
        .type   readLine, @function
readLine:
        pushq   %rbp
        movq    %rsp, %rbp
        addq    $localSize, %rsp

        movq    %rdi, str(%rbp)         # pointer to string
        movl    %esi, %r12d             # max size of string
        movl    $0, count(%rbp)         # count = 0

        jmp     getChar                 # get first char

continueLoop:
        incl    count(%rbp)             # count++
        cmpl    %r12d, count(%rbp)      # count less than max size?
        je      throwAway               # throw away remaining stream

        incq    str(%rbp)               # str++ move to next char address

getChar:
        
        movl    $1, %edx                # read one character
        movq    str(%rbp), %rsi         # storage area
        movl    $STDIN, %edi            # read from keyboard
        call    read

        movq    str(%rbp), %rax         # pointer to cur char
        cmpb    $'\n', (%rax)           # new line character?
        jne     continueLoop 

overwrite:
        movq    str(%rbp), %rax         # pointer to cur char
        movb    $0, (%rax)              # override newline with NUL char
        jmp     finish

throwAway:
        leaq    dummyChar(%rbp), %rsi   # &dummyChar
        movl    $readChar, %edi          # get one char
        movl    $0, %eax                # no floats
        call    scanf

        cmpb    $'\n', dummyChar(%rbp)  # check for new line
        jne     throwAway
        jmp     overwrite

finish:
        movl    count(%rbp), %eax       # return count
        movq    %rbp, %rsp
        popq    %rbp
        ret
