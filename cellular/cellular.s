########################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
#
# Written by Yijie Shen, July 2020.


# Maximum and minimum values for the 3 parameters.

MIN_WORLD_SIZE	=    1
MAX_WORLD_SIZE	=  128
MIN_GENERATIONS	= -256
MAX_GENERATIONS	=  256
MIN_RULE	=    0
MAX_RULE	=  255

# Characters used to print alive/dead cells.

ALIVE_CHAR	= '#'
DEAD_CHAR	= '.'

# Maximum number of bytes needs to store all generations of cells.

MAX_CELLS_BYTES	= (MAX_GENERATIONS + 1) * MAX_WORLD_SIZE

	.data

# `cells' is used to store successive generations.  Each byte will be 1
# if the cell is alive in that generation, and 0 otherwise.

cells:	.space MAX_CELLS_BYTES


# Some strings you'll need to use:

prompt_world_size:	.asciiz "Enter world size: "
error_world_size:	.asciiz "Invalid world size\n"
prompt_rule:		.asciiz "Enter rule: "
error_rule:		.asciiz "Invalid rule\n"
prompt_n_generations:	.asciiz "Enter how many generations: "
error_n_generations:	.asciiz "Invalid number of generations\n"

	.text

	# $s0 -> world size
	# $s1 -> rule
	# $s2 -> generation
	# $s3 -> reverse
	# $s4 -> g for passing into the print_generation
	# $a0 -> g for passing into the func
	# $a1 -> world_size
	# $a2 -> rule
	
main:

    sub $sp, $sp, 20
    sw  $ra, 16($sp)
    sw  $s3, 12($sp)    # inverse
    sw  $s2, 8($sp)     # gen
    sw  $s1, 4($sp)     # rule
    sw  $s0, 0($sp)     # world_size

	la	$a0, prompt_world_size
	li  $v0, 4
	syscall				# printf("Enter world size: ");

	li  $v0, 5
	syscall				# scanf("%d",&n)

	blt $v0, MIN_WORLD_SIZE, InvalidSize   # printf('invalid...')
	bgt $v0, MAX_WORLD_SIZE, InvalidSize
	move $s0, $v0       # s0 = world_size

	la	$a0, prompt_rule
	li  $v0, 4
	syscall				# printf("Enter rule: ");
	
	li  $v0, 5
	syscall				# scanf("%d",&n)

	blt $v0, MIN_RULE, InvalidRule   # printf('invalid...')
	bgt $v0, MAX_RULE, InvalidRule
	move $s1, $v0		# s1 = rule

	la	$a0, prompt_n_generations
	li  $v0, 4
	syscall				# printf("Enter how many generations: ");
	
	li  $v0, 5
	syscall				# scanf("%d",&n)

	blt $v0, MIN_GENERATIONS, InvalidGen   # printf('invalid...')
	bgt $v0, MAX_GENERATIONS, InvalidGen
	move $s2, $v0		# s2 = gen

	j   out

InvalidSize:
	la	$a0, error_world_size
	li  $v0, 4
	syscall				# printf("Invalid world size\n");
	j   error

InvalidRule:
	la	$a0, error_rule
	li  $v0, 4
	syscall				# printf("Invalid rule\n");
	j	error

InvalidGen:
	la	$a0, error_n_generations
	li  $v0, 4
	syscall				# printf("Invalid number of generations\n");
	j   error

out:
	li  $a0, '\n'
	li  $v0, 11
	syscall				# putchar('\n')

	li  $s3, 0
	blt $s2, 0, inverse # negative gen
	j   out1

inverse:
	li  $s3, 1          # inverse = 1
	neg $s2, $s2

out1:
	la   $t9, cells		# addr for cells[]
	move $t1, $s0		# world size
	div  $t1, $t1, 2    # world size / 2

	add  $t2, $t9, $t1  # addr for the center of the world
	li   $t3, 1        
	sb   $t3, 0($t2)	# cells[0][world_size/2] = 1

	li   $a0, 1			# g = 1

run_G:
	bgt  $a0, $s2, out2  # g > n_gen break out
	move $a1, $s0		 # a1 = world_size
	move $a2, $s1		 # a2 = rule
	jal  run_generation
	addi $a0, $a0, 1	 # g++
	j    run_G

out2:
	li   $s4, 0		
	beqz $s3, print_PG  # inverse = 0
	move $s4, $s2		# inverse = 1, a0 = generation
	li   $t6, 1
	li   $t5, 0
	
print_NG:
	blt  $s4, $t5, end	# g < 0 break out
	move $a0, $s4
	move $a1, $s0		 
	jal  print_generation
	sub  $s4, $s4, $t6	# g--
	j    print_NG

