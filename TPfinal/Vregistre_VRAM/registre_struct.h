//------------------------
//--- HEXADECIMAL CODE ---
//------------------------
#include "../register_define.h"

//------------------------
//------ STRUCT DEF ------
//------------------------

static Register ra = {REGISTER_RA_STR1, REGISTER_RA_ADDR, 0, NULL};
static Register fp = {REGISTER_FP_STR1, REGISTER_FP_ADDR, 0, &ra};
static Register sp = {REGISTER_SP_STR1, REGISTER_SP_ADDR, 0, &fp};
static Register gp = {REGISTER_GP_STR1, REGISTER_GP_ADDR, 0, &sp};
static Register k1 = {REGISTER_K1_STR1, REGISTER_K1_ADDR, 0, &gp};
static Register k0 = {REGISTER_K0_STR1, REGISTER_K0_ADDR, 0, &k1};
static Register t9 = {REGISTER_T9_STR1, REGISTER_T9_ADDR, 0, &k0};
static Register t8 = {REGISTER_T8_STR1, REGISTER_T8_ADDR, 0, &t9};
static Register s7 = {REGISTER_S7_STR1, REGISTER_S7_ADDR, 0, &t8};
static Register s6 = {REGISTER_S6_STR1, REGISTER_S6_ADDR, 0, &s7};
static Register s5 = {REGISTER_S5_STR1, REGISTER_S5_ADDR, 0, &s6};
static Register s4 = {REGISTER_S4_STR1, REGISTER_S4_ADDR, 0, &s5};
static Register s3 = {REGISTER_S3_STR1, REGISTER_S3_ADDR, 0, &s4};
static Register s2 = {REGISTER_S2_STR1, REGISTER_S2_ADDR, 0, &s3};
static Register s1 = {REGISTER_S1_STR1, REGISTER_S1_ADDR, 0, &s2};
static Register s0 = {REGISTER_S0_STR1, REGISTER_S0_ADDR, 0, &s1};
static Register t7 = {REGISTER_T7_STR1, REGISTER_T7_ADDR, 0, &s0};
static Register t6 = {REGISTER_T6_STR1, REGISTER_T6_ADDR, 0, &t7};
static Register t5 = {REGISTER_T5_STR1, REGISTER_T5_ADDR, 0, &t6};
static Register t4 = {REGISTER_T4_STR1, REGISTER_T4_ADDR, 0, &t5};
static Register t3 = {REGISTER_T3_STR1, REGISTER_T3_ADDR, 0, &t4};
static Register t2 = {REGISTER_T2_STR1, REGISTER_T2_ADDR, 0, &t3};
static Register t1 = {REGISTER_T1_STR1, REGISTER_T1_ADDR, 0, &t2};
static Register t0 = {REGISTER_T0_STR1, REGISTER_T0_ADDR, 0, &t1};
static Register a3 = {REGISTER_A3_STR1, REGISTER_A3_ADDR, 0, &t0};
static Register a2 = {REGISTER_A2_STR1, REGISTER_A2_ADDR, 0, &a3};
static Register a1 = {REGISTER_A1_STR1, REGISTER_A1_ADDR, 0, &a2};
static Register a0 = {REGISTER_A0_STR1, REGISTER_A0_ADDR, 0, &a1};
static Register v1 = {REGISTER_V1_STR1, REGISTER_V1_ADDR, 0, &a0};
static Register v0 = {REGISTER_V0_STR1, REGISTER_V0_ADDR, 0, &v1};
static Register at = {REGISTER_AT_STR1, REGISTER_AT_ADDR, 0, &v0};
static Register zero = {REGISTER_ZERO_STR1, REGISTER_ZERO_ADDR, 0, &at};

//registre speciaux processeur
static Register pc = {REGISTER_PC_STR1, REGISTER_PC_ADDR, 0, &zero};
static Register hi = {REGISTER_HI_STR1, REGISTER_HI_ADDR, 0, &pc};
static Register lo = {REGISTER_LO_STR1, REGISTER_LO_ADDR, 0, &hi};

static Register *head_lst_register = &lo;
