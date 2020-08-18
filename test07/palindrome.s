# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li   $t0, 0           # i = 0
    la   $t1, line

loop:
    add  $t2, $t1, $t0
    lb   $t2, ($t2)
    beqz $t2, out 
    add  $t0, $t0, 1
    b    loop

out:
    li   $t2, 0          # j = 0
    sub  $t3, $t0, 2     # k = i - 2

loop2:
    bgt  $t2, $t3, p
    add  $t4, $t1, $t2
    add  $t5, $t1, $t3
    lb   $t4, ($t4)
    lb   $t5, ($t5)
    bne  $t4, $t5, notp
    add  $t2, $t2, 1
    sub  $t3, $t3, 1
    b    loop2
    
notp:
    la   $a0, not_palindrome
    li   $v0, 4
    syscall
    b    return

p:
    la   $a0, palindrome
    li   $v0, 4
    syscall

return:
    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

