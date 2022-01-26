#Ana Baide
#Grace: abaide
#UID: 118441368

isqrt:
	#PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

	#BODY
	subu $sp, $sp, 4        
	sw $a0, 4($sp)         #storing the passed value

	blt $a0, 2, basesqrt   #checking for the base case

	srl $a0, $a0, 2        #moving 2 bytes (n>>2)
	jal isqrt              #recursive
	sll $v0, $v0, 1        #assigning small

	lw $t0, 4($sp)        #writing arg
	add $t1, $v0, 1       #adding to small

	mul $t2, $t1, $t1    #checking next condition large * large

	bgt $t2, $t0, return_small   #if statement
	move $v0, $t1    #return large is false
	j exit

	basesqrt:
		move $v0, $a0   #return if n < 2

	return_small:
	exit:
		#EPILOGUE 
		move $sp, $fp           # restore $sp
		lw   $ra, ($fp)         # restore saved $ra
		lw   $fp, -4($sp)       # restore saved $fp
		j    $ra                # return to kernel