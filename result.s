.data

.globl main
.text

li $t0, 0

li $a0, 4
mult $a0, $t0
mflo $t2
la $t3, unsorted
add $t2, $t3, $t2
l.s $f1, 0($t2)


