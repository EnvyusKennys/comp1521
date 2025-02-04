# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

# i in register $t0,
# registers $t1 - $t3 used to hold temporary results

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:
    li $t0, 1           # i = 1
loop1:
    bge $t0, 10, end1
    mul $t3, $t0, 4
    add $t3, $t3, $t2
    lw  $t6, ($t3)      # x

    sub $t4, $t0, 1
    mul $t5, $t4, 4
    add $t5, $t5, $t2
    lw  $t7, ($t5)      # y
    bge $t6, $t7, branch
    move $t8, $t6
    sw  $t7, ($t3)
    sw  $t8, ($t5)

branch:
    add $t0, $t0, 1     #  i++
    b loop1             # }

end1:
    li $t0, 0           # i = 0

loop2:
    bge $t0, 10, end2   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop2            # }
end2:

    jr $31              # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