print_PG:
	bgt  $s4, $s2, end  # g > n_gen break out
	move $a0, $s4
	move $a1, $s0		
	jal  print_generation
	addi $s4, $s4, 1	# g++
	j    print_PG


end:
	# return 0	
	li	$v0, 0
    j   release

error:
	# return 1	
	li	$v0, 1

release:
    lw  $s0, 0($sp)
    lw  $s1, 4($sp)
    lw  $s2, 8($sp)
    lw  $s3, 12($sp)
    lw  $ra, 16($sp)
    add $sp, $sp, 20
    jr  $ra

	# Callee:
	# $t0 -> state
	# $t1 -> x
	# $t2 -> left
	# $t6 -> center
	# $t7 -> right

	# Caller:
	# $a0 -> g for passing into the func
	# $a1 -> world_size
	# $a2 -> rule

run_generation:

	li  $t1, 0			# int x = 0
	la  $t9, cells
loop:	
	bge $t1, $a1, outLoop  # break out of the loop
	li  $t2, 0			# int left = 0
	li  $t3, 0
	bgt $t1, $t3, left  # x > 0 => left
	j   center

left:
	li  $t5, 1
	sub $t3, $a0, $t5	# which_generation - 1
	sub $t6, $t1, $t5 	# x - 1
	mul $t4, $t3, MAX_WORLD_SIZE	# which_gen * world
	add $t4, $t4, $t6   # cells[which_gen - 1][x - 1]
	add $t4, $t4, $t9	# addr + cell
	lb  $t2, 0($t4)		# $t2 =  cells[which_gen - 1][x - 1]

center:
	li  $t5, 1
	sub $t3, $a0, $t5	# which_generation - 1
	mul $t4, $t3, MAX_WORLD_SIZE
	add $t4, $t4, $t1
	add $t4, $t4, $t9
	lb  $t6, 0($t4)		# center = cells[which_gen - 1][x]

	sub $t4, $a1, $t5	# world_size - 1
	li  $t7, 0
	blt $t1, $t4, right # x < world_size - 1 => right
	j   out4


right:
	add $t5, $t1, $t5
	mul $t4, $t3, MAX_WORLD_SIZE
	add $t4, $t4, $t5
	add $t4, $t4, $t9
	lb  $t7, 0($t4)		# right = cells[which_gen - 1][x + 1]

out4:
	sll $t2, $t2, 2		# left << 2
	sll $t6, $t6, 1		# center << 1
	or  $t0, $t2, $t6	
	or  $t0, $t0, $t7	# state = left << 2 | centre << 1 | right << 0;

	li  $t2, 1
	sllv $t2, $t2, $t0	# bit = 1 << state
	and $t2, $a2, $t2	# set = rule & bit

	mul $t4, $a0, MAX_WORLD_SIZE
	add $t4, $t4, $t1
	add $t4, $t4, $t9	# cells[which_gen][x]

	beqz $t2, set0		# set = 0
	li	$t3, 1
	sb  $t3, 0($t4)		# cells[which_gen][x] = 1
	addi $t1, $t1, 1
	j   loop

set0:
	li	$t3, 0
	sb  $t3, 0($t4)		# cells[which_gen][x] = 0
	addi $t1, $t1, 1
	j   loop
	
outLoop:	
	jr	$ra

	# Callee:
	# $t0 -> g
	# $t1 -> world_size
	# $t2 -> address for the current byte
	# $t3 -> current byte

	# Caller:
	# $a0 -> generation
	# $a1 -> world size

print_generation:

	move $t0, $a0		# t0 = g
	li  $v0, 1
	syscall				# printf("%d")

	li  $a0, '\t'
	li  $v0, 11
	syscall				# putchar('\t')

	li  $t1, 0			# x = 0

put:
	bge $t1, $a1, out5  # x = world_size, break out
	mul $t2, $t0, MAX_WORLD_SIZE	# gen * world
	add $t2, $t2, $t1	# x + gen * world
	la  $t9, cells
	add $t2, $t2, $t9	# addr +  x + gen * world
	lb  $t3, 0($t2)		# load byte

	beqz $t3, dead 		# dead char with 0
	li  $a0, ALIVE_CHAR
	li  $v0, 11
	syscall				# putchar(ALIVE_CHAR)
	addi $t1, $t1, 1	# x++
	j put

dead:
	li  $a0, DEAD_CHAR
	li  $v0, 11
	syscall				# putchar(DEAD_CHAR)
	addi $t1, $t1, 1	# x++
	j put

out5:
	li  $a0, '\n'
	li  $v0, 11
	syscall				# putchar('\n')
	jr	$ra
