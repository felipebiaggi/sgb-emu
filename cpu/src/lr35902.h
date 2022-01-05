#ifndef LR35902_H
#define LR35902_H
#include <cstdint>
#include "cb.h"


class Bus;

class lr35902
{


public:
    lr35902();
    ~lr35902();

public:
    // register AF
    uint8_t A = 0x00;

    // Flags - register F

    // |7|6|5|4|3|2|1|0
    // ----------------
    // |Z|N|H|C|0|0|0|0
    union FLAGS {
            struct
            {
                uint8_t : 4;
                uint8_t C : 1;
                uint8_t H : 1;
                uint8_t N : 1;
                uint8_t Z : 1;
            } bits;
            uint8_t value;
    } F = { 0x00 };

    // register BC
    uint8_t B = 0x00;
    uint8_t C = 0x00;

    // register DE
    uint8_t D = 0x00;
    uint8_t E = 0x00;

    // register HL
    uint8_t H = 0x00;
    uint8_t L = 0x00;

    //Stack Pointer
    uint8_t S = 0x00;
    uint8_t P = 0x00;

    uint16_t PC = 0x0000; //Program Counter

    Cb cb;

    bool halt = false;
    bool interruption = false;

    void ConnectBus(Bus* n) {
        bus = n;
    }

    void clock();

    uint8_t opcode = 0x00;
    uint8_t cycles = 0;

    // 0x00~0x0F
    void NOP(); void LD_BC_u16(); void LD_BC_A(); void INC_BC(); void INC_B(); void DEC_B(); void LD_B_u8(); void RLCA();

    void LD_u16_SP(); void ADD_HL_BC(); void LD_A_BC(); void DEC_BC(); void INC_C(); void DEC_C(); void LD_C_u8(); void RRCA();


    // 0x10~0x1F
    void STOP(); void LD_DE_u16(); void LD_DE_A(); void INC_DE(); void INC_D(); void DEC_D(); void LD_D_u8(); void RLA();

    void JR_i8(); void ADD_HL_DE(); void LD_A_DE(); void DEC_DE(); void INC_E(); void DEC_E(); void LD_E_u8(); void RRA();

    // 0x20~0x2F

    void JR_NZ_i8(); void LD_HL_u16(); void LD_HLp_A(); void INC_HL(); void INC_H(); void DEC_H(); void LD_H_u8(); void DAA();

    void JR_Z_i8(); void ADD_HL_HL(); void LD_A_HLp(); void DEC_HL(); void INC_L(); void DEC_L(); void LD_L_u8(); void CPL();


    // 0x30~0x3F

    void JR_NC_i8(); void LD_SP_u16(); void LD_HLm_A(); void INC_SP(); void INC_HLa(); void DEC_HLa(); void LD_HL_u8(); void SCF();

    void JR_C_i8(); void ADD_HL_SP(); void LD_A_HLm(); void DEC_SP(); void INC_A(); void DEC_A(); void LD_A_u8(); void CCF();

    // 0x40~0x4F

    void LD_B_B(); void LD_B_C(); void LD_B_D(); void LD_B_E(); void LD_B_H(); void LD_B_L(); void LD_B_HL(); void LD_B_A();

    void LD_C_B(); void LD_C_C(); void LD_C_D(); void LD_C_E(); void LD_C_H(); void LD_C_L(); void LD_C_HL(); void LD_C_A();

    // 0x50~0x5F

    void LD_D_B(); void LD_D_C(); void LD_D_D(); void LD_D_E(); void LD_D_H(); void LD_D_L(); void LD_D_HL(); void LD_D_A();

    void LD_E_B(); void LD_E_C(); void LD_E_D(); void LD_E_E(); void LD_E_H(); void LD_E_L(); void LD_E_HL(); void LD_E_A();

    // 0x60~0x6F

    void LD_H_B(); void LD_H_C(); void LD_H_D(); void LD_H_E(); void LD_H_H(); void LD_H_L(); void LD_H_HL(); void LD_H_A();

    void LD_L_B(); void LD_L_C(); void LD_L_D(); void LD_L_E(); void LD_L_H(); void LD_L_L(); void LD_L_HL(); void LD_L_A();

    //0x70~0x7F

    void LD_HL_B(); void LD_HL_C(); void LD_HL_D(); void LD_HL_E(); void LD_HL_H(); void LD_HL_L(); void HALT(); void LD_HL_A();

    void LD_A_B(); void LD_A_C(); void LD_A_D(); void LD_A_E(); void LD_A_H(); void LD_A_L(); void LD_A_HL(); void LD_A_A();

    //0x80~0x8F

    void ADD_A_B(); void ADD_A_C(); void ADD_A_D(); void ADD_A_E(); void ADD_A_H(); void ADD_A_L(); void ADD_A_HL(); void ADD_A_A();

    void ADC_A_B(); void ADC_A_C(); void ADC_A_D(); void ADC_A_E(); void ADC_A_H(); void ADC_A_L(); void ADC_A_HL(); void ADC_A_A();

