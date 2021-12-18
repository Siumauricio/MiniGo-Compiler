.data
string6: .asciiz"loop"

.globl main
.text
main: 
addiu $sp, $sp, -16

sw $ra, 0($sp)

li $t0, 1

sw $t0, 4($sp)

for0: 
lw $t0, 4($sp)

li $t1, 3

sle $t0, $t0, $t1

beqz $t0, endFor1
lw $t1, 4($sp)

move $a0, $t1
li $v0, 1
syscall

lw $t1, 4($sp)


j for0
endFor1: 

for2: 
lw $t2, 8($sp)

li $t3, 9

sle $t2, $t2, $t3

beqz $t2, endFor3
addi $t2, $t2, 1
sw $t2, 8($sp)
lw $t3, 8($sp)

move $a0, $t3
li $v0, 1
syscall


j for2
endFor3: 

for4: 

la $a0, string6
li $v0, 4
syscall



j for4
endFor5: 

for7: 
lw $t3, 12($sp)

li $t5, 5

sle $t3, $t3, $t5

beqz $t3, endFor8
addi $t3, $t3, 1
sw $t3, 12($sp)
lw $t5, 12($sp)

li $t7, 2

div $t5, $t7
mfhi $t5

li $t5, 0
mtc1 $t5, $f0
cvt.s.w $f0, $f0


bc1f endif9


endif9 :

lw $t5, 12($sp)

move $a0, $t5
li $v0, 1
syscall


j for7
endFor8: 


lw $ra, 0($sp)
addiu $sp, $sp, 16
jr $ra

