//------------------------
//--- HEXADECIMAL CODE ---
//------------------------

//SPECIAL
#define SPECIAL 0x00
#define NOP 0x00

//ARITHMETIC
#define ADD 0x20
#define ADDI 0x08
#define SUB 0x22
#define MULT 0x18
#define DIV 0x1A

//LOGIC
#define AND 0x24
#define OR 0x25
#define XOR 0x26

//SHIFT
#define ROTR 0x02
#define SLL 0x00
#define SRL 0x02

//SET
#define SLT 0x2A

//LOAD/STORE
#define LW 0x23
#define SW 0x2B
#define LUI 0x0F
#define MFHI 0x10
#define MFLO 0x12

//BRANCH
#define BEQ 0x04
#define BNE 0x05
#define BGTZ 0x07
#define BLEZ 0x06
#define J 0x02
#define JAL 0x03
#define JR 0x08

//------------------------
//----- STRING CODE ------
//------------------------

//SPECIAL
#define STR_NOP "NOP"

//ARITHMETIC
#define STR_ADD "ADD"
#define STR_ADDI "ADDI"
#define STR_SUB "SUB"
#define STR_MULT "MULT"
#define STR_DIV "DIV"

//LOGIC
#define STR_AND "AND"
#define STR_OR "OR"
#define STR_XOR "XOR"

//SHIFT
#define STR_ROTR "ROTR"
#define STR_SLL "SLL"
#define STR_SRL "SRL"

//SET
#define STR_SLT "SLT"

//LOAD/STORE
#define STR_LW "LW"
#define STR_SW "SW"
#define STR_LUI "LUI"
#define STR_MFHI "MFHI"
#define STR_MFLO "MFLO"

//BRANCH
#define STR_BEQ "BEQ"
#define STR_BNE "BNE"
#define STR_BGTZ "BGTZ"
#define STR_BLEZ "BLEZ"
#define STR_J "J"
#define STR_JAL "JAL"
#define STR_JR "JR"

//------------------------
//------ STRUCT DEF ------
//------------------------
typedef struct Instruction Instruction;

struct Instruction{
	char *str;
	char opcode;
	char type;
  Instruction *suivant;
};

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
