# Name: Aneeket Yadav
# Enrollment no. 2022CS11116
#************************************************************************************
#Instructions for entering 256-bit numbers
#1.Numbers must be converted to hex. 
#	Thus the number can be divided into 8 length-8 hex strings
#2.Enter the lower 8 digits(msb left,lsb right) i.e bits 31 downto 0, without presseing Enter-key, 
# 	continue to input such 8 length strings(63 downto 32, 95 downto 64,...)
#**********************************************************************************
.data 
	num1: .space 288
	num2: .space 288
	sum: .space 288
	wow: .asciz "wow"
	prompt1: .asciz "Enter num1: "
	prompt2: .asciz "Enter num2: "
	
.data
	string: .space 9
	binary_output: .word 0
	#prompt: .asciz "Enter 8 hex string: "
	
.text
enter_num_1:
	la a0, prompt1
	li a7, 4
	ecall

store_num1:
	li t4, 0 #j
	li a4, 57
	li t1, 4
#Block to accept hex string from user
#To be executed 8 times for each num
#begin num1 input
	start_1:
		la a0, string
    		li a1, 9
    		li a7, 8         
    		ecall
    
    		la a1, string
		li t0, 8

	distinguish_1:
		lbu a2, 0(a1)
		bleu a2, a4, number_1
		j alphabet_1

	number_1:
		addi a2, a2, -48
		sb a2, 0(a1)
		addi a1, a1, 1
		addi t0, t0, -1
		bnez t0, distinguish_1
		j compress_prep_1
	
	alphabet_1:
		addi a2, a2, -87
		sb a2, 0(a1)
		addi a1, a1, 1
		addi t0, t0, -1
		bnez t0, distinguish_1
		j compress_prep_1
	
	compress_prep_1:
		#At ith step, we need to extract the 4 lsbs of string[0],
		#left shift them by 4*i steps and OR it with main register
		li t0, 0		#i
		la a1, string 
		addi a1, a1, 7
		li a3, 0		#main register
		li t2, 0		#stores 4*i
		li t3, 8
	
	compress_1:
		lbu a2, 0(a1)
		mul t2, t1, t0
		sll a2, a2, t2
		or a3, a3, a2
	
		addi a1, a1, -1
		addi t0, t0, 1
		bne t0, t3, compress_1
	
		la a1, num1
		mul t5, t4, t1 
		add a1, a1, t5
		sw a3, 0(a1)
		addi t4, t4, 1
		bne t4, t3, start_1 # t3 = 8
#end num1 input
leave_line:
	li a0, '\n'
	li a7, 11
	ecall
enter_num_2:
	la a0, prompt2
	li a7, 4
	ecall

store_num2:
	li t4, 0 #j
	li a4, 57
	li t1, 4
#Block to accept hex string from user
#To be executed 8 times for each num
#begin num2 input
	start_2:
		la a0, string
    		li a1, 9
    		li a7, 8         
    		ecall
    
    		la a1, string
		li t0, 8

	distinguish_2:
		lbu a2, 0(a1)
		bleu a2, a4, number_2
		j alphabet_2

	number_2:
		addi a2, a2, -48
		sb a2, 0(a1)
		addi a1, a1, 1
		addi t0, t0, -1
		bnez t0, distinguish_2
		j compress_prep_2
	
	alphabet_2:
		addi a2, a2, -87
		sb a2, 0(a1)
		addi a1, a1, 1
		addi t0, t0, -1
		bnez t0, distinguish_2
		j compress_prep_2
	
	compress_prep_2:
		#At ith step, we need to extract the 4 lsbs of string[0],
		#left shift them by 4*i steps and OR it with main register
		li t0, 0		#i
		la a1, string 
		addi a1, a1, 7
		li a3, 0		#main register
		li t2, 0		#stores 4*i
		li t3, 8
	
	compress_2:
		lbu a2, 0(a1)
		mul t2, t1, t0
		sll a2, a2, t2
		or a3, a3, a2
	
		addi a1, a1, -1
		addi t0, t0, 1
		bne t0, t3, compress_2
	
		la a1, num2
		mul t5, t4, t1 
		add a1, a1, t5
		sw a3, 0(a1)
		addi t4, t4, 1
		bne t4, t3, start_2 # t3 = 8
#end num2 input
#*********************************************************************************
preparation_1:
	la a1,num1	#a1 contains the array cell address and
	li t0, 0		#t0 represents the iteration i
	li a3, 0		#a3 contains the transfer bits from previous word
	li t2, 0		#t2 contains tranfer bits extracted from the current word
	
	#bitmask
	li t3, 0x80000000
	li a4, 0x7fffffff
	#constants
	li t4, 32
	li t6, 8
	
