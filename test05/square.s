main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0           # i = 0
loop1:
    bge $t1, $t0, end
    li $t2, 0           # j = 0
loop2:
    bge $t2, $t0, out
    li $a0, '*'         
    li $v0, 11
    syscall
    addi $t2, $t2, 1
    b loop2
out:
    addi $t1, $t1, 1
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    b loop1
end:

    li $v0, 0           # return 0
    jr $31
