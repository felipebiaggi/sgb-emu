#ifndef CB_H
#define CB_H
#include <cstdint>

class lr35902;
class Bus;

class Cb
{

public:
    Cb();

public:
    void ConnectCpu(lr35902* n) {cpu = n; }
    void ConnectBus(Bus* n) {bus = n; }

    void process(uint16_t opcode);


    //0x00~0x0F

    void RLC_B(); void RLC_C(); void RLC_D(); void RLC_E(); void RLC_H(); void RLC_L(); void RLC_HL(); void RLC_A();

    void RRC_B(); void RRC_C(); void RRC_D(); void RRC_E(); void RRC_H(); void RRC_L(); void RRC_HL(); void RRC_A();

    //0x10~0x1F

    void RL_B(); void RL_C(); void RL_D(); void RL_E(); void RL_H(); void RL_L(); void RL_HL(); void RL_A();

    void RR_B(); void RR_C(); void RR_D(); void RR_E(); void RR_H(); void RR_L(); void RR_HL(); void RR_A();

    //0x20~0x2F

    void SLA_B(); void SLA_C(); void SLA_D(); void SLA_E(); void SLA_H(); void SLA_L(); void SLA_HL(); void SLA_A();

    void SRA_B(); void SRA_C(); void SRA_D(); void SRA_E(); void SRA_H(); void SRA_L(); void SRA_HL(); void SRA_A();

    //0x30~0x3F

    void SWAP_B(); void SWAP_C(); void SWAP_D(); void SWAP_E(); void SWAP_H(); void SWAP_L(); void SWAP_HL(); void SWAP_A();

    void SRL_B(); void SRL_C(); void SRL_D(); void SRL_E(); void SRL_H(); void SRL_L(); void SRL_HL(); void SRL_A();

    //0x40~0x4F

    void BIT_0_B(); void BIT_0_C(); void BIT_0_D(); void BIT_0_E(); void BIT_0_H(); void BIT_0_L(); void BIT_0_HL(); void BIT_0_A();

    void BIT_1_B(); void BIT_1_C(); void BIT_1_D(); void BIT_1_E(); void BIT_1_H(); void BIT_1_L(); void BIT_1_HL(); void BIT_1_A();

    //0x50~0x5F

    void BIT_2_B(); void BIT_2_C(); void BIT_2_D(); void BIT_2_E(); void BIT_2_H(); void BIT_2_L(); void BIT_2_HL(); void BIT_2_A();

    void BIT_3_B(); void BIT_3_C(); void BIT_3_D(); void BIT_3_E(); void BIT_3_H(); void BIT_3_L(); void BIT_3_HL(); void BIT_3_A();

    //0x60~0x6F

    void BIT_4_B(); void BIT_4_C(); void BIT_4_D(); void BIT_4_E(); void BIT_4_H(); void BIT_4_L(); void BIT_4_HL(); void BIT_4_A();

    void BIT_5_B(); void BIT_5_C(); void BIT_5_D(); void BIT_5_E(); void BIT_5_H(); void BIT_5_L(); void BIT_5_HL(); void BIT_5_A();

    //0x70~0x7F

    void BIT_6_B(); void BIT_6_C(); void BIT_6_D(); void BIT_6_E(); void BIT_6_H(); void BIT_6_L(); void BIT_6_HL(); void BIT_6_A();

    void BIT_7_B(); void BIT_7_C(); void BIT_7_D(); void BIT_7_E(); void BIT_7_H(); void BIT_7_L(); void BIT_7_HL(); void BIT_7_A();

    //0x80~0x8F

    void RES_0_B(); void RES_0_C(); void RES_0_D(); void RES_0_E(); void RES_0_H(); void RES_0_L(); void RES_0_HL(); void RES_0_A();

    void RES_1_B(); void RES_1_C(); void RES_1_D(); void RES_1_E(); void RES_1_H(); void RES_1_L(); void RES_1_HL(); void RES_1_A();

