# Name: Aneeket Yadav
# Enrollment no. 2022CS11116
.data
    string1: .space 51   # Allocate space for a 50-character string and 1 null terminator
    string2: .space 11   # Allocate space for a 10-character string and 1 null terminator
    prompt1: .asciz "Enter your name: "
    prompt2: .asciz "Enter 10-letter alphanumeric string: "
    
.text
.global start

start:
    # Print prompt1
    la a0, prompt1
    li a7, 4
    ecall
    
    # Read string1
    la a0, string1
    li a1, 51       # Accept only the first 50 characters
    li a7, 8            # System call number for reading string
    ecall
    
    # Print prompt2
    la a0, prompt2
    li a7, 4
    ecall
    
    # Read string2
    la a0, string2
    li a1, 11    
    li a7, 8              
    ecall
	
	la a1, string1
	la a2, string2
	j print_string2
	
print_string1:
	beqz a0, string1_over
	
	lb a0, 0(a1)
	li a7, 11
	ecall 
	
	addi a1, a1, 1
	j print_string2
	
print_string2:
	beqz a0, string2_over
	
	lb a0, 0(a2)
	li a7, 11
	ecall
	
	addi a2, a2, 1
	j print_string1

string1_over:
	lb a0, 0(a2)
	beqz a0, terminate
	
	li a7, 11
	ecall 
	
	addi a2, a2, 1
	j string1_over
	
string2_over:
	lb a0, 0(a1)
	beqz a0, terminate
	
	li a7, 11
	ecall 
	
	addi a1, a1, 1
	j string2_over
	
terminate:
	li a7, 10
	ecall
