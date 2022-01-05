#include "lr35902.h"
#include "cb.h"
#include "bus.h"


Cb::Cb()
{

}

uint8_t Cb::read(uint16_t addr)
{
    return bus->read(addr);
}

void Cb::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
}



void Cb::rlc(uint8_t* u8)
{

    uint8_t value = *u8;

    if ((value & 0x80) == 0x80) {
        cpu->F.bits.C = 1;

        value <<= 1;

        value |= 0x01;
    }
    else {
        cpu->F.value = 0x00;

        value <<= 1;
    }

    if (value == 0x00) {

        cpu->F.bits.Z = 1;
    }

    *u8 = static_cast<uint8_t>(value);

}

void Cb::rlc(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x80) == 0x80) {
        cpu->F.bits.C = 1;

        value <<= 1;

        value |= 0x01;
    }
    else {
        cpu->F.value = 0x00;

        value <<= 1;
    }

    if (value == 0x00) {

        cpu->F.bits.Z = 1;
    }

    write(*addr, static_cast<uint8_t>(value));

}

void Cb::rrc(uint8_t* u8)
{
    uint8_t value = *u8;

    if ((value & 0x01) == 0x01) {

        cpu->F.bits.C = 1;

        value >>= 1;

        value |= 0x08;

    }
    else {

        cpu->F.value = 0x00;

        value >>= 1;

    }

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    *u8 = static_cast<uint8_t>(value);

}

void Cb::rrc(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x01) == 0x01) {

        cpu->F.bits.C = 1;

        value >>= 1;

        value |= 0x08;

    }
    else {

        cpu->F.value = 0x00;

        value >>= 1;

    }

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    write(*addr, static_cast<uint8_t>(value));

}

void Cb::rl(uint8_t* u8)
{
    uint8_t value = *u8;

    if ((value & 0x80) == 0x80) {

        value <<= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x01;
        }

        cpu->F.bits.C = 1;
    }
    else {
        value <<= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x01;
        }

        cpu->F.bits.C = 0;
    }

    *u8 = static_cast<uint8_t>(value);
}

void Cb::rl(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x80) == 0x80) {

        value <<= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x01;
        }

        cpu->F.bits.C = 1;
    }
    else {
        value <<= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x01;
        }

        cpu->F.bits.C = 0;
    }

    write(*addr, static_cast<uint8_t>(value));
}

void Cb::rr(uint8_t* u8)
{
    uint8_t value = *u8;

    if ((value & 0x01) == 0x01) {

        value >>= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x80;
        }

        cpu->F.bits.C = 1;
    }
    else {
        value >>= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x80;
        }

        cpu->F.bits.C = 0;
    }

    *u8 = static_cast<uint8_t>(value);
}

void Cb::rr(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x01) == 0x01) {

        value >>= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x80;
        }

        cpu->F.bits.C = 1;
    }
    else {
        value >>= 1;

        if (cpu->F.bits.C == 0x01) {
            value |= 0x80;
        }

        cpu->F.bits.C = 0;
    }

    write(*addr, static_cast<uint8_t>(value));
}


void Cb::sla(uint8_t* u8)
{
    uint8_t value = *u8;

    if ((value & 0x80) == 0x80) {
        cpu->F.bits.C = 1;
    }
    else {
        cpu->F.value = 0x00;
    }

    value <<= 1;

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    *u8 = static_cast<uint8_t>(value);

}

void Cb::sla(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x80) == 0x80) {
        cpu->F.bits.C = 1;
    }
    else {
        cpu->F.value = 0x00;
    }

    value <<= 1;

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    write(*addr, static_cast<uint8_t>(value));
}

void Cb::sra(uint8_t* u8)
{
    uint8_t value = *u8;

    if ((value & 0x01) == 0x01) {
        cpu->F.bits.C = 1;
    }
    else {
        cpu->F.value = 0x00;
    }

    if ((value & 0x80) == 0x80) {
        value >>= 1;
        value |= 0x80;
    }
    else {
        value >>= 1;
    }

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    *u8 = static_cast<uint8_t>(value);

}

void Cb::sra(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x01) == 0x01) {
        cpu->F.bits.C = 1;
    }
    else {
        cpu->F.value = 0x00;
    }

    if ((value & 0x80) == 0x80) {
        value >>= 1;
        value |= 0x80;
    }
    else {
        value >>= 1;
    }

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    write(*addr, static_cast<uint8_t>(value));
}

void Cb::swap(uint8_t* u8)
{
    cpu->F.value = 0x00;

    uint8_t lower = (*u8 & 0x0F);
    uint8_t upper = (*u8 >> 4 & 0x0F);

    uint8_t result = (lower << 4 | upper);

    *u8 = static_cast<uint8_t>(result);

    if (result == 0x00) {
        cpu->F.bits.Z = 1;
    }

}

