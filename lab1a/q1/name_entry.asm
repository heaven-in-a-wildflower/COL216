.data
	name: .asciz "Aneeket"
	entry: .asciz "2022CS11116"
.text
print:
	la a0, name
	li a7, 4
	ecall
	
	li a0, '\n'
	li a7, 11
	ecall
	
	la a0, entry
	li a7, 4
	ecall
	
	li a7, 10
	ecall