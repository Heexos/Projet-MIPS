ADDI $t0, $0, -1 # 10100 ... 0010
ADDI $t1, $0, 5 #0101
ADDI $t2, $0, 2
ADDI $t3, $0, 1

ROTR $t3, $t0, $t2 # 1010100 ... -> 43008
SLL $t4, $t1, $t3 # 1010 -> 10
SRL $t5, $t1, $t2 # 1 -> 1