void Cb::swap(uint16_t* addr)
{
    cpu->F.value = 0x00;

    uint8_t value = read(*addr);

    uint8_t lower = (value & 0x0F);
    uint8_t upper = (value >> 4 & 0x0F);

    uint8_t result = (lower << 4 | upper);

    write(*addr, static_cast<uint8_t>(result));

    if (result == 0x00) {
        cpu->F.bits.Z = 1;
    }

}

void Cb::srl(uint8_t* u8)
{
    uint8_t value = *u8;

    if ((value & 0x01) == 0x01) {
        cpu->F.bits.C = 1;
    }
    else {
        cpu->F.value = 0x00;
    }

    value >>= 1;

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    *u8 = static_cast<uint8_t>(value);

}

void Cb::srl(uint16_t* addr)
{
    uint8_t value = read(*addr);

    if ((value & 0x01) == 0x01) {
        cpu->F.bits.C = 1;
    }
    else {
        cpu->F.value = 0x00;
    }

    value >>= 1;

    if (value == 0x00) {
        cpu->F.bits.Z = 1;
    }

    write(*addr, static_cast<uint8_t>(value));
}

void Cb::bit(uint8_t* u8, uint8_t n)
{
    uint8_t value = *u8;

    if (((value >> n) & 0x01) == 0x00) {
        cpu->F.bits.Z = 1;
    }
    else {
        cpu->F.bits.Z = 0;
    }

    cpu->F.bits.H = 1;
    cpu->F.bits.N = 0;

    *u8 = static_cast<uint8_t>(value);
}

void Cb::bit(uint16_t* addr, uint8_t n)
{
    uint8_t value = read(*addr);

    if (((value >> n) & 0x01) == 0x00) {
        cpu->F.bits.Z = 1;
    }
    else {
        cpu->F.bits.Z = 0;
    }

    cpu->F.bits.H = 1;
    cpu->F.bits.N = 0;

    write(*addr, static_cast<uint8_t>(value));
}

void Cb::res(uint8_t* u8, uint8_t n)
{
    uint8_t result = *u8 & ~(1 << n);

    *u8 = static_cast<uint8_t>(result);
}

void Cb::res(uint16_t* addr, uint8_t n)
{
    uint8_t value = read(*addr);

    uint8_t result = value & ~(1 << n);

    write(*addr, static_cast<uint8_t>(result));
}

void Cb::set(uint8_t* u8, uint8_t n)
{
    uint8_t result = *u8 | (1 << n);

    *u8 = static_cast<uint8_t>(result);
}

void Cb::set(uint16_t* addr, uint8_t n)
{
    uint8_t value = read(*addr);

    uint8_t result = value | (1 << n);

    write(*addr, static_cast<uint8_t>(result));
}


