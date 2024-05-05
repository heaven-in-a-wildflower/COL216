#Name:Aneeket Yadav
#Enrollment no.2022CS11116
.data
	prompt: .asciz "Enter n: "
.text
start:
	la a0, prompt
	li a7, 4
	ecall
	
	li a7, 5
	ecall
	
	rdcycle t0
	#a0 = n now
    li a1, 0          # sum = 0
    li a2, 1          # i = 1
loop:
    bgt a2, a0, terminate
    add a1, a1, a2   
    addi a2, a2, 1    
    j loop            
terminate:
	rdcycle t1
	sub t2 t1 t0
	mv a0 a1
	li a7, 1
	ecall
	
	li a7, 10
	ecall
	
