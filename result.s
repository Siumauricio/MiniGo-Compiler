.data

.globl main
.text
BubbleSort: 
addiu $sp, $sp, -20

sw $ra, 0($sp)

sw $a0, 4($sp)
sw $a1, 8($sp)
for0: 
lw $t0, 12($sp)

lw $t1, 8($sp)

li $t2, 1

sub $t1, $t1, $t2

slt $t0, $t0, $t1

beqz $t0, endFor1
addi $t0, $t0, 1
sw $t0, 12($sp)
for2: 
lw $t1, 16($sp)

lw $t3, 8($sp)

lw $t4, 12($sp)

sub $t3, $t3, $t4

li $t4, 1

sub $t3, $t3, $t4

slt $t1, $t1, $t3

beqz $t1, endFor3
addi $t1, $t1, 1
sw $t1, 16($sp)
lw $t3, 16($sp)

li $a0, 4
mult $a0, $t3
mflo $t3
lw $t5, 4($sp)
add $t3, $t5, $t3

lw $t5, 16($sp)

li $t6, 1

add $t5, $t5, $t6

li $a0, 4
mult $a0, $t5
mflo $t5
lw $t6, 4($sp)
add $t5, $t6, $t5

c.lt.s , 

bc1f endif4
lw $t6, 16($sp)

li $a0, 4
mult $a0, $t6
mflo $t6
lw $t7, 4($sp)
add $t6, $t7, $t6

b Exit5
Exit5:


endif4 :


j for2
endFor3: 


j for0
endFor1: 


mfc1 $v0, 


lw $ra, 0($sp)
addiu $sp, $sp, 20
jr $ra
main: 
addiu $sp, $sp, -36

sw $ra, 0($sp)

li $t7, 5

sw $t7, 4($sp)

li $t7, 11

sw $t7, 8($sp)
li $t7, 14

sw $t7, 12($sp)
li $t7, 3

sw $t7, 16($sp)
li $t7, 8

sw $t7, 20($sp)
li $t7, 18

sw $t7, 24($sp)
li $t7, 17

sw $t7, 28($sp)
li $t7, 43

sw $t7, 32($sp)

la $t7, 8($sp)

lw $t8, 4($sp)

move $a1, $t8
jal BubbleSort

move $a0, 
li $v0, 1
syscall


lw $ra, 0($sp)
addiu $sp, $sp, 36
jr $ra