void Cb::RLC_B()
{
    cpu->PC++;

    rlc(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RLC_C()
{
    cpu->PC++;

    rlc(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RLC_D()
{
    cpu->PC++;

    rlc(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RLC_E()
{
    cpu->PC++;

    rlc(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RLC_H()
{
    cpu->PC++;

    rlc(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RLC_L()
{
    cpu->PC++;

    rlc(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RLC_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    rlc(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RLC_A()
{
    cpu->PC++;

    rlc(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_B()
{
    cpu->PC++;

    rrc(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_C()
{
    cpu->PC++;

    rrc(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_D()
{
    cpu->PC++;

    rrc(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_E()
{
    cpu->PC++;

    rrc(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_H()
{
    cpu->PC++;

    rrc(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_L()
{
    cpu->PC++;

    rrc(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RRC_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    rrc(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RRC_A()
{
    cpu->PC++;

    rrc(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_B()
{
    cpu->PC++;

    rl(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_C()
{
    cpu->PC++;

    rl(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_D()
{
    cpu->PC++;

    rl(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_E()
{
    cpu->PC++;

    rl(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_H()
{
    cpu->PC++;

    rl(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_L()
{
    cpu->PC++;

    rl(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RL_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    rl(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RL_A()
{
    cpu->PC++;

    rl(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_B()
{
    cpu->PC++;

    rr(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_C()
{
    cpu->PC++;

    rr(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_D()
{
    cpu->PC++;

    rr(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_E()
{
    cpu->PC++;

    rr(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_H()
{
    cpu->PC++;

    rr(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_L()
{
    cpu->PC++;

    rr(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RR_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    rr(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RR_A()
{
    cpu->PC++;

    rr(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_B()
{
    cpu->PC++;

    sla(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_C()
{
    cpu->PC++;

    sla(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_D()
{
    cpu->PC++;

    sla(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_E()
{
    cpu->PC++;

    sla(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_H()
{
    cpu->PC++;

    sla(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_L()
{
    cpu->PC++;

    sla(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SLA_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    sla(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SLA_A()
{
    cpu->PC++;

    sla(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRA_B()
{
    cpu->PC++;

    sra(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}


void Cb::SRA_C()
{
    cpu->PC++;

    sra(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRA_D()
{
    cpu->PC++;

    sra(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRA_E()
{
    cpu->PC++;

    sra(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}


void Cb::SRA_H()
{
    cpu->PC++;

    sra(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}


void Cb::SRA_L()
{
    cpu->PC++;

    sra(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRA_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    sra(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SRA_A()
{
    cpu->PC++;

    sra(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_B()
{
    cpu->PC++;

    swap(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_C()
{
    cpu->PC++;

    swap(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_D()
{
    cpu->PC++;

    swap(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_E()
{
    cpu->PC++;

    swap(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_H()
{
    cpu->PC++;

    swap(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_L()
{
    cpu->PC++;

    swap(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SWAP_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    swap(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SWAP_A()
{
    cpu->PC++;

    swap(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_B()
{
    cpu->PC++;

    srl(&cpu->B);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_C()
{
    cpu->PC++;

    srl(&cpu->C);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_D()
{
    cpu->PC++;

    srl(&cpu->D);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_E()
{
    cpu->PC++;

    srl(&cpu->E);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_H()
{
    cpu->PC++;

    srl(&cpu->H);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_L()
{
    cpu->PC++;

    srl(&cpu->L);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SRL_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    srl(&addr);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SRL_A()
{
    cpu->PC++;

    srl(&cpu->A);

    cpu->PC++;

    cpu->cycles += 2;
}


void Cb::BIT_0_B()
{
    cpu->PC++;

    bit(&cpu->B, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_0_C()
{
    cpu->PC++;

    bit(&cpu->C, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_0_D()
{
    cpu->PC++;

    bit(&cpu->D, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_0_E()
{
    cpu->PC++;

    bit(&cpu->E, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_0_H()
{
    cpu->PC++;

    bit(&cpu->H, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_0_L()
{
    cpu->PC++;

    bit(&cpu->L, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_0_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 0);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_0_A()
{
    cpu->PC++;

    bit(&cpu->A, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_B()
{
    cpu->PC++;

    bit(&cpu->B, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_C()
{
    cpu->PC++;

    bit(&cpu->C, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_D()
{
    cpu->PC++;

    bit(&cpu->D, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_E()
{
    cpu->PC++;

    bit(&cpu->E, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_H()
{
    cpu->PC++;

    bit(&cpu->H, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_L()
{
    cpu->PC++;

    bit(&cpu->L, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_1_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 1);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_1_A()
{
    cpu->PC++;

    bit(&cpu->A, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_B()
{
    cpu->PC++;

    bit(&cpu->B, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_C()
{
    cpu->PC++;

    bit(&cpu->C, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_D()
{
    cpu->PC++;

    bit(&cpu->D, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_E()
{
    cpu->PC++;

    bit(&cpu->E, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_H()
{
    cpu->PC++;

    bit(&cpu->H, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_L()
{
    cpu->PC++;

    bit(&cpu->L, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_2_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 2);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_2_A()
{
    cpu->PC++;

    bit(&cpu->A, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_B()
{
    cpu->PC++;

    bit(&cpu->A, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_C()
{
    cpu->PC++;

    bit(&cpu->C, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_D()
{
    cpu->PC++;

    bit(&cpu->D, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_E()
{
    cpu->PC++;

    bit(&cpu->E, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_H()
{
    cpu->PC++;

    bit(&cpu->H, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_L()
{
    cpu->PC++;

    bit(&cpu->L, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_3_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 3);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_3_A()
{
    cpu->PC++;

    bit(&cpu->A, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_B()
{
    cpu->PC++;

    bit(&cpu->B, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_C()
{
    cpu->PC++;

    bit(&cpu->C, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_D()
{
    cpu->PC++;

    bit(&cpu->D, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_E()
{
    cpu->PC++;

    bit(&cpu->E, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_H()
{
    cpu->PC++;

    bit(&cpu->H, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_L()
{
    cpu->PC++;

    bit(&cpu->L, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_4_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 4);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_4_A()
{
    cpu->PC++;

    bit(&cpu->A, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_B()
{
    cpu->PC++;

    bit(&cpu->B, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_C()
{
    cpu->PC++;

    bit(&cpu->C, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_D()
{
    cpu->PC++;

    bit(&cpu->D, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_E()
{
    cpu->PC++;

    bit(&cpu->E, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_H()
{
    cpu->PC++;

    bit(&cpu->H, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_L()
{
    cpu->PC++;

    bit(&cpu->L, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_5_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 5);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_5_A()
{
    cpu->PC++;

    bit(&cpu->A, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_B()
{
    cpu->PC++;

    bit(&cpu->B, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_C()
{
    cpu->PC++;

    bit(&cpu->C, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_D()
{
    cpu->PC++;

    bit(&cpu->D, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_E()
{
    cpu->PC++;

    bit(&cpu->E, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_H()
{
    cpu->PC++;

    bit(&cpu->H, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_L()
{
    cpu->PC++;

    bit(&cpu->L, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_6_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 6);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_6_A()
{
    cpu->PC++;

    bit(&cpu->A, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_B()
{
    cpu->PC++;

    bit(&cpu->B, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_C()
{
    cpu->PC++;

    bit(&cpu->C, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_D()
{
    cpu->PC++;

    bit(&cpu->D, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_E()
{
    cpu->PC++;

    bit(&cpu->E, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_H()
{
    cpu->PC++;

    bit(&cpu->H, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_L()
{
    cpu->PC++;

    bit(&cpu->L, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::BIT_7_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    bit(&addr, 7);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::BIT_7_A()
{
    cpu->PC++;

    bit(&cpu->A, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_B()
{
    cpu->PC++;

    res(&cpu->B, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_C()
{
    cpu->PC++;

    res(&cpu->C, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_D()
{
    cpu->PC++;

    res(&cpu->D, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_E()
{
    cpu->PC++;

    res(&cpu->E, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_H()
{
    cpu->PC++;

    res(&cpu->H, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_L()
{
    cpu->PC++;

    res(&cpu->L, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_0_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 0);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_0_A()
{
    cpu->PC++;

    res(&cpu->A, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_B()
{
    cpu->PC++;

    res(&cpu->B, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_C()
{
    cpu->PC++;

    res(&cpu->C, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_D()
{
    cpu->PC++;

    res(&cpu->D, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_E()
{
    cpu->PC++;

    res(&cpu->E, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_H()
{
    cpu->PC++;

    res(&cpu->H, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_L()
{
    cpu->PC++;

    res(&cpu->L, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_1_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 1);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_1_A()
{
    cpu->PC++;

    res(&cpu->A, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_B()
{
    cpu->PC++;

    res(&cpu->B, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_C()
{
    cpu->PC++;

    res(&cpu->C, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_D()
{
    cpu->PC++;

    res(&cpu->D, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_E()
{
    cpu->PC++;

    res(&cpu->E, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_H()
{
    cpu->PC++;

    res(&cpu->H, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_L()
{
    cpu->PC++;

    res(&cpu->L, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_2_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 2);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_2_A()
{
    cpu->PC++;

    res(&cpu->A, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_B()
{
    cpu->PC++;

    res(&cpu->B, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_C()
{
    cpu->PC++;

    res(&cpu->C, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_D()
{
    cpu->PC++;

    res(&cpu->D, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_E()
{
    cpu->PC++;

    res(&cpu->E, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_H()
{
    cpu->PC++;

    res(&cpu->H, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_L()
{
    cpu->PC++;

    res(&cpu->L, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_3_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 3);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_3_A()
{
    cpu->PC++;

    res(&cpu->A, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_B()
{
    cpu->PC++;

    res(&cpu->B, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_C()
{
    cpu->PC++;

    res(&cpu->C, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_D()
{
    cpu->PC++;

    res(&cpu->D, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_E()
{
    cpu->PC++;

    res(&cpu->E, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_H()
{
    cpu->PC++;

    res(&cpu->H, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_L()
{
    cpu->PC++;

    res(&cpu->L, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_4_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 4);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_4_A()
{
    cpu->PC++;

    res(&cpu->A, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_B()
{
    cpu->PC++;

    res(&cpu->B, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_C()
{
    cpu->PC++;

    res(&cpu->C, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_D()
{
    cpu->PC++;

    res(&cpu->D, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_E()
{
    cpu->PC++;

    res(&cpu->E, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_H()
{
    cpu->PC++;

    res(&cpu->H, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_L()
{
    cpu->PC++;

    res(&cpu->L, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_5_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 5);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_5_A()
{
    cpu->PC++;

    res(&cpu->A, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_B()
{
    cpu->PC++;

    res(&cpu->B, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_C()
{
    cpu->PC++;

    res(&cpu->C, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_D()
{
    cpu->PC++;

    res(&cpu->D, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_E()
{
    cpu->PC++;

    res(&cpu->E, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_H()
{
    cpu->PC++;

    res(&cpu->H, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_L()
{
    cpu->PC++;

    res(&cpu->L, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_6_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 6);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_6_A()
{
    cpu->PC++;

    res(&cpu->A, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_B()
{
    cpu->PC++;

    res(&cpu->B, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_C()
{
    cpu->PC++;

    res(&cpu->C, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_D()
{
    cpu->PC++;

    res(&cpu->D, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_E()
{
    cpu->PC++;

    res(&cpu->E, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_H()
{
    cpu->PC++;

    res(&cpu->H, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_L()
{
    cpu->PC++;

    res(&cpu->L, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::RES_7_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    res(&addr, 7);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::RES_7_A()
{
    cpu->PC++;

    res(&cpu->A, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_B()
{
    cpu->PC++;

    set(&cpu->B, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_C()
{
    cpu->PC++;

    set(&cpu->C, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_D()
{
    cpu->PC++;

    set(&cpu->D, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_E()
{
    cpu->PC++;

    set(&cpu->E, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_H()
{
    cpu->PC++;

    set(&cpu->H, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_L()
{
    cpu->PC++;

    set(&cpu->L, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_0_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 0);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_0_A()
{
    cpu->PC++;

    set(&cpu->A, 0);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_B()
{
    cpu->PC++;

    set(&cpu->B, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_C()
{
    cpu->PC++;

    set(&cpu->C, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_D()
{
    cpu->PC++;

    set(&cpu->D, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_E()
{
    cpu->PC++;

    set(&cpu->E, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_H()
{
    cpu->PC++;

    set(&cpu->H, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_L()
{
    cpu->PC++;

    set(&cpu->L, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_1_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 1);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_1_A()
{
    cpu->PC++;

    set(&cpu->A, 1);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_B()
{
    cpu->PC++;

    set(&cpu->B, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_C()
{
    cpu->PC++;

    set(&cpu->C, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_D()
{
    cpu->PC++;

    set(&cpu->D, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_E()
{
    cpu->PC++;

    set(&cpu->E, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_H()
{
    cpu->PC++;

    set(&cpu->H, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_L()
{
    cpu->PC++;

    set(&cpu->L, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_2_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 2);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_2_A()
{
    cpu->PC++;

    set(&cpu->A, 2);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_B()
{
    cpu->PC++;

    set(&cpu->B, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_C()
{
    cpu->PC++;

    set(&cpu->C, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_D()
{
    cpu->PC++;

    set(&cpu->D, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_E()
{
    cpu->PC++;

    set(&cpu->E, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_H()
{
    cpu->PC++;

    set(&cpu->H, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_L()
{
    cpu->PC++;

    set(&cpu->L, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_3_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 3);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_3_A()
{
    cpu->PC++;

    set(&cpu->A, 3);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_B()
{
    cpu->PC++;

    set(&cpu->B, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_C()
{
    cpu->PC++;

    set(&cpu->C, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_D()
{
    cpu->PC++;

    set(&cpu->D, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_E()
{
    cpu->PC++;

    set(&cpu->E, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_H()
{
    cpu->PC++;

    set(&cpu->H, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_L()
{
    cpu->PC++;

    set(&cpu->L, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_4_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 4);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_4_A()
{
    cpu->PC++;

    set(&cpu->A, 4);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_B()
{
    cpu->PC++;

    set(&cpu->B, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_C()
{
    cpu->PC++;

    set(&cpu->C, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_D()
{
    cpu->PC++;

    set(&cpu->D, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_E()
{
    cpu->PC++;

    set(&cpu->E, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_H()
{
    cpu->PC++;

    set(&cpu->H, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_L()
{
    cpu->PC++;

    set(&cpu->L, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_5_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 5);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_5_A()
{
    cpu->PC++;

    set(&cpu->A, 5);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_B()
{
    cpu->PC++;

    set(&cpu->B, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_C()
{
    cpu->PC++;

    set(&cpu->C, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_D()
{
    cpu->PC++;

    set(&cpu->D, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_E()
{
    cpu->PC++;

    set(&cpu->E, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_H()
{
    cpu->PC++;

    set(&cpu->H, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_L()
{
    cpu->PC++;

    set(&cpu->L, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_6_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 6);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_6_A()
{
    cpu->PC++;

    set(&cpu->A, 6);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_B()
{
    cpu->PC++;

    set(&cpu->B, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_C()
{
    cpu->PC++;

    set(&cpu->C, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_D()
{
    cpu->PC++;

    set(&cpu->D, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_E()
{
    cpu->PC++;

    set(&cpu->E, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_H()
{
    cpu->PC++;

    set(&cpu->H, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_L()
{
    cpu->PC++;

    set(&cpu->L, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::SET_7_HL()
{
    cpu->PC++;

    uint16_t addr = (cpu->H << 8 | cpu->L);

    set(&addr, 7);

    cpu->PC++;

    cpu->cycles += 4;
}

void Cb::SET_7_A()
{
    cpu->PC++;

    set(&cpu->A, 7);

    cpu->PC++;

    cpu->cycles += 2;
}

void Cb::process(uint16_t opcode) {

    switch (opcode)
    {
    case 0x00:
        RLC_B();
        break;
    case 0x01:
        RLC_C();
        break;
    case 0x02:
        RLC_D();
        break;
    case 0x03:
        RLC_E();
        break;
    case 0x04:
        RLC_H();
        break;
    case 0x05:
        RLC_L();
        break;
    case 0x06:
        RLC_HL();
        break;
    case 0x07:
        RLC_A();
        break;
    case 0x08:
        RRC_B();
        break;
    case 0x09:
        RRC_C();
        break;
    case 0x0A:
        RRC_D();
        break;
    case 0x0B:
        RRC_E();
        break;
    case 0x0C:
        RRC_H();
        break;
    case 0x0D:
        RRC_L();
        break;
    case 0x0E:
        RRC_HL();
        break;
    case 0x0F:
        RRC_A();
        break;
    case 0x10:
        RL_B();
        break;
    case 0x12:
        RL_C();
        break;
    case 0x13:
        RL_D();
        break;
    case 0x14:
        RL_E();
        break;
    case 0x15:
        RL_L();
        break;
    case 0x16:
        RL_HL();
        break;
    case 0x17:
        RL_A();
        break;
    case 0x18:
        RR_B();
        break;
    case 0x19:
        RR_C();
        break;
    case 0x1A:
        RR_D();
        break;
    case 0x1B:
        RR_E();
        break;
    case 0x1C:
        RR_H();
        break;
    case 0x1D:
        RR_L();
        break;
    case 0x1E:
        RR_HL();
        break;
    case 0x1F:
        RR_A();
        break;
    case 0x20:
        SLA_B();
        break;
    case 0x21:
        SLA_C();
        break;
    case 0x22:
        SLA_D();
        break;
    case 0x23:
        SLA_E();
        break;
    case 0x24:
        SLA_H();
        break;
    case 0x25:
        SLA_L();
        break;
    case 0x26:
        SLA_HL();
        break;
    case 0x27:
        SLA_A();
        break;
    case 0x28:
        SRA_B();
        break;
    case 0x29:
        SRA_C();
        break;
    case 0x2A:
        SRA_D();
        break;
    case 0x2B:
        SRA_E();
        break;
    case 0x2C:
        SRA_H();
        break;
    case 0x2D:
        SRA_L();
        break;
    case 0x2E:
        SRA_HL();
        break;
    case 0x2F:
        SRA_A();
        break;
    case 0x30:
        SWAP_B();
        break;
    case 0x31:
        SWAP_C();
        break;
    case 0x32:
        SWAP_D();
        break;
    case 0x33:
        SWAP_E();
        break;
    case 0x34:
        SWAP_H();
        break;
    case 0x35:
        SWAP_L();
        break;
    case 0x36:
        SWAP_HL();
        break;
    case 0x37:
        SWAP_A();
        break;
    case 0x38:
        SRL_B();
        break;
    case 0x39:
        SRL_C();
        break;
    case 0x3A:
        SRL_D();
        break;
    case 0x3B:
        SRL_E();
        break;
    case 0x3C:
        SRL_H();
        break;
    case 0x3D:
        SRL_L();
        break;
    case 0x3E:
        SRL_HL();
        break;
    case 0x3F:
        SRL_A();
        break;
    case 0x40:
        BIT_0_B();
        break;
    case 0x41:
        BIT_0_C();
        break;
    case 0x42:
        BIT_0_D();
        break;
    case 0x43:
        BIT_0_E();
        break;
    case 0x44:
        BIT_0_H();
        break;
    case 0x45:
        BIT_0_L();
        break;
    case 0x46:
        BIT_0_HL();
        break;
    case 0x47:
        BIT_0_A();
        break;
    case 0x48:
        BIT_1_B();
        break;
    case 0x49:
        BIT_1_C();
        break;
    case 0x4A:
        BIT_1_D();
        break;
    case 0x4B:
        BIT_1_E();
        break;
    case 0x4C:
        BIT_1_H();
        break;
    case 0x4D:
        BIT_1_L();
        break;
    case 0x4E:
        BIT_1_HL();
        break;
    case 0x4F:
        BIT_1_A();
        break;
    case 0x50:
        BIT_2_B();
        break;
    case 0x51:
        BIT_2_C();
        break;
    case 0x52:
        BIT_2_D();
        break;
    case 0x53:
        BIT_2_E();
        break;
    case 0x54:
        BIT_2_H();
        break;
    case 0x55:
        BIT_2_L();
        break;
    case 0x56:
        BIT_2_HL();
        break;
    case 0x57:
        BIT_2_A();
        break;
    case 0x58:
        BIT_3_B();
        break;
    case 0x59:
        BIT_3_C();
        break;
    case 0x5A:
        BIT_3_D();
        break;
    case 0x5B:
        BIT_3_E();
        break;
    case 0x5C:
        BIT_3_H();
        break;
    case 0x5D:
        BIT_3_L();
        break;
    case 0x5E:
        BIT_3_HL();
        break;
    case 0x5F:
        BIT_3_A();
        break;
    case 0x60:
        BIT_4_B();
        break;
    case 0x61:
        BIT_4_C();
        break;
    case 0x62:
        BIT_4_D();
        break;
    case 0x63:
        BIT_4_E();
        break;
    case 0x64:
        BIT_4_H();
        break;
    case 0x65:
        BIT_4_L();
        break;
    case 0x66:
        BIT_4_HL();
        break;
    case 0x67:
        BIT_4_A();
        break;
    case 0x68:
        BIT_5_B();
        break;
    case 0x69:
        BIT_5_C();
        break;
    case 0x6A:
        BIT_5_D();
        break;
    case 0x6B:
        BIT_5_E();
        break;
    case 0x6C:
        BIT_5_H();
        break;
    case 0x6D:
        BIT_5_L();
        break;
    case 0x6E:
        BIT_5_HL();
        break;
    case 0x6F:
        BIT_5_A();
        break;
    case 0x70:
        BIT_6_B();
        break;
    case 0x71:
        BIT_6_C();
        break;
    case 0x72:
        BIT_6_D();
        break;
    case 0x73:
        BIT_6_E();
        break;
    case 0x74:
        BIT_6_H();
        break;
    case 0x75:
        BIT_6_L();
        break;
    case 0x76:
        BIT_6_HL();
        break;
    case 0x77:
        BIT_6_A();
        break;
    case 0x78:
        BIT_7_B();
        break;
    case 0x79:
        BIT_7_C();
        break;
    case 0x7A:
        BIT_7_D();
        break;
    case 0x7B:
        BIT_7_E();
        break;
    case 0x7C:
        BIT_7_H();
        break;
    case 0x7D:
        BIT_7_L();
        break;
    case 0x7E:
        BIT_7_HL();
        break;
    case 0x7F:
        BIT_7_A();
        break;
    case 0x80:
        RES_0_B();
        break;
    case 0x81:
        RES_0_C();
        break;
    case 0x82:
        RES_0_D();
        break;
    case 0x83:
        RES_0_E();
        break;
    case 0x84:
        RES_0_H();
        break;
    case 0x85:
        RES_0_L();
        break;
    case 0x86:
        RES_0_HL();
        break;
    case 0x87:
        RES_0_A();
        break;
    case 0x88:
        RES_1_B();
        break;
    case 0x89:
        RES_1_C();
        break;
    case 0x8A:
        RES_1_D();
        break;
    case 0x8B:
        RES_1_E();
        break;
    case 0x8C:
        RES_1_H();
        break;
    case 0x8D:
        RES_1_L();
        break;
    case 0x8E:
        RES_1_HL();
        break;
    case 0x8F:
        RES_1_A();
        break;
    case 0x90:
        RES_2_B();
        break;
    case 0x91:
        RES_2_C();
        break;
    case 0x92:
        RES_2_D();
        break;
    case 0x93:
        RES_2_E();
        break;
    case 0x94:
        RES_2_H();
        break;
    case 0x95:
        RES_2_L();
        break;
    case 0x96:
        RES_2_HL();
        break;
    case 0x97:
        RES_2_A();
        break;
    case 0x98:
        RES_3_B();
        break;
    case 0x99:
        RES_3_C();
        break;
    case 0x9A:
        RES_3_D();
        break;
    case 0x9B:
        RES_3_E();
        break;
    case 0x9C:
        RES_3_H();
        break;
    case 0x9D:
        RES_3_L();
        break;
    case 0x9E:
        RES_3_HL();
        break;
    case 0x9F:
        RES_3_A();
        break;
    case 0xA0:
        RES_4_B();
        break;
    case 0xA1:
        RES_4_C();
        break;
    case 0xA2:
        RES_4_D();
        break;
    case 0xA3:
        RES_4_E();
        break;
    case 0xA4:
        RES_4_H();
        break;
    case 0xA5:
        RES_4_L();
        break;
    case 0xA6:
        RES_4_HL();
        break;
    case 0xA7:
        RES_4_A();
        break;
    case 0xA8:
        RES_5_B();
        break;
    case 0xA9:
        RES_5_C();
        break;
    case 0xAA:
        RES_5_D();
        break;
    case 0xAB:
        RES_5_E();
        break;
    case 0xAC:
        RES_5_H();
        break;
    case 0xAD:
        RES_5_L();
        break;
    case 0xAE:
        RES_5_HL();
        break;
    case 0xAF:
        RES_5_A();
        break;
    case 0xB0:
        RES_6_B();
        break;
    case 0xB1:
        RES_6_C();
        break;
    case 0xB2:
        RES_6_D();
        break;
    case 0xB3:
        RES_6_E();
        break;
    case 0xB4:
        RES_6_H();
        break;
    case 0xB5:
        RES_6_L();
        break;
    case 0xB6:
        RES_6_HL();
        break;
    case 0xB7:
        RES_6_A();
        break;
    case 0xB8:
        RES_7_B();
        break;
    case 0xB9:
        RES_7_C();
        break;
    case 0xBA:
        RES_7_D();
        break;
    case 0xBB:
        RES_7_E();
        break;
    case 0xBC:
        RES_7_H();
        break;
    case 0xBD:
        RES_7_L();
        break;
    case 0xBE:
        RES_7_HL();
        break;
    case 0xBF:
        RES_7_A();
        break;
    case 0xC0:
        SET_0_B();
        break;
    case 0xC1:
        SET_0_C();
        break;
    case 0xC2:
        SET_0_D();
        break;
    case 0xC3:
        SET_0_E();
        break;
    case 0xC4:
        SET_0_H();
        break;
    case 0xC5:
        SET_0_L();
        break;
    case 0xC6:
        SET_0_HL();
        break;
    case 0xC7:
        SET_0_A();
        break;
    case 0xC8:
        SET_1_B();
        break;
    case 0xC9:
        SET_1_C();
        break;
    case 0xCA:
        SET_1_D();
        break;
    case 0xCB:
        SET_1_E();
        break;
    case 0xCC:
        SET_1_H();
        break;
    case 0xCD:
        SET_1_L();
        break;
    case 0xCE:
        SET_1_HL();
        break;
    case 0xCF:
        SET_1_A();
        break;
    case 0xD0:
        SET_2_B();
        break;
    case 0xD1:
        SET_2_C();
        break;
    case 0xD2:
        SET_2_D();
        break;
    case 0xD3:
        SET_2_E();
        break;
    case 0xD4:
        SET_2_H();
        break;
    case 0xD5:
        SET_2_L();
        break;
    case 0xD6:
        SET_2_HL();
        break;
    case 0xD7:
        SET_2_A();
        break;
    case 0xD8:
        SET_3_B();
        break;
    case 0xD9:
        SET_3_C();
        break;
    case 0xDA:
        SET_3_D();
        break;
    case 0xDB:
        SET_3_E();
        break;
    case 0xDC:
        SET_3_H();
        break;
    case 0xDD:
        SET_3_L();
        break;
    case 0xDE:
        SET_3_HL();
        break;
    case 0xDF:
        SET_3_A();
        break;
    case 0xE0:
        SET_4_B();
        break;
    case 0xE1:
        SET_4_C();
        break;
    case 0xE2:
        SET_4_D();
        break;
    case 0xE3:
        SET_4_E();
        break;
    case 0xE4:
        SET_4_H();
        break;
    case 0xE5:
        SET_4_L();
        break;
    case 0xE6:
        SET_4_HL();
        break;
    case 0xE7:
        SET_4_A();
        break;
    case 0xE8:
        SET_5_B();
        break;
    case 0xE9:
        SET_5_C();
        break;
    case 0xEA:
        SET_5_D();
        break;
    case 0xEB:
        SET_5_E();
        break;
    case 0xEC:
        SET_5_H();
        break;
    case 0xED:
        SET_5_L();
        break;
    case 0xEE:
        SET_5_HL();
        break;
    case 0xEF:
        SET_5_A();
        break;
    case 0xF0:
        SET_6_B();
        break;
    case 0xF1:
        SET_6_C();
        break;
    case 0xF2:
        SET_6_D();
        break;
    case 0xF3:
        SET_6_E();
        break;
    case 0xF4:
        SET_6_H();
        break;
    case 0xF5:
        SET_6_L();
        break;
    case 0xF6:
        SET_6_HL();
        break;
    case 0xF7:
        SET_6_A();
        break;
    case 0xF8:
        SET_7_B();
        break;
    case 0xF9:
        SET_7_C();
        break;
    case 0xFA:
        SET_7_D();
        break;
    case 0xFB:
        SET_7_E();
        break;
    case 0xFC:
        SET_7_H();
        break;
    case 0xFD:
        SET_7_L();
        break;
    case 0xFE:
        SET_7_HL();
        break;
    case 0xFF:
        SET_7_A();
        break;
    default:
        break;
    }

}
