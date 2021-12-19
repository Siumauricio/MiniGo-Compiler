.data
string5: .asciiz"Sorted Array : "

.globl main
.text
bubbleSort: 
addiu $sp, $sp, -16

sw $ra, 0($sp)

sw $a0, 4($sp)
li $t0, 1


for0: 
lw $t0, 8($sp)

beqz $t0, endFor1
lw $t1, 8($sp)

for2: 
lw $t2, 12($sp)

li $t3, 10

slt $t2, $t2, $t3

beqz $t2, endFor3
addi $t2, $t2, 1
sw $t2, 12($sp)
lw $t3, 4($sp)
lw $t3, 12($sp)

li $t5, 1

sub $t3, $t3, $t5

li $a0, 4
mult $a0, $t3
mflo $t5
lw $t6, 4($sp)
add $t5, $t6, $t5

lw $t6, 4($sp)
lw $t6, 12($sp)

li $a0, 4
mult $a0, $t6
mflo $t7
lw $t8, 4($sp)
add $t7, $t8, $t7

sgt $t3, $t3, $t6

beqz $t3, endif4
lw $t6, 4($sp)
lw $t6, 12($sp)

li $a0, 4
mult $a0, $t6
mflo $t8
lw $t9, 4($sp)
add $t8, $t9, $t8

lw $t9, 4($sp)
lw $t9, 12($sp)

li , 1

sub $t9, $t9, 

li $a0, 4
mult $a0, $t9
mflo 
lw , 4($sp)
add , , 

lw , 8($sp)


endif4 :


j for2
endFor3: 


j for0
endFor1: 

la $t3, 4($sp)

mfc1 $v0, $t3


lw $ra, 0($sp)
addiu $sp, $sp, 16
jr $ra
main: 
addiu $sp, $sp, -52

sw $ra, 0($sp)

li $t3, 10

sw $t3, 4($sp)
li $t3, 6

sw $t3, 8($sp)
li $t3, 2

sw $t3, 12($sp)
li $t3, 1

sw $t3, 16($sp)
li $t3, 5

sw $t3, 20($sp)
li $t3, 8

sw $t3, 24($sp)
li $t3, 3

sw $t3, 28($sp)
li $t3, 4

sw $t3, 32($sp)
li $t3, 7

sw $t3, 36($sp)
li $t3, 9

sw $t3, 40($sp)

la $t3, 4($sp)

add $t3, $t3, 0
move $a0, $t3
jal bubbleSort
move , $v0
sw , 44($sp)


la $a0, string5
li $v0, 4
syscall

for6: 
lw , 48($sp)

li , 10

slt , , 

beqz , endFor7
addi , , 1
sw , 48($sp)
lw , 44($sp)
lw , 48($sp)

li $a0, 4
mult $a0, 
mflo 
la , 44($sp)
add , , 

move $a0, 
li $v0, 1
syscall


j for6
endFor7: 


lw $ra, 0($sp)
addiu $sp, $sp, 52
jr $ra

