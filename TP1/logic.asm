ADDI $t0, $0, 12 # 1100
ADDI $t1, $0, 10 # 1010

AND $t2, $t0, $t1 # 1000 -> 8

OR $t3, $t0, $t1 # 1110 -> 14

XOR $t4, $t0, $t1 #0110 -> 6