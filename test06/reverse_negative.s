# Read numbers into an array until a negative number is entered
# then print the numbers in reverse order

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

main:
    li $t0, 0           # i = 0
loop0:
    bge $t0, 1000, loop1 # while (i < 1000) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    blt $v0, 0, loop1
    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
loop1:
    ble $t0, 0, end0
    sub $t0, $t0, 1
    mul  $t1, $t0, 4
    add  $t3, $t1, $t2
    lw   $t4, ($t3)
    move $a0, $t4       # printf("%d", number[i]);
    li   $v0, 1
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall
 

    b loop1
end0:

    li $v0, 0           # return 0
    jr $31              #

.data
numbers:
    .space 4000
