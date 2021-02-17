//------------------------
//--- HEXADECIMAL CODE ---
//------------------------

#define REGISTER_ZERO_ADDR 0x00
#define REGISTER_AT_ADDR 0x01
#define REGISTER_V0_ADDR 0x02
#define REGISTER_V1_ADDR 0x03
#define REGISTER_A0_ADDR 0x04
#define REGISTER_A1_ADDR 0x05
#define REGISTER_A2_ADDR 0x06
#define REGISTER_A3_ADDR 0x07
#define REGISTER_T0_ADDR 0x08
#define REGISTER_T1_ADDR 0x09
#define REGISTER_T2_ADDR 0x0A
#define REGISTER_T3_ADDR 0x0B
#define REGISTER_T4_ADDR 0x0C
#define REGISTER_T5_ADDR 0x0D
#define REGISTER_T6_ADDR 0x0E
#define REGISTER_T7_ADDR 0x0F
#define REGISTER_S0_ADDR 0x10
#define REGISTER_S1_ADDR 0x11
#define REGISTER_S2_ADDR 0x12
#define REGISTER_S3_ADDR 0x13
#define REGISTER_S4_ADDR 0x14
#define REGISTER_S5_ADDR 0x15
#define REGISTER_S6_ADDR 0x16
#define REGISTER_S7_ADDR 0x17
#define REGISTER_T8_ADDR 0x18
#define REGISTER_T9_ADDR 0x19
#define REGISTER_K0_ADDR 0x1A
#define REGISTER_K1_ADDR 0x1B
#define REGISTER_GP_ADDR 0x1C
#define REGISTER_SP_ADDR 0x1D
#define REGISTER_FP_ADDR 0x1E
#define REGISTER_RA_ADDR 0x1F

//------------------------
//----- STRING CODE ------
//------------------------

#define REGISTER_ZERO_STR1 "$ZERO"
#define REGISTER_AT_STR1 "$AT"
#define REGISTER_V0_STR1 "$V0"
#define REGISTER_V1_STR1 "$V1"
#define REGISTER_A0_STR1 "$A0"
#define REGISTER_A1_STR1 "$A1"
#define REGISTER_A2_STR1 "$A2"
#define REGISTER_A3_STR1 "$A3"
#define REGISTER_T0_STR1 "$T0"
#define REGISTER_T1_STR1 "$T1"
#define REGISTER_T2_STR1 "$T2"
#define REGISTER_T3_STR1 "$T3"
#define REGISTER_T4_STR1 "$T4"
#define REGISTER_T5_STR1 "$T5"
#define REGISTER_T6_STR1 "$T6"
#define REGISTER_T7_STR1 "$T7"
#define REGISTER_S0_STR1 "$S0"
#define REGISTER_S1_STR1 "$S1"
#define REGISTER_S2_STR1 "$S2"
#define REGISTER_S3_STR1 "$S3"
#define REGISTER_S4_STR1 "$S4"
#define REGISTER_S5_STR1 "$S5"
#define REGISTER_S6_STR1 "$S6"
#define REGISTER_S7_STR1 "$S7"
#define REGISTER_T8_STR1 "$T8"
#define REGISTER_T9_STR1 "$T9"
#define REGISTER_K0_STR1 "$K0"
#define REGISTER_K1_STR1 "$K1"
#define REGISTER_GP_STR1 "$GP"
#define REGISTER_SP_STR1 "$SP"
#define REGISTER_FP_STR1 "$FP"
#define REGISTER_RA_STR1 "$RA"

#define REGISTER_ZERO_STR2 "$0"
#define REGISTER_AT_STR2 "$1"
#define REGISTER_V0_STR2 "$2"
#define REGISTER_V1_STR2 "$3"
#define REGISTER_A0_STR2 "$4"
#define REGISTER_A1_STR2 "$5"
#define REGISTER_A2_STR2 "$6"
#define REGISTER_A3_STR2 "$7"
#define REGISTER_T0_STR2 "$8"
#define REGISTER_T1_STR2 "$9"
#define REGISTER_T2_STR2 "$10"
#define REGISTER_T3_STR2 "$11"
#define REGISTER_T4_STR2 "$12"
#define REGISTER_T5_STR2 "$13"
#define REGISTER_T6_STR2 "$14"
#define REGISTER_T7_STR2 "$15"
#define REGISTER_S0_STR2 "$16"
#define REGISTER_S1_STR2 "$17"
#define REGISTER_S2_STR2 "$18"
#define REGISTER_S3_STR2 "$19"
#define REGISTER_S4_STR2 "$20"
#define REGISTER_S5_STR2 "$21"
#define REGISTER_S6_STR2 "$22"
#define REGISTER_S7_STR2 "$23"
#define REGISTER_T8_STR2 "$24"
#define REGISTER_T9_STR2 "$25"
#define REGISTER_K0_STR2 "$26"
#define REGISTER_K1_STR2 "$27"
#define REGISTER_GP_STR2 "$28"
#define REGISTER_SP_STR2 "$29"
#define REGISTER_FP_STR2 "$30"
#define REGISTER_RA_STR2 "$31"

