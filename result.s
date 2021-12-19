.data
string0: .asciiz"a = "
string3: .asciiz"a+b = "
string4: .asciiz"a-b = "
string5: .asciiz"a*b = "
string6: .asciiz"a/b = "
string7: .asciiz"a>b = "
string8: .asciiz"a<b = "
string9: .asciiz"a>=b = "
string10: .asciiz"a<=b = "
string11: .asciiz"true&&true = "

.globl main
.text
main: 
addiu $sp, $sp, -24

sw $ra, 0($sp)

li $t0, 10

sw $t0, 4($sp)

li $t0, 20

sw $t0, 8($sp)

li $t0, 0


li $t0, 0


li.s $f0, 10

s.s $f0, 20($sp)


la $a0, string0
li $v0, 4
syscall

lw $t0, 12($sp)

lw $t1, 16($sp)

addi $t0, $zero, 0
beq $t0, $t0, finalLabel2
beq $t1, $t0, finalLabel2
label1:
addi $t0, $zero, 1
finalLabel2:

la $a0, $t0
li $v0, 4
syscall


la $a0, string3
li $v0, 4
syscall

lw $t0, 4($sp)

move $a0, $t0
li $v0, 1
syscall


la $a0, string4
li $v0, 4
syscall


la $a0, string5
li $v0, 4
syscall

lw $t0, 4($sp)

lw $t1, 8($sp)

mult $t0, $t1
mflo $t0

move $a0, $t0
li $v0, 1
syscall


la $a0, string6
li $v0, 4
syscall

lw $t0, 4($sp)

lw $t1, 8($sp)

div $t0, $t1
mflo $t0

move $a0, $t0
li $v0, 1
syscall


la $a0, string7
li $v0, 4
syscall

lw $t0, 4($sp)

lw $t1, 8($sp)

sgt $t0, $t0, $t1

move $a0, $t0
li $v0, 1
syscall


la $a0, string8
li $v0, 4
syscall

lw $t0, 4($sp)

lw $t1, 8($sp)

slt $t0, $t0, $t1

move $a0, $t0
li $v0, 1
syscall


la $a0, string9
li $v0, 4
syscall

lw $t0, 4($sp)

lw $t1, 8($sp)

sge $t0, $t0, $t1

move $a0, $t0
li $v0, 1
syscall


la $a0, string10
li $v0, 4
syscall

lw $t0, 4($sp)

lw $t1, 8($sp)

sle $t0, $t0, $t1

move $a0, $t0
li $v0, 1
syscall


la $a0, string11
li $v0, 4
syscall


lw $ra, 0($sp)
addiu $sp, $sp, 24
jr $ra

