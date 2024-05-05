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
	li a1, 0
	#sum(p,acc) = sum(p-1,acc+p)
	#a0 = n
	#acc:a1 
tail_rec_sum:
	beqz a0, terminate
	add a1, a0, a1
	addi a0, a0, -1
	j tail_rec_sum
terminate:
	rdcycle t1
	sub t2, t1, t0
	mv a0 a1
	li a7, 1
	ecall
	
	li a7, 10
	ecall
	
