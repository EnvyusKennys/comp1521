# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall

    blt		$v0, 50, markfl	# if $v0 < 50 then marked as fl
    blt		$v0, 65, markps	# if $v0 < 65 then marked as ps
    blt		$v0, 75, markcr	# if $v0 < 75 then marked as cr
    blt		$v0, 85, markdn	# if $v0 < 85 then marked as dn
    j		markhd			# if $v0 > 85 then marked as hd


markfl:
    la $a0, fl          # printf("FL\n");
    li $v0, 4
    syscall 
    j end

markps:
    la $a0, ps          # printf("PS\n");
    li $v0, 4
    syscall
    j end

markcr:
    la $a0, cr          # printf("CR\n");
    li $v0, 4
    syscall
    j end

markdn:
    la $a0, dn          # printf("DN\n");
    li $v0, 4
    syscall
    j end

markhd:
    la $a0, hd          # printf("HD\n");
    li $v0, 4
    syscall

end:
    jr $ra              # return

    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