//------------------------
//------ STRUCT DEF ------
//------------------------
typedef struct Register Register;

struct Register{
	char *name1;
  char *name2;
	char address_value;
  Register *suivant;
};

static Register ra = {REGISTER_RA_STR1, REGISTER_RA_STR2, REGISTER_RA_ADDR, NULL};
static Register fp = {REGISTER_FP_STR1, REGISTER_FP_STR2, REGISTER_FP_ADDR, &ra};
static Register sp = {REGISTER_SP_STR1, REGISTER_SP_STR2, REGISTER_SP_ADDR, &fp};
static Register gp = {REGISTER_GP_STR1, REGISTER_GP_STR2, REGISTER_GP_ADDR, &sp};
static Register k1 = {REGISTER_K1_STR1, REGISTER_K1_STR2, REGISTER_K1_ADDR, &gp};
static Register k0 = {REGISTER_K0_STR1, REGISTER_K0_STR2, REGISTER_K0_ADDR, &k1};
static Register t9 = {REGISTER_T9_STR1, REGISTER_T9_STR2, REGISTER_T9_ADDR, &k0};
static Register t8 = {REGISTER_T8_STR1, REGISTER_T8_STR2, REGISTER_T8_ADDR, &t9};
static Register s7 = {REGISTER_S7_STR1, REGISTER_S7_STR2, REGISTER_S7_ADDR, &t8};
static Register s6 = {REGISTER_S6_STR1, REGISTER_S6_STR2, REGISTER_S6_ADDR, &s7};
static Register s5 = {REGISTER_S5_STR1, REGISTER_S5_STR2, REGISTER_S5_ADDR, &s6};
static Register s4 = {REGISTER_S4_STR1, REGISTER_S4_STR2, REGISTER_S4_ADDR, &s5};
static Register s3 = {REGISTER_S3_STR1, REGISTER_S3_STR2, REGISTER_S3_ADDR, &s4};
static Register s2 = {REGISTER_S2_STR1, REGISTER_S2_STR2, REGISTER_S2_ADDR, &s3};
static Register s1 = {REGISTER_S1_STR1, REGISTER_S1_STR2, REGISTER_S1_ADDR, &s2};
static Register s0 = {REGISTER_S0_STR1, REGISTER_S0_STR2, REGISTER_S0_ADDR, &s1};
static Register t7 = {REGISTER_T7_STR1, REGISTER_T7_STR2, REGISTER_T7_ADDR, &s0};
static Register t6 = {REGISTER_T6_STR1, REGISTER_T6_STR2, REGISTER_T6_ADDR, &t7};
static Register t5 = {REGISTER_T5_STR1, REGISTER_T5_STR2, REGISTER_T5_ADDR, &t6};
static Register t4 = {REGISTER_T4_STR1, REGISTER_T4_STR2, REGISTER_T4_ADDR, &t5};
static Register t3 = {REGISTER_T3_STR1, REGISTER_T3_STR2, REGISTER_T3_ADDR, &t4};
static Register t2 = {REGISTER_T2_STR1, REGISTER_T2_STR2, REGISTER_T2_ADDR, &t3};
static Register t1 = {REGISTER_T1_STR1, REGISTER_T1_STR2, REGISTER_T1_ADDR, &t2};
static Register t0 = {REGISTER_T0_STR1, REGISTER_T0_STR2, REGISTER_T0_ADDR, &t1};
static Register a3 = {REGISTER_A3_STR1, REGISTER_A3_STR2, REGISTER_A3_ADDR, &t0};
static Register a2 = {REGISTER_A2_STR1, REGISTER_A2_STR2, REGISTER_A2_ADDR, &a3};
static Register a1 = {REGISTER_A1_STR1, REGISTER_A1_STR2, REGISTER_A1_ADDR, &a2};
static Register a0 = {REGISTER_A0_STR1, REGISTER_A0_STR2, REGISTER_A0_ADDR, &a1};
static Register v1 = {REGISTER_V1_STR1, REGISTER_V1_STR2, REGISTER_V1_ADDR, &a0};
static Register v0 = {REGISTER_V0_STR1, REGISTER_V0_STR2, REGISTER_V0_ADDR, &v1};
static Register at = {REGISTER_AT_STR1, REGISTER_AT_STR2, REGISTER_AT_ADDR, &v0};
static Register zero = {REGISTER_ZERO_STR1, REGISTER_ZERO_STR2, REGISTER_ZERO_ADDR, &at};

static Register *head_lst_register = &zero;

























//
