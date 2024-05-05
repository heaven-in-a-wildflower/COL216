# Name: Aneeket Yadav
# Enrollment no. 2022CS11116
#To find the nth fibonacci number, n>=1?
.data 
	prompt: .asciz "Enter n (F0 = 0): "
	result_msg: .asciz "Nth Fibonacci number is: "
	
.text
start:
	la a0, prompt
	li a7, 4
	ecall
	
	li a7, 5
	ecall
	
	mv t0, a0
	addi t0, t0, -1 #Require n-1 steps to obtain fib(n)
	
	li a1,0
	li a2,1

compute:
	beqz t0, print_result
	add a3, a1, a2
	mv a1, a2
	mv a2, a3
	addi t0, t0, -1
	j compute

print_result:
	la a0, result_msg
	li a7, 4
	ecall
	
	mv a0, a3
	li a7, 1
	ecall
	
	li a7, 10
	ecall
	
	
	

	
