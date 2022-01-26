#Ana Baide
#Grace: abaide
#UID: 118441368

fibonacci:
     #PROLOGUE
     subu $sp, $sp, 8        # expand stack by 8 bytes
     sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
     sw   $fp, 4($sp)        # push $fp (4 bytes)
     addu $fp, $sp, 8        # set $fp to saved $ra

     #BODY
     beqz $a0, basefibo0           #return 0
     beq $a0, 1, basefibo1        #return 1
   
     sub $sp, $sp, 4             #make space to save the location
     sw $ra, 0($sp)              
   
     sub $a0, $a0, 1             #subtract 1 from n 
     jal fibonacci               #call fibonacci on n - 1

     lw $ra, 0($sp)             #remove space save for the location
     add $sp, $sp, 4            

     sub $sp, $sp, 4            #Store the result of fibonnaci(n-1)
     sw $v0, 0($sp)

     sub $sp, $sp, 4            #make space to save the location
     sw $ra, 0($sp)

     sub $a0, $a0, 1            #subtract 2 from n
     jal fibonacci              #call fibonacci on n - 2
     add $a0, $a0, 2            #add 2 again to n

     lw $ra, 0($sp)            #remove space save for the location
     add $sp, $sp, 4

     lw $s1, 0($sp)            #store the result of fibonacci(n-2)
     add $sp, $sp, 4

     add $v0, $v0, $s1         #move everything to $v0 to return

     j exit

     basefibo0:
          li $v0, 0
          j exit

     basefibo1:
          li $v0, 1
          j exit

     exit:
          #EPILOGUE 
          move $sp, $fp           # restore $sp
          lw   $ra, ($fp)         # restore saved $ra
          lw   $fp, -4($sp)       # restore saved $fp
          j    $ra                # return to kernel
        