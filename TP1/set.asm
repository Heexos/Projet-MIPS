ADDI $t0, $0, 4
ADDI $t1, $0, 3

SLT $t2, $t0, $t1 # t2 = 0
SLT $t3, $t0, $t0 # t3 = 0
SLT $t4, $t1, $t0 # t4 = 1