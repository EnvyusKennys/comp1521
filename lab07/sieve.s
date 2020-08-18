# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:

    # PUT YOUR CODE
    li $t0, 0           # i = 0
    la $t1, prime
   
loop1:
    bge $t0, 1000, out1
    li  $t2, 1
    add $t3, $t0, $t1
    sb  $t2, ($t3)

    addi $t0, $t0, 1
    b loop1  
out1:  
    
    li $t0, 2           # i = 2
    
loop2:
    bge $t0, 1000, out2
    add $t3, $t0, $t1
    lb  $t2, ($t3)
    li  $t4, 1
    bne $t2, $t4, inc

    move $a0, $t0
    li  $v0, 1
    syscall

    li  $a0, '\n'
    li  $v0, 11
    syscall

    mul $t4, $t0, 2

loop3:
    bge $t4, 1000, inc
    add $t5, $t4, $t1
    li  $t6, 0
    sb  $t6, ($t5)
    add $t4, $t4, $t0
    b loop3

inc:
    addi $t0, $t0, 1
    b loop2
out2:
    
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000