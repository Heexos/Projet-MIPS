#include "../register_define.h"

typedef struct Register Register;
struct Register{
	char *name1;
  char *name2;
	char address_value;
  Register *suivant;
};

//------------------------
//------ STRUCT DEF ------
//------------------------

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
