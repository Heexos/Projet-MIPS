#include "../opcode_define.h"
typedef struct Instruction Instruction;

struct Instruction{
	char *str;
	char opcode;
	char type;
  Instruction *suivant;
};

//------------------------
//------ STRUCT DEF ------
//------------------------
static Instruction jr = {STR_JR, JR, 'R', NULL};
static Instruction jal = {STR_JAL, JAL, 'J', &jr};
static Instruction j = {STR_J, J, 'J', &jal};
static Instruction blez = {STR_BLEZ, BLEZ, 'I', &j};
static Instruction bgtz = {STR_BGTZ, BGTZ, 'I', &blez};
static Instruction bne = {STR_BNE, BNE, 'I', &bgtz};
static Instruction beq = {STR_BEQ, BEQ, 'I', &bne};
static Instruction mflo = {STR_MFLO, MFLO, 'R', &beq};
static Instruction mfhi = {STR_MFHI, MFHI, 'R', &mflo};
static Instruction lui = {STR_LUI, LUI, 'I', &mfhi};
static Instruction sw = {STR_SW, SW, 'I', &lui};
static Instruction lw = {STR_LW, LW, 'I', &sw};
static Instruction slt = {STR_SLT, SLT, 'R', &lw};
static Instruction srl = {STR_SRL, SRL, 'R', &slt};
static Instruction sll = {STR_SLL, SLL, 'R', &srl};
static Instruction rotr = {STR_ROTR, ROTR, 'R', &sll};
static Instruction xor = {STR_XOR, XOR, 'R', &rotr};
static Instruction or = {STR_OR, OR, 'R', &xor};
static Instruction and = {STR_AND, AND, 'R', &or};
static Instruction _div = {STR_DIV, DIV, 'R', &and};
static Instruction mult = {STR_MULT, MULT, 'R', &_div};
static Instruction sub = {STR_SUB, SUB, 'R', &mult};
static Instruction addi = {STR_ADDI, ADDI, 'I', &sub};
static Instruction add = {STR_ADD, ADD, 'R', &addi};
static Instruction nop = {STR_NOP, NOP, 'R', &add};

static Instruction* head_lst_instruction = &nop;
