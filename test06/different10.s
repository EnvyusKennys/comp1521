# x in register $t0
# i in register $t1
# n_seen in register $t2
# registers $t3 and $t4 used to hold temporary results
main:

    li $t2, 0           # n_seen = 0;
start:
    bge $t2, 10, end    # while (n_seen < 10) {
    la $a0, string0     # printf("Enter a number: ");
    li $v0, 4
    syscall
    li $v0, 5           # scanf("%d", &x);
    syscall
    li  $t5, 0          # i = 0
    la $t4, numbers
    move $t0, $v0     
loop0:
    bge $t5, $t2, out   # i >= n_seen
    mul $t3, $t5, 4
    add $t3, $t3, $t4
    lw  $t6, ($t3)
    beq $t6, $t0, out
    add $t5, $t5, 1
    b  loop0
out:

    bne $t5, $t2, inc
    mul $t3, $t2, 4     # calculate &numbers[n_seen]

    add $t3, $t3, $t4   #
    sw $t0, ($t3)       # numbers[n_seen] = x

    add $t2, $t2, 1     # n_seen++;
    
inc:
    b start



end:
    la $a0, string1     # printf("10th different number was: ");
    li $v0, 4
    syscall

    move $a0, $t0       # printf("%d", x)
    li $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    li $v0, 0           # return 0
    jr $31

    .data

numbers:
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "10th different number was: "
