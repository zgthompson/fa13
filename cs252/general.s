# general.s
        .text
        .globl  general
        .type   general, @function
general:
        pushq   %rbp        # save calling function's frame pointer
        movq    %rsp, %rbp  # establish our frame pointer

# 1. Allocate memory for local variables andsaving registers,
#    ensuring that the address in rsp is a multiple of 16
# 2. Save the contents of general purpose registers that must be
#    preserved and are used in this function

# 3. The code that implements the function goes here.

# 4. Restore the contents of the general purpose registers that
#    were saved in stop 2.
# 5. Place the return value, if any, in the eax register.

        movq    %rbp, %rsp  # delete local variables and reg. save area
        popq    %rbp        # restor calling function's frame pointer

        ret
