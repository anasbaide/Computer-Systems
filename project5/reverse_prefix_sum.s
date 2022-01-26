#Ana Baide
#Grace: abaide
#UID: 118441368

reverse_prefix_sum:
	#PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

    lw $t0,0($a0)

    beq $t0,-1, base0      #checking for base case

    subu $sp, $sp, 4      #making space 
    sw $a0, 4($sp)        #putting elemnet
    addu $a0,$a0,4        #moving to the next element
 
    jal reverse_prefix_sum    #recursive call

    lw $a0,4($sp)          #getting address
    lw $t0,0($a0)          #getting address
    addu $v0,$v0,$t0       #adding next element

    sw $v0,0($a0)          #storing in next bit available
    j exit      #finish loop

base0:
    li $v0, 0    #return 0
    j exit       #finish loop

exit:
    #EPILOGUE 
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra                # return to kernel