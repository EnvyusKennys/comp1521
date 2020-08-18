# read a number n and print the integers 1..n one per line

main:                           # int main(void)
    la      $a0, prompt         # printf("Enter a number: ");
    li      $v0, 4
    syscall

    li      $v0, 5              # scanf("%d", number);
    syscall

    # li  $a0, 42               # printf("%d", 42);
    # li  $v0, 1
    # syscall

    move	$t0, $v0 		    # $t0 = number
    li		$t1, 1 		        # $t1 = i;
    

loop:
    bgt		$t1, $t0, end	    # if i > number then branch out
    move	$a0, $t1		    # printf("%d", i);
    li		$v0, 1	
    syscall

    li      $a0, '\n'           # printf("%c", '\n');
    li      $v0, 11
    syscall
    
    add		$t1, $t1, 1		    # $t1 = $t1 + $t1
    j       loop

end:
    jr  $ra                     # return

    .data
prompt:
    .asciiz "Enter a number: "
