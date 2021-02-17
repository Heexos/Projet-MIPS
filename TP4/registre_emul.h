#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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

//registre speciaux processeur
#define REGISTER_PC_ADDR 0x20
#define REGISTER_HI_ADDR 0x30
#define REGISTER_LO_ADDR 0x31

//------------------------
//------ STRUCT DEF ------
//------------------------
typedef struct Register Register;

struct Register {

	char address_value;
  uint32_t value;
  Register *suivant;
};

static Register ra = {REGISTER_RA_ADDR, 0, NULL};
static Register fp = {REGISTER_FP_ADDR, 0, &ra};
static Register sp = {REGISTER_SP_ADDR, 0, &fp};
static Register gp = {REGISTER_GP_ADDR, 0, &sp};
static Register k1 = {REGISTER_K1_ADDR, 0, &gp};
static Register k0 = {REGISTER_K0_ADDR, 0, &k1};
static Register t9 = {REGISTER_T9_ADDR, 0, &k0};
static Register t8 = {REGISTER_T8_ADDR, 0, &t9};
static Register s7 = {REGISTER_S7_ADDR, 0, &t8};
static Register s6 = {REGISTER_S6_ADDR, 0, &s7};
static Register s5 = {REGISTER_S5_ADDR, 0, &s6};
static Register s4 = {REGISTER_S4_ADDR, 0, &s5};
static Register s3 = {REGISTER_S3_ADDR, 0, &s4};
static Register s2 = {REGISTER_S2_ADDR, 0, &s3};
static Register s1 = {REGISTER_S1_ADDR, 0, &s2};
static Register s0 = {REGISTER_S0_ADDR, 0, &s1};
static Register t7 = {REGISTER_T7_ADDR, 0, &s0};
static Register t6 = {REGISTER_T6_ADDR, 0, &t7};
static Register t5 = {REGISTER_T5_ADDR, 0, &t6};
static Register t4 = {REGISTER_T4_ADDR, 0, &t5};
static Register t3 = {REGISTER_T3_ADDR, 0, &t4};
static Register t2 = {REGISTER_T2_ADDR, 0, &t3};
static Register t1 = {REGISTER_T1_ADDR, 0, &t2};
static Register t0 = {REGISTER_T0_ADDR, 0, &t1};
static Register a3 = {REGISTER_A3_ADDR, 0, &t0};
static Register a2 = {REGISTER_A2_ADDR, 0, &a3};
static Register a1 = {REGISTER_A1_ADDR, 0, &a2};
static Register a0 = {REGISTER_A0_ADDR, 0, &a1};
static Register v1 = {REGISTER_V1_ADDR, 0, &a0};
static Register v0 = {REGISTER_V0_ADDR, 0, &v1};
static Register at = {REGISTER_AT_ADDR, 0, &v0};
static Register zero = {REGISTER_ZERO_ADDR, 0, &at};

//registre speciaux processeur
static Register pc = {REGISTER_PC_ADDR, 0, &zero};
static Register hi = {REGISTER_HI_ADDR, 0, &pc};
static Register lo = {REGISTER_LO_ADDR, 0, &hi};

static Register *head_lst_register = &lo;

//------------------------
//------ FUNCTIONS -------
//------------------------

//read_register
//Permet de lire le contenu d'un registre.
//Entrée : (int32_t*) pointeur vers espace
//         memoire qui contiendra la valeur du registre
//         (char) l'addresse du registre
//Sortie : (Int), 0 = succes, 1 = echec
int read_register(uint32_t* value, char hex_address);

//write_register
//Permet de lire le contenu d'un registre.
//Entrée : (int32_t) valeur que l'on veut mettre dans le registre
//         (char) l'addresse du registre
//Sortie : (Int), 0 = succes, 1 = echec
int write_register(uint32_t value, char hex_address);

//incremente le registre du program_counter de 4
void inc_pc_4();








//
