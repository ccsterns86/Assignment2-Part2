# This file helps in the editing mode. It prints only to the top line.
    .text
    
    .globl display_line
    
display_line:
    li t0,0xffff8000    # address of the graphics display

    lw t2,0(a0)         # load line (a word -> 32)
    sw t2,0(t0)         # write it to the corresponding line of the graphics display

    jr ra               # return 
    