    //0x90~0x9F

    void RES_2_B(); void RES_2_C(); void RES_2_D(); void RES_2_E(); void RES_2_H(); void RES_2_L(); void RES_2_HL(); void RES_2_A();

    void RES_3_B(); void RES_3_C(); void RES_3_D(); void RES_3_E(); void RES_3_H(); void RES_3_L(); void RES_3_HL(); void RES_3_A();

    //0xA0~0xAF

    void RES_4_B(); void RES_4_C(); void RES_4_D(); void RES_4_E(); void RES_4_H(); void RES_4_L(); void RES_4_HL(); void RES_4_A();

    void RES_5_B(); void RES_5_C(); void RES_5_D(); void RES_5_E(); void RES_5_H(); void RES_5_L(); void RES_5_HL(); void RES_5_A();

    //0xB0~0xBF

    void RES_6_B(); void RES_6_C(); void RES_6_D(); void RES_6_E(); void RES_6_H(); void RES_6_L(); void RES_6_HL(); void RES_6_A();

    void RES_7_B(); void RES_7_C(); void RES_7_D(); void RES_7_E(); void RES_7_H(); void RES_7_L(); void RES_7_HL(); void RES_7_A();

    //0xC0~0xCF

    void SET_0_B(); void SET_0_C(); void SET_0_D(); void SET_0_E(); void SET_0_H(); void SET_0_L(); void SET_0_HL(); void SET_0_A();

    void SET_1_B(); void SET_1_C(); void SET_1_D(); void SET_1_E(); void SET_1_H(); void SET_1_L(); void SET_1_HL(); void SET_1_A();

    //0xD0~0xDF

    void SET_2_B(); void SET_2_C(); void SET_2_D(); void SET_2_E(); void SET_2_H(); void SET_2_L(); void SET_2_HL(); void SET_2_A();

    void SET_3_B(); void SET_3_C(); void SET_3_D(); void SET_3_E(); void SET_3_H(); void SET_3_L(); void SET_3_HL(); void SET_3_A();

    //0xE0~0xEF

    void SET_4_B(); void SET_4_C(); void SET_4_D(); void SET_4_E(); void SET_4_H(); void SET_4_L(); void SET_4_HL(); void SET_4_A();

    void SET_5_B(); void SET_5_C(); void SET_5_D(); void SET_5_E(); void SET_5_H(); void SET_5_L(); void SET_5_HL(); void SET_5_A();

    //0xF0~0xFF

    void SET_6_B(); void SET_6_C(); void SET_6_D(); void SET_6_E(); void SET_6_H(); void SET_6_L(); void SET_6_HL(); void SET_6_A();

    void SET_7_B(); void SET_7_C(); void SET_7_D(); void SET_7_E(); void SET_7_H(); void SET_7_L(); void SET_7_HL(); void SET_7_A();

    Bus* bus = nullptr;

private:
    lr35902* cpu = nullptr;
    

    void rlc(uint8_t* u8);
    void rlc(uint16_t* addr);

    void rrc(uint8_t* u8);
    void rrc(uint16_t* addr);

    void rl(uint8_t* u8);
    void rl(uint16_t* addr);

    void rr(uint8_t* u8);
    void rr(uint16_t* addr);

    void sla(uint8_t* u8);
    void sla(uint16_t* addr);

    void sra(uint8_t* u8);
    void sra(uint16_t* addr);

    void swap(uint8_t* u8);
    void swap(uint16_t* addr);

    void srl(uint8_t* u8);
    void srl(uint16_t* addr);

    void bit(uint8_t* u8, uint8_t n);
    void bit(uint16_t* addr, uint8_t n);

    void res(uint8_t* u8, uint8_t n);
    void res(uint16_t* addr, uint8_t n);

    void set(uint8_t* u8, uint8_t n);
    void set(uint16_t* addr, uint8_t n);

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t data);


};

#endif // CB_H