rearrangement_1:
	#a2 contains the word stored in array[i]		
	#At each step, the number of bits increase by 1.
	#At the ith step, 0<=i<=7, i left shifts occur and (i+1) bits are transferred
	#In the final step, 8 bits are transferred to array[9]
	
	#We need to extract the upper (i+1) bits of array[i] and load them in t1.
	#We need a bitmask having (i+1)msb = 1 and rest of the bits 0.
	#Let t3 represent the bitmask.
	#At each step,we will arithmetically shift the bitmask right by 1 unit
	
	#load word
	lw a2, 0(a1)
	
	#extract msbs
	and t2, t3, a2
	
	#left shift word 
	sll a2, a2, t0
	
	#make left-most bit 0
	and a2, a2, a4
	
	#append incoming bits after shifting them by (32-i) positions
	#t5 contains (32-i)
	sub t5, t4, t0
	srl a3, a3, t5
	or a2, a2, a3
	
	mv a3,t2 
	
	#store word to memory
	sw a2, 0(a1)
	
	#arith. right shift bitmask
	srai t3, t3, 1
	
	#increment word address
	addi a1, a1, 4
	
	#increment computation step
	addi t0, t0, 1
	
	#loop
	bne t0, t6, rearrangement_1
	
num1_8:
	lw a2, 0(a1)
	#append most significant 8 bits
	srli a3, a3, 24
	or a2, a2, a3
	
	#store 
	sw a2, 0(a1)

#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
preparation_2:
	la a1,num2	#a1 contains the array cell address and
	li t0, 0		#t0 represents the iteration i
	li a3, 0		#a3 contains the transfer bits from previous word
	li t2, 0		#t2 contains tranfer bits extracted from the current word
	
	#bitmask
	li t3, 0x80000000
	li a4, 0x7fffffff
	#constants
	li t4, 32
	li t6, 8
	
rearrangement_2:
	#a2 contains the word stored in array[i]		
	#At each step, the number of bits increase by 1.
	#At the ith step, 0<=i<=7, i left shifts occur and (i+1) bits are transferred
	#In the final step, 8 bits are transferred to array[9]
	
	#We need to extract the upper (i+1) bits of array[i] and load them in t1.
	#We need a bitmask having (i+1)msb = 1 and rest of the bits 0.
	#Let t3 represent the bitmask.
	#At each step,we will arithmetically shift the bitmask right by 1 unit
	
	#load word
	lw a2, 0(a1)
	
	#extract msbs
	and t2, t3, a2
	
	#left shift word 
	sll a2, a2, t0
	
	#make left-most bit 0
	and a2, a2, a4
	
	#append incoming bits after shifting them by (32-i) positions
	#t5 contains (32-i)
	sub t5, t4, t0
	srl a3, a3, t5
	or a2, a2, a3
	
	mv a3,t2 
	
	#store word to memory
	sw a2, 0(a1)
	
	#arith. right shift bitmask
	srai t3, t3, 1
	
	#increment word address
	addi a1, a1, 4
	
	#increment computation step
	addi t0, t0, 1
	
	#loop
	bne t0, t6, rearrangement_2
	
num2_8:
	lw a2, 0(a1)
	#append most significant 8 bits
	srli a3, a3, 24
	or a2, a2, a3
	
	#store 
	sw a2, 0(a1)
#*********************************************************************************
#We have now rearranged the numbers in a form suitable for addition
#Perform addition:-

sum_prep:
	li t0, 9
	la a1, num1
	la a2, num2
	la a3, sum
	li t1, 0x80000000
	
summation:
	lw a4, 0(a1)
	lw a5, 0(a2)
	add a6, a4, a5
	sw a6, 0(a3)
	
    #Extract the msb using a bitmask, perform carry operation
    and a6, a6, t1
    srli a6, a6, 31
    
    #Increment addresses
    addi a1, a1, 4
    addi a2, a2, 4
    addi a3, a3, 4
    addi t0, t0, -1
    
    bnez t0, summation
    
#*********************************************************************************
#We now need to compress the result back from 9x32 words to 8x32 words.
rearrange_sum_prep:
	la a1, sum
	addi a1, a1, 32
	li t0, 8 #iteration 8>=i>=1
	lbu t1, 0(a1) #Stores the i bits being transferred to the word
	slli t1, t1, 24
	li t2, 0 #Stores the lower i-i bits being extracted from the word
	li t3, 127 #bitmask
	li t4, 33
	addi a1, a1, -4
rearrange_sum:
	#load word
	lw a2, 0(a1)
	
	#Extract the lower (i-i) bits
	and t2, a2, t3
	#Left shift them by (32-(i-1)) bits
	sub t5, t4, t0
	sll t2, t2, t5
	
	#logically right shift word by i-1 bits
	addi t5, t0, -1
	srl a2, a2, t5
	
	#cons the i bits from previous word
	or a2, a2, t1
	sw a2, 0(a1)
	mv t1,t2
	
	#adjust bitmask
	srli t3, t3, 1
	
	#adjust word address
	addi a1, a1, -4
	
	#decrement i
	addi t0, t0, -1
	
	#loop
	bnez t0, rearrange_sum
	
	#Overflow bit
	la a1, sum
	addi a1, a1, 32
	lw a2 0(a1)
	srli a2, a2, 8
	sw a2, 0(a1)
	
	li a7, 10
	ecall
	
	
	
	 
	
