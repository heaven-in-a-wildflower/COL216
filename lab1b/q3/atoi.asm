#Name:Aneeket Yadav
#Enrollment no.2022CS11116
.data
    prompt_1:	.asciz "Enter first ASCII string: "
    prompt_2:	.asciz "Enter second ASCII string: "
    prompt_op:	.asciz "Enter opcode(a,s,m,d): "
    #error_msg:	.asciz "Invalid operation, program aborted"	
    num_1: .word 0
    num_2: .word 0
	buffer: .space 12  # Allocate space for the input string
.text
    .global main

main:
	la a1, prompt_1
	li a2, 27          # Length of the prompt string
	jal ra, print_prompt
	jal ra, read_string
	
    la a0, buffer       # Address of the ASCII string
    la a1, num_1
    jal ra, ascii_to_decimal
    	#num_1 ready
    	
	la a1, prompt_2
	li a2, 28          # Length of the prompt string
	jal ra, print_prompt
	jal ra, read_string
	
    la a0, buffer       # Address of the ASCII string
    la a1, num_2
    jal ra, ascii_to_decimal
	#num_2 ready

	la a1, prompt_op
	li a2, 23
	jal ra, print_prompt
	jal ra, read_string
	
	jal ra, operation
	
	#Print result
	li a7, 1
	ecall
	
	li a7, 10
	ecall
	
print_prompt:
    li a0, 1		# File descriptor: STDOUT   
    li a7, 64         
    ecall
    ret

read_string:
    li a0, 0		# File descriptor: STDIN
    la a1, buffer       
    li a2, 12	# Maximum number of characters to read
    li a7, 63          
    ecall
    ret

# Function to convert ASCII string to decimal number
ascii_to_decimal:
    # Function prologue
    li t0, 0            # Initialize result to 0
    li t1, 1            # Initialize sign to positive

    lbu t2, 0(a0)       # Load the first character
    
    # Check for minus sign
    li t3, 45           # ASCII code for minus sign
    bne t2, t3, not_negative

    # If the first character is '-', set the sign to negative
    li t1, -1
    li t3 10
    addi a0, a0, 1      # Move to the next character
    j convert_loop
 
not_negative:
	li t3 10
    convert_loop:
        lbu t2, 0(a0)       # Load the next ASCII character
        beq t2,t3,convert_done  # If null terminator, exit the loop

        addi t2, t2, -48     # Convert ASCII character to integer
        mul t0, t0, t3      # Multiply result by 10
        add t0, t0, t2      # Add the new digit

        addi a0, a0, 1      # Move to the next character
        j convert_loop

    convert_done:
        # Multiply the result by the sign
        mul a0, t0, t1
  		sw a0 0(a1)
        ret

operation:
	li t0, 97 	#ASCII value of 'a' for add
	li t1, 115	#ASCII value of 's' for sub
	li t2, 109	#ASCII value of 'm' for mul
	li t3, 100	#ASCII value of 'd' for div
	
	la a0, num_1
	lw a1, 0(a0)
	
	la a0, num_2
	lw a2, 0(a0)
	
	la a0, buffer
	lbu t4, 0(a0)       # Load the first character
	beq t4,t0,addop
	beq t4,t1,subop
	beq t4,t2,mulop
	beq t4,t3,divop
	
	addop:
		add a0,a1,a2
		ret 
	subop:
		sub a0,a1,a2
		ret
	mulop:
		mul a0,a1,a2
		ret
	divop:
		div a0,a1,a2
		ret
	

	

