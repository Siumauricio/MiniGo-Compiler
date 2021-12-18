.data

.globl main
.text
BubbleSort: 
addiu $sp, $sp, -12

sw $ra, 0($sp)

sw $a0, 4($sp)
sw $a1, 8($sp)
li $t0, 0

beqz $t0, exit1
li $t2, 0

beqz $t2, exit3
lw $t4, j

li $a0, 4
mult $a0, $t4
mflo $t4
lw $t5, 4($sp)
add $t4, $t5, $t4

lw $t5, j

li $t6, 1
mtc1 $t6, $f0
cvt.s.w $f0, $f0

add.s $f0, $t5, $f0

li $a0, 4
mult $a0, $f0
mflo $t5
lw $t6, 4($sp)
add $t5, $t6, $t5

c.lt.s , 

bc1f endif4
lw $t6, j

li $a0, 4
mult $a0, $t6
mflo $t6
lw $t7, 4($sp)
add $t6, $t7, $t6


endif4 :


exit3 :


exit1 :


mfc1 $v0, 


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra
main: 
addiu $sp, $sp, -36

sw $ra, 0($sp)

li $t0, 5

sw $t0, 4($sp)

li $t0, 11

sw $t0, 8($sp)
li $t0, 14

sw $t0, 12($sp)
li $t0, 3

sw $t0, 16($sp)
li $t0, 8

sw $t0, 20($sp)
li $t0, 18

sw $t0, 24($sp)
li $t0, 17

sw $t0, 28($sp)
li $t0, 43

sw $t0, 32($sp)

la $t0, 8($sp)

lw $t2, 4($sp)

move $a1, $t2
jal BubbleSort

move $a0, 
li $v0, 1
syscall


lw $ra, 0($sp)
addiu $sp, $sp, 36
jr $ra

