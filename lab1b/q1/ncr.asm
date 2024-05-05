#Name:Aneeket Yadav
#Enrollment no.2022CS11116
.data
	prompt1: .asciz "Enter n: "
	prompt2: .asciz "Enter r: "
	n: .word 0
	r: .word 0
	fact_n: .space 8
	fact_r: .space 8
	result_msg: .asciz "The answer is: "
.text
start:
#Input n from the user
	la a0, prompt1
	li a7, 4
	ecall
	
	li a7, 5
	ecall

	#a0 = n now
		
	#Store n to memory
	la a2, n
	sw a0, 0(a2)
	
	li a1, 0		
	ble a0, a1, zero_n
	li a3, 1
#nCr = n!/((n-r)!*r!)

compute_fact_n_non_trivial:
	#Termination
	beq a1, a0, input_r 

	#Inductive method
	addi a2, a1, 1 # a2 = i
	mul a3, a3, a2 #t3 = 1*2*...*(i)
	
	#Increment i
	addi a1, a1, 1	
	j compute_fact_n_non_trivial

input_r:
	#First store the result of fact(n) to memory so that a3 is freed.
	la a2, fact_n
	sd a3 0(a2)
	
	#Input r from the user
	la a0, prompt2
	li a7, 4
	ecall
	li a7, 5
	ecall
	
	#Store r to memory
	la a2, r
	sw a0, 0(a2)
	
	#a0 = r now
	la a2, n
	lw a1, 0(a2)
	
	#Terminate computation if n<r
	blt a1, a0, terminate

	#(n-r=0) <=> r=0
	beq a1, a0, zero_r
		 
	li a1, 0		#i
	li a3, 1
	
compute_fact_r_non_trivial:
	#Termination
	beq a1, a0, n_minus_r 
	
	#Inductive method
	addi a2, a1, 1 # a2 = i
	mul a3, a3, a2 #t3 = 1*2*...*(i)
	
	#Increment i
	addi a1, a1, 1
	
	j compute_fact_r_non_trivial
n_minus_r:
	#First store the result of fact(r) to memory so that a3 is freed.
	la a2, fact_r
	sd a3, 0(a2)
	
	#Find n-r
	la a3, n
	lw a1, 0(a3)
	
	la a3, r
	lw a2, 0(a3)
	sub a0, a1, a2
	
	#Trivial cases have been already addressed i.e n-r >= 1.
	li a1, 0		#i
	li a3, 1
	
compute_fact_n_minus_r:
	#Termination
	beq a1, a0, compute_nCr 	#Explanation of efficiency

	#Inductive method
	addi a2, a1, 1 # a2 = i
	mul a3, a3, a2 #t3 = 1*2*...*(i)
	
	#Increment i
	addi a1, a1, 1
	
	j compute_fact_n_minus_r
	
compute_nCr:
	#a3 = (n-r)!
	la a0, fact_n
	ld a1, 0(a0)
	
	la a0, fact_r
	ld a2, 0(a0)
	
	mul a3, a2, a3 #a2 = r! * (n-r)!
	div a3, a1, a3 #a1 = nCr
	j terminate
		
zero_n:
	#nCr = 0
	li a3, 0
		
zero_r:
	#nCr = 1
	li a3, 1

terminate:		
	la a0, result_msg
	li a7, 4
	ecall
	
	#In each case, a3 constains final answer
	mv a0, a3
	li a7, 1
	ecall
	
	li a7, 10
	ecall
	

	
	
	
	
	  
	