    //0x90~0x9F

    void SUB_A_B(); void SUB_A_C(); void SUB_A_D(); void SUB_A_E(); void SUB_A_H(); void SUB_A_L(); void SUB_A_HL(); void SUB_A_A();

    void SBC_A_B(); void SBC_A_C(); void SBC_A_D(); void SBC_A_E(); void SBC_A_H(); void SBC_A_L(); void SBC_A_HL(); void SBC_A_A();

    //0xA0~0xAF

    void AND_A_B(); void AND_A_C(); void AND_A_D(); void AND_A_E(); void AND_A_H(); void AND_A_L(); void AND_A_HL(); void AND_A_A();

    void XOR_A_B(); void XOR_A_C(); void XOR_A_D(); void XOR_A_E(); void XOR_A_H(); void XOR_A_L(); void XOR_A_HL(); void XOR_A_A();

    //0xB0~0xBF

    void OR_A_B(); void OR_A_C(); void OR_A_D(); void OR_A_E(); void OR_A_H(); void OR_A_L(); void OR_A_HL(); void OR_A_A();

    void CP_A_B(); void CP_A_C(); void CP_A_D(); void CP_A_E(); void CP_A_H(); void CP_A_L(); void CP_A_HL(); void CP_A_A();

    //0xC0~0xCF

    void RET_NZ(); void POP_BC(); void JP_NZ_u16(); void JP_u16(); void CALL_NZ_u16(); void PUSH_BC(); void ADD_A_u8(); void RST_00h();

    void RET_Z(); void RET(); void JP_Z_u16(); void PREFIX_CB(); void CALL_Z_u16(); void CALL_u16(); void ADC_A_u8(); void RST_08h();

    //0xD0~0xDF

    void RET_NC(); void POP_DE(); void JP_NC_u16(); void CALL_NC_u16(); void PUSH_DE(); void SUB_A_u8(); void RST_10h(); void RET_C();

    void RETI(); void JP_C_u16(); void CALL_C_u16(); void SBC_A_u8(); void RST_18h();

    //0xE0~0xEF

    void LD_FF00_u8_A(); void POP_HL(); void LD_FF00_C_A(); void PUSH_HL(); void AND_A_u8(); void RST_20h(); void ADD_SP_i8(); void JP_HL();

    void LD_u16_A(); void XOR_A_u8(); void RST_28h();

    //0xF0~0xFE

    void LD_A_FF00_u8(); void POP_AF(); void LD_A_FF00_C(); void DI(); void PUSH_AF(); void OR_A_u8(); void RST_30h(); void LD_HL_SP_i8();

    void LD_SP_HL(); void LD_A_u16(); void EI(); void CP_A_u8(); void RST_38h();

    Bus* bus = nullptr;

private:
    

    void ld(uint8_t* u8, uint16_t* addr);
    void ld(uint8_t* upper, uint8_t* lower, uint8_t* u8);
    void ld(uint8_t* u8, uint8_t* value);

    void ld_hlp(uint8_t* upper, uint8_t* lower, uint8_t* u8);
    void ld_hlm(uint8_t* upper, uint8_t* lower, uint8_t* u8);


    void add_hl(uint8_t* upper, uint8_t* lower);

    void inc(uint8_t* upper, uint8_t* lower);
    void inc(uint8_t* u8);

    void dec(uint8_t* upper, uint8_t* lower);
    void dec(uint8_t* u8);

    void jr(uint16_t* pc);
    void jp(uint16_t* pc);

    void call(uint16_t* pc);

    uint8_t add(uint8_t u8_1, uint8_t u8_2);
    uint8_t add(uint8_t u8, uint16_t r16);

    uint8_t adc(uint8_t u8_1, uint8_t u8_2);
    uint8_t adc(uint8_t u8, uint16_t r16);

    uint8_t sub(uint8_t u8_1, uint8_t u8_2);
    uint8_t sub(uint8_t u8, uint16_t r16);

    uint8_t sbc(uint8_t u8_1, uint8_t u8_2);
    uint8_t sbc(uint8_t u8, uint16_t r16);

    uint8_t and_op(uint8_t u8_1, uint8_t u8_2);
    uint8_t and_op(uint8_t u8, uint16_t r16);

    uint8_t xor_op(uint8_t u8_1, uint8_t u8_2);
    uint8_t xor_op(uint8_t u8, uint16_t r16);

    uint8_t or_op(uint8_t u8_1, uint8_t u8_2);
    uint8_t or_op(uint8_t u8, uint16_t r16);

    void cp(uint8_t u8_1, uint8_t u8_2);
    void cp(uint8_t u8, uint16_t r16);

    void pop(uint16_t* u16);
    void pop(uint8_t* upper, uint8_t* lower);

    void push(uint16_t* u16);
    void push(uint8_t* upper, uint8_t* lower);

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);

    void reset();

    void process(uint16_t opcode);


};

#endif // LR35902_H
