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
li $t1, 0

beqz $t1, exit3

bc1f endif4
lw $t2, j

li $a0, 4
mult $a0, $t2
mflo $t2
lw $t3, 4($sp)
add $t2, $t3, $t2
l.s $f0, 0($t2)


endif4 :


exit3 :


exit1 :


mfc1 $v0, 


lw $ra, 0($sp)
addiu $sp, $sp, 12
jr $ra
main: 
addiu $sp, $sp, -4

sw $ra, 0($sp)



lw $t0, a

lw $t1, size

jal BubbleSort



lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra

