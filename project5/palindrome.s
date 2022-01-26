main:
        irmovl 0x1000, %esp
        
        irmovl 20, %ebx
        irmovl 1, %esi

        irmovl 0, %ecx
        pushl %ecx

        irmovl 10, %eax
        irmovl Array, %edi

loop:
        rdch %ecx
        
        irmovl $10, %esi
        subl %ecx, %esi

        je next

        popl %ecx
        addl %esi, %ecx
        pushl %ecx

        subl %esi, %ebx
        je next

        irmovl 4, %ecx
        addl %ecx, %edi

        jmp loop

next: 
        popl %edx
        
        rrmovl %edx, %ecx
        subl %esi, %ecx

        irmovl 2, %eax
        divl %eax, %edx
        je endif
        
        irmovl $4, %eax
        multl %eax, %ecx

        irmovl Array, %eax
        irmovl Array, %abx
        addl %ecx, %ebx

secondloop:
        mrmovl 0(%eax), %ecx
        mrmovl 0(%ebx), %edi

        subl %ecx, %edi
        jne endif2

        irmovl $4, %ecx
        addl %ecx, %eax
        subl %ecx, %ebx

        subl %esi, %edx
        je endif

        jmp secondloop

endif2:
        rrmovl %esp, %ebp
        irmovl 78, %eax
        wrch %eax
        jmp end

endif:
        rrmovl %esp, %ebp
        irmovl 89, %eax
        wrch %eax

end:
        irmovl 10, %eax
        wrch %eax
        halt

        .align 4

Array:  .long 0