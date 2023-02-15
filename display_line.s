# This file helps in the editing mode. It prints only to the top line.
    .text
    
    .globl display_line
    
display_line:           # has 2 parameters, the displayline (an int), and number of the line (1-32)
    li t0,0xffff8000    # address of the graphics display

    li s1, 4
    mul t2, a1, s1      # get the offset for the graphics line
    add t0, t0, t2      # address of the graphics line

    lw t1, 0(a0)        # get the contents of the line we want to display
    sw t1,0(t0)         # write it to the corresponding line of the graphics display

    jr ra               # return 
    
