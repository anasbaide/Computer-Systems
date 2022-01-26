#Ana Baide
#Grace: abaide
#UID: 118441368

is_palindrome:
	#PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

	sub $sp, $sp, 4 	#allocate memory in the stack
	sw $a0, 0($sp) 		#store the arg value

##################STRLEN##################
	strlen:
   		li $v0, 0

   	loop_strlen:
    	lb $t1, 0($a0)
    	beqz $t1, finish
    	add $v0, $v0, 1
    	add $a0, $a0, 1
    	j loop_strlen

	finish:
		move $t0, $v0 		#move the result to temp space

##################STRLEN##################

	lw $a0 0($sp) 		#load argument
	move $t1, $a0 		#save its value to t1

	li $t2, 0 		#set the counter to 0
	li $v0, 1 		#set the return value to 1
	add $s1, $a0, $t2  #point to the character
	lb $t6, 0($s1)      #set the pointer

	div $t3, $t0, 2     #divide the string length

	sub $t4, $t0, $t2   #reduce the counter
	sub $t4, $t4, 1     #calculate last char
	add $s3, $t1, $t4    
	lb $t7, 0($s3)         #set the pointer 

	loop_palindrome:			
		bge $t2, $t3 exit 	#when counter equals strlen/2

		bne $t6, $t7, return_false  #finish program if not pali
		add $t2, $t2, 1      #increase counter
		add $s1, $t1, $t2      #change pointer
		lb $t6, 0($s1)

		sub $t4, $t0, $t2    #subtract position
		sub $t4, $t4, 1      
		add $s3, $t1, $t4    #change pointer
		lb $t7, 0($s3)

		j loop_palindrome    #recursive call

return_false:
	li $v0, 0     #set return val to 0

exit: 
    #EPILOGUE 
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra                # return to kernel