# Name: Aneeket Yadav
# Enrollment no. 2022CS11116
.data
arr:    .space 40          
prompt: .asciz "Enter integer #"
result_prompt: .asciz "Sum of 10 integers: "

.text
_start:
    # Initialize variables
    la a1, arr	
    li t0, 10   
    li t2, 0  

    # Input Loop
input_loop:
    # Print prompt
    li a7, 4               
    la a0, prompt           
    ecall

    #Read integer input
    li a7, 5                # System call number for reading integer
    ecall
    
    sw a0, 0(a1)           
    addi a1, a1, 4         

    addi t0, t0, -1        
    bnez t0, input_loop    

    #Sum Loop
    la a1, arr             
    li t0, 10               
    li t2, 0                

sum_loop:
    lw a0, 0(a1)           
    add t2, t2, a0          
    addi a1, a1, 4          

    addi t0, t0, -1         
    bnez t0, sum_loop      

    #Print sum
    li a7, 4               
    la a0, result_prompt   
    ecall

    li a7, 1               
    mv a0, t2               
    ecall

    # Exit the program
    li a7, 10              
    ecall
