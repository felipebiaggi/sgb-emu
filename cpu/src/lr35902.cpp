#include <iostream>
#include <stdio.h>
#include <string.h>
#include "lr35902.h"
#include "bus.h"

lr35902::lr35902() {

    cb.ConnectCpu(this);
    cb.ConnectBus(bus);
    reset();

}

lr35902::~lr35902() {

}

uint8_t lr35902::read(uint16_t addr) {
    return bus->read(addr);
}

void lr35902::ld(uint8_t* u8, uint16_t* addr)
{
    *u8 = read(*addr);
}

void lr35902::ld(uint8_t* upper, uint8_t* lower, uint8_t* u8)
{
    uint16_t addr = (*upper << 8 | *lower);

    write(addr, *u8);
}

void lr35902::ld_hlp(uint8_t* upper, uint8_t* lower, uint8_t* u8)
{
    uint16_t addr = (*upper << 8 | *lower);

    write(addr, *u8);

    addr++;

    *upper = (addr >> 8 & 0x00FF);
    *lower = (addr & 0x00FF);

}

void lr35902::ld_hlm(uint8_t* upper, uint8_t* lower, uint8_t* u8)
{
    uint16_t addr = (*upper << 8 | *lower);

    write(addr, *u8);

    addr--;

    *upper = (addr >> 8 & 0x00FF);
    *lower = (addr & 0x00FF);
}

void lr35902::ld(uint8_t* u8, uint8_t* value) {

    *u8 = *value;

}

void lr35902::inc(uint8_t* upper, uint8_t* lower) {

    uint16_t increment = (*upper << 8 | *lower);

    increment++;

    *upper = static_cast<uint8_t>(increment >> 8 & 0x00FF);
    *lower = static_cast<uint8_t>(increment & 0x00FF);
}


void lr35902::inc(uint8_t* u8) {

    F.bits.N = 0;

    uint8_t result = *u8 + 1;

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    if ((result & 0x0F) == 0x00) {
        F.bits.H = 1;
    }

    *u8 = static_cast<uint8_t>(result);
}

void lr35902::dec(uint8_t* u8) {

    F.bits.N = 1;

    uint8_t result = *u8 - 1;

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    if ((result & 0x0F) == 0x0F) {
        F.bits.H = 1;
    }

    *u8 = static_cast<uint8_t>(result);
}

//Opcode misterioso
void lr35902::add_hl(uint8_t* upper, uint8_t* lower)
{
    F.bits.N = 0;

    uint16_t value = (*upper << 8 | *lower);

    uint16_t HL = (H << 8 | L);

    uint32_t result = HL + value;

    //dunno
    //0x0FFF -> 0000 1111 1111 1111
    if ((HL & 0x0FFF) + (value & 0x0FFF) > 0x0FFF) {
        F.bits.H = 1;
    }

    //0x10000 -> 0001 0000 0000 0000 0000
    if (result & 0x10000) {
        F.bits.C = 1;
    }


    H = (static_cast<uint16_t>(result) >> 8 & 0x00FF);
    L = (static_cast<uint16_t>(result) & 0x00FF);

}

void lr35902::dec(uint8_t* upper, uint8_t* lower) {

    uint16_t decrement = (*upper << 8 | *lower);

    decrement--;

    *upper = static_cast<uint8_t>(decrement >> 8 & 0x0FF);
    *lower = static_cast<uint8_t>(decrement & 0x00FF);
}


uint8_t lr35902::add(uint8_t u8_1, uint8_t u8_2) {

    F.bits.N = 0;

    // u8_1 -> 0x08 -> 8
    // u8_2 -> 0x1B -> 27
    // 0x08 + 0x0B -> 0x23
    uint16_t result = u8_1 = u8_2;

    // (0x08 & 0xF) -> 0x8
    // (0x23 & 0xF) -> 0x3
    // 0x8 + 0x3 > 0xF
    if ((u8_1 & 0xF) + (u8_2 & 0xF) > 0xF) {
        F.bits.H = 1;
    }

    if ((result & 0x100) != 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 0;
    }

    return static_cast<uint8_t>(result);
}

//?????
uint8_t lr35902::add(uint8_t r8, uint16_t r16) {

    F.bits.N = 0;

    uint8_t value = read(r16);

    uint16_t result = r8 + value;

    if ((r8 & 0xF) + (value & 0xF) > 0xF) {
        F.bits.H = 1;
    }

    if ((result & 0x100) != 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return static_cast<uint8_t>(result);
}


uint8_t lr35902::adc(uint8_t u8_1, uint8_t u8_2)
{
    F.bits.N = 0;

    uint8_t carry = 0x00;

    if (F.bits.C == 0x01) {
        carry = 0x01;
    }

    // Clear flags
    F.value = 0x00;

    uint16_t result = u8_1 + u8_2 + carry;

    if ((u8_1 & 0xF) + (u8_2 & 0xF) + (carry) > 0xF) {
        F.bits.H = 1;
    }

    if ((result & 0x100) != 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return static_cast<uint8_t>(result);
}

uint8_t lr35902::adc(uint8_t u8, uint16_t r16)
{
    F.bits.N = 0;

    uint8_t value = read(r16);

    uint8_t carry = 0x00;

    if (F.bits.C == 0x01) {
        carry = 0x01;
    }

    F.value = 0x00;

    uint16_t result = u8 + value + carry;

    if ((u8 & 0xF) + (value & 0xF) + (carry) > 0xF) {
        F.bits.H = 1;
    }

    if ((result & 0x100) != 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return static_cast<uint8_t>(result);

}


uint8_t lr35902::sub(uint8_t u8_1, uint8_t u8_2)
{
    F.bits.N = 1;

    uint16_t result = u8_1 - u8_2;

    if (((u8_1 & 0x0F) - (u8_2 & 0x0F)) < 0) {
        F.bits.H = 0;
    }

    if (static_cast<int16_t>(result) < 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 0;
    }

    return static_cast<uint8_t>(result);
}


uint8_t lr35902::sub(uint8_t u8, uint16_t r16)
{
    F.bits.N = 1;

    uint8_t value = read(r16);

    uint16_t result = u8 - value;

    if (((u8 & 0x0F) - (value & 0x0F)) < 0) {
        F.bits.H = 0;
    }

    if (static_cast<int16_t>(result) < 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 0;
    }

    return static_cast<uint8_t>(result);
}


// SEC
uint8_t lr35902::sbc(uint8_t u8_1, uint8_t u8_2)
{
    F.bits.N = 1;

    uint8_t carry = 0x00;

    if (F.bits.C == 0x01) {
        carry = 0x01;
    }

    uint16_t result = u8_1 - u8_2 - carry;

    if (((u8_1 & 0x0F) - (u8_2 & 0x0F) - carry) < 0) {
        F.bits.H = 0;
    }

    if (static_cast<int16_t>(result) < 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 0;
    }


    return static_cast<uint8_t>(result);
}


uint8_t lr35902::sbc(uint8_t u8, uint16_t r16)
{
    F.bits.N = 1;

    uint8_t carry = 0x00;

    if (F.bits.C == 0x01) {
        carry = 0x01;
    }

    uint8_t value = read(r16);

    uint16_t result = u8 - value - carry;

    if (((u8 & 0x0F) - (value & 0x0F) - carry) < 0) {
        F.bits.H = 0;
    }

    if (static_cast<int16_t>(result) < 0) {
        F.bits.C = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 0;
    }


    return static_cast<uint8_t>(result);
}

// AND A, r8
// Bitwise AND between the value in r8 and A
// Z -> Set if result is 0
// H -> 1
// N -> 0
// C -> 0
uint8_t lr35902:: and_op(uint8_t u8_1, uint8_t u8_2)
{
    F.value = 0x00;

    F.bits.H = 1;

    uint8_t result = u8_1 & u8_2;

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return result;
}

uint8_t lr35902:: and_op(uint8_t u8, uint16_t r16)
{
    F.value = 0x00;

    F.bits.H = 1;

    uint8_t value = read(r16);

    uint8_t result = u8 & value;

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return result;
}


// XOR A, r8
// Bitwise XOR between the value in r8 and A
// Z -> Set if result is 0.
// N -> 0
// H -> 0
// C -> 0
uint8_t lr35902:: xor_op(uint8_t u8_1, uint8_t u8_2)
{
    F.value = 0x00;

    uint8_t result = u8_1 ^ u8_2;

    if (result == 0) {
        F.bits.Z = 1;
    }

    return result;
}

uint8_t lr35902:: xor_op(uint8_t u8, uint16_t r16)
{
    F.value = 0x00;

    uint8_t value = read(r16);

    uint8_t result = u8 ^ value;

    if (result == 0) {
        F.bits.Z = 1;
    }

    return result;
}

// OR A, r8
// Store into A the bitwise OR of the value in r8 and A.
// Z -> Set if result is 0.
// N -> 0
// H -> 0
// C -> 0
uint8_t lr35902:: or_op(uint8_t u8_1, uint8_t u8_2)
{
    F.value = 0x00;

    uint8_t result = u8_1 | u8_2;

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return result;
}

// OR A, [HL]
// Store into A the bitwise OR of the byte pointed to by HL and A.
// Z -> Set if result is 0.
// N -> 0
// H -> 0
// C -> 0
uint8_t lr35902:: or_op(uint8_t u8, uint16_t r16)
{
    F.value = 0x00;

    uint8_t value = read(r16);

    uint8_t result = u8 | value;

    if (result == 0x00) {
        F.bits.Z = 1;
    }

    return result;
}

// CP A, r8
// Subtract the value in r8 from A and set flags accordingly, but don't store the result.
// This is useful for Comparing values.
// Z -> Set if result is 0.
// N -> 1
// H -> Set if borrow from bit 4
// C -> Set if borrow (i.e if r8 > A)
void lr35902::cp(uint8_t u8_1, uint8_t u8_2)
{
    F.bits.N = 1;

    uint16_t result = u8_1 - u8_2;

    if (u8_1 < u8_2) {
        F.bits.C = 1;
    }

    if ((result & 0xF) > (u8_1 & 0xF)) {
        F.bits.H = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 1;
    }
}

void lr35902::cp(uint8_t u8, uint16_t r16)
{
    F.bits.N = 1;

    uint8_t value = read(r16);

    uint16_t result = u8 - value;

    if (u8 < value) {
        F.bits.C = 1;
    }

    if ((result & 0xF) > (u8 & 0xF)) {
        F.bits.H = 1;
    }

    if (result == 0x00) {
        F.bits.Z = 1;
    }
}

// POP u16
// Pop register u16 from the stack. This is roughly equivalent to the following imaginary instructions.
// ld LOW(r16), [sp]
// inc sp
// ld HIGH(r16), [sp]
// inc sp
void lr35902::pop(uint8_t* upper, uint8_t* lower)
{
    uint16_t SP = (S << 8 | P);

    *lower = read(SP);
    SP++;
    *upper = read(SP);
    SP++;

    S = (SP >> 8 & 0x00FF);
    P = (SP & 0x00FF);
}

void lr35902::pop(uint16_t* u16) {

    uint16_t SP = (S << 8 | P);

    uint8_t lower = read(SP);
    SP++;
    uint8_t upper = read(SP);
    SP++;

    *u16 = (upper << 8 | lower);

    S = (SP >> 8 & 0x00FF);
    P = (SP & 0x00FF);
}

void lr35902::push(uint16_t* u16)
{
    uint8_t upper = (*u16 >> 8 & 0x00FF);
    uint8_t lower = (*u16 & 0x00FF);

    uint16_t SP = (S << 8 | P);

    SP--;
    write(SP, upper);
    SP--;
    write(SP, lower);

    S = (SP >> 8 & 0x00FF);
    P = (SP & 0x00FF);

}

void lr35902::push(uint8_t* upper, uint8_t* lower) {

    uint16_t SP = (S << 8 | P);

    SP--;
    write(SP, *upper);
    SP--;
    write(SP, *lower);

    S = (SP >> 8 & 0x00FF);
    P = (SP & 0x00FF);

}


void lr35902::jp(uint16_t* pc)
{
    uint8_t lower = read(*pc);
    *pc++;
    uint8_t upper = read(*pc);

    uint16_t jump = static_cast<uint16_t>(upper << 8 | lower);

    *pc = jump;
}

void lr35902::call(uint16_t* pc)
{
    uint16_t lower = read(*pc);
    *pc++;
    uint16_t upper = read(*pc);
    *pc++;

    push(pc);

    *pc = static_cast<uint16_t>(upper << 8 | lower);
}


void lr35902::jr(uint16_t* pc) {

    uint16_t jump = *pc + read(*pc);

    *pc = static_cast<uint16_t>(jump);
}

void lr35902::write(uint16_t addr, uint8_t data) {
    bus->write(addr, data);
}




// INICIO OPCODES

void lr35902::NOP()
{
    PC++;
    cycles = 1;
}


void lr35902::LD_BC_u16()
{
    PC++;

    ld(&C, &PC);
    PC++;

    ld(&B, &PC);
    PC++;

    cycles = 3;
}

void lr35902::LD_BC_A()
{
    PC++;

    ld(&B, &C, &A);

    cycles = 2;
}

void lr35902::INC_BC()
{
    PC++;

    inc(&B, &C);

    cycles = 2;
}

void lr35902::INC_B()
{
    PC++;

    inc(&B);

    cycles = 1;
}

void lr35902::DEC_B() {

    PC++;

    dec(&B);

    cycles = 1;
}

void lr35902::LD_B_u8() {

    PC++;

    uint8_t value = read(PC);

    ld(&B, &value);

    PC++;

    cycles = 2;
}


//Rotate register A left.
void lr35902::RLCA() {

    PC++;

    uint8_t value = A;

    // 0x80 -> 0b10000000
    if ((value & 0x80) == 0x80) {
        F.bits.C = 1;

        value <<= 1;

        value |= 0x01;
    }
    else {
        F.bits.C = 0;

        value <<= 1;
    }

    A = static_cast<uint8_t>(value);

    cycles = 1;
}

//LD [n16],SP
//Store SP & $FF at address n16 and SP >> 8 at address n16 + 1.
void lr35902::LD_u16_SP() {

    PC++;

    uint8_t lower = read(PC);
    PC++;

    uint8_t upper = read(PC);
    PC++;

    uint16_t addr = (upper << 8 | lower);

    write(addr, P);

    addr++;
    write(addr, S);

    cycles = 5;
}

void lr35902::ADD_HL_BC() {

    PC++;

    add_hl(&B, &C);

    cycles = 2;
}

void lr35902::LD_A_BC() {
    PC++;

    uint16_t BC = (B << 8 | C);

    ld(&A, &BC);

    cycles = 2;
}

// DEC BC
// Decrement value in register BC by 1
void lr35902::DEC_BC() {

    PC++;

    dec(&B, &C);

    cycles = 2;
}

//INC C
//Increment value in register C by 1.
void lr35902::INC_C() {
    PC++;

    inc(&C);

    cycles = 1;
}

// DEC C
// Decrement value in register C by 1.
void lr35902::DEC_C() {

    PC++;

    dec(&C);

    cycles = 1;
}

void lr35902::LD_C_u8() {

    PC++;

    uint8_t value = read(PC);

    ld(&C, &value);

    PC++;

    cycles = 1;
}

void lr35902::RRCA() {

    PC++;

    uint8_t result = A; // A -> 0xA3 -> 0b10100011

    // 0x01 -> 0b00000001

    if ((result & 0x01) == 0x01) {

        result >>= 1;

        F.bits.C = 1;

        F.value |= 0x80;

    }
    else {
        result >>= 1;

        F.bits.C = 0;

    }

    A = result;

    cycles = 1;
}

// Enter CPU very low power mode. Also used to switch between double and normal speed CPU modes in GBC
void lr35902::STOP() {

    PC++;

    PC++;

    cycles = 4;
}

void lr35902::LD_DE_u16() {

    PC++;

    ld(&E, &PC);
    PC++;

    ld(&D, &PC);

    PC++;

    cycles = 4;
}

void lr35902::LD_DE_A() {

    PC++;

    ld(&D, &E, &A);

    cycles = 2;
}

void lr35902::INC_DE() {

    PC++;

    inc(&D, &E);

    cycles = 2;
}

void lr35902::INC_D() {

    PC++;

    inc(&D);

    cycles = 1;

}

void lr35902::DEC_D() {

    PC++;

    dec(&D);

    cycles = 1;
}

void lr35902::LD_D_u8()
{
    PC++;

    uint8_t value = read(PC);

    ld(&D, &value);

    PC++;

    cycles = 2;
}

void lr35902::RLA()
{
    PC++;

    uint8_t result = A;

    // 0x80 -> 0x10000000
    if ((result & 0x80) == 0x80) {

        result <<= 1;

        if (F.bits.C == 0x01) {
            result |= 0x01;
        }

        F.bits.C = 1;
    }
    else {
        result <<= 1;

        if (F.bits.C == 0x01) {
            result |= 0x01;
        }

        F.bits.C = 0;
    }

    A = static_cast<uint8_t>(result);

    cycles = 1;
}

void lr35902::JR_i8()
{
    PC++;

    jr(&PC);

    cycles = 3;
}

void lr35902::ADD_HL_DE()
{
    PC++;

    add_hl(&D, &E);

    cycles = 2;
}

void lr35902::LD_A_DE()
{
    PC++;

    uint16_t DE = (D << 8 & E);

    ld(&A, &DE);

    cycles = 2;
}


void lr35902::DEC_DE()
{
    PC++;

    dec(&D, &E);

    cycles = 2;
}


void lr35902::INC_E()
{
    PC++;

    inc(&E);

    cycles = 1;
}


void lr35902::DEC_E()
{
    PC++;

    dec(&E);

    cycles = 1;
}

void lr35902::LD_E_u8()
{
    PC++;

    uint8_t value = read(PC);

    ld(&E, &value);

    PC++;

    cycles = 2;
}

void lr35902::RRA()
{
    PC++;

    uint8_t result = A;

    // 0x01 -> 0b00000001
    if ((result & 0x01) == 0x01) {

        result >>= 1;

        if (F.bits.C == 0x01) {
            result |= 0x80;
        }

        F.bits.C = 1;
    }
    else {
        result >>= 1;

        if (F.bits.C == 0x01) {
            result |= 0x80;
        }

        F.bits.C = 0;
    }

    A = static_cast<uint8_t>(result);


    cycles = 1;
}

// JR CC, i8
// Relative Jump by adding i8 to the current address if condition cc is met
void lr35902::JR_NZ_i8()
{
    PC++;

    if (F.bits.Z == 0x00) {

        jr(&PC);

        cycles = 3;
    }
    else {
        PC++;

        cycles = 2;
    }

}


void lr35902::LD_HL_u16()
{

    PC++;

    ld(&L, &PC);
    PC++;

    ld(&P, &PC);
    PC++;

    cycles = 3;
}


void lr35902::LD_HLp_A()
{
    PC++;

    ld_hlp(&H, &L, &A);

    cycles = 2;
}

void lr35902::INC_HL()
{
    PC++;

    inc(&H, &L);

    cycles = 2;
}

void lr35902::INC_H()
{
    PC++;

    inc(&H);

    cycles = 1;
}


void lr35902::DEC_H()
{
    PC++;

    dec(&H);

    cycles = 1;
}

void lr35902::LD_H_u8()
{
    PC++;

    ld(&H, &PC);

    PC++;

    cycles = 2;
}

void lr35902::DAA()
{
    PC++;

    uint8_t adj = A;

    if (F.bits.N == 0) {

        if ((F.bits.H == 1) || ((adj & 0xF) > 9)) {
            adj += 0x06;
        }

        if ((F.bits.H) || (adj & 0x9F)) {
            adj += 0x60;
        }
    }
    else
    {
        if (F.bits.H == 1) {
            adj = (adj - 6) & 0xFF;
        }

        if (F.bits.C == 1) {
            adj -= 0x60;
        }
    }

    F.bits.C = 0x00;
    F.bits.H = 0x00;

    if ((adj & 0x100) == 0x100) {
        F.bits.C = 1;
    }

    adj &= 0xFF;

    if (adj == 0x00) {
        F.bits.Z = 1;
    }

    A = static_cast<uint8_t>(adj);

    cycles = 1;
}

void lr35902::JR_Z_i8()
{
    PC++;

    if (F.bits.Z == 1) {

        jr(&PC);
        cycles = 3;
    }
    else {
        PC++;
        cycles = 2;
    }
}


void lr35902::ADD_HL_HL()
{
    PC++;

    add_hl(&H, &L);

    cycles = 2;
}

void lr35902::LD_A_HLp()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = read(HL);


    HL++;

    H = (HL >> 8 & 0x00FF);
    L = (HL & 0x00FF);

    cycles = 2;
}


void lr35902::DEC_HL()
{
    PC++;

    dec(&H, &L);

    cycles = 2;
}

void lr35902::INC_L()
{
    PC++;

    inc(&L);

    cycles = 1;
}

void lr35902::DEC_L()
{
    PC++;

    dec(&L);

    cycles = 1;
}

void lr35902::LD_L_u8()
{
    PC++;

    uint8_t value = read(PC);

    ld(&L, &value);

    PC++;

    cycles = 2;
}

void lr35902::CPL()
{
    PC++;
    uint8_t value = A;
    uint8_t result = ~value;

    A = result;

    F.bits.C = 1;
    F.bits.H = 1;

    cycles = 1;
}

void lr35902::JR_NC_i8()
{
    PC++;

    if (F.bits.C == 0) {

        jr(&PC);

        cycles = 3;
    }
    else {
        PC++;

        cycles = 2;
    }
}


void lr35902::LD_SP_u16()
{
    PC++;

    ld(&P, &PC);
    PC++;

    ld(&S, &PC);
    PC++;

    cycles = 3;
}


void lr35902::LD_HLm_A()
{
    PC++;

    ld_hlm(&H, &L, &A);

    cycles = 2;
}


void lr35902::INC_SP()
{
    PC++;

    inc(&S, &P);

    cycles = 2;
}


void lr35902::INC_HLa()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    uint8_t value = read(HL);

    value++;

    write(HL, value);

    cycles = 3;
}


void lr35902::DEC_HLa()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    uint8_t value = read(HL);

    value--;

    write(HL, value);

    cycles = 3;
}

// LD [HL], u8
// Store value u8 into byte pointed to by register HL
void lr35902::LD_HL_u8()
{
    PC++;

    uint8_t value = read(PC);

    ld(&H, &L, &value);

    PC++;

    cycles = 3;
}


void lr35902::SCF()
{
    PC++;

    F.bits.C = 1;

    cycles = 1;
}


// JR, cc, i8
// Relative jump by adding i8 to the current address if condition cc is met.
// C -> Carry (C) is set
void lr35902::JR_C_i8()
{
    PC++;

    if (F.bits.C == 1) {

        jr(&PC);

        cycles = 3;
    }
    else {

        PC++;

        cycles = 2;
    }
}

void lr35902::ADD_HL_SP()
{
    PC++;

    add_hl(&S, &P);

    cycles = 2;
}

void lr35902::LD_A_HLm()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = read(HL);

    HL--;

    H = (HL >> 8 & 0x00FF);
    L = (HL & 0x00FF);

    cycles = 2;
}


void lr35902::DEC_SP()
{
    PC++;

    dec(&S, &P);

    cycles = 2;
}


void lr35902::INC_A()
{
    PC++;

    inc(&A);

    cycles = 1;
}

// DEC A
// Decrement value in register A by 1
void lr35902::DEC_A()
{
    PC++;

    dec(&A);

    cycles = 1;
}
void lr35902::LD_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    ld(&A, &value);

    PC++;

    cycles = 2;
}


void lr35902::CCF()
{
    PC++;

    uint8_t value = F.bits.C;
    uint8_t result = ~value;

    F.bits.C = result;

    F.bits.H = 0;
    F.bits.Z = 0;

    cycles = 1;
}


void lr35902::LD_B_B()
{
    PC++;

    B = B;

    cycles = 1;
}


void lr35902::LD_B_C()
{
    PC++;

    B = C;

    cycles = 1;
}


void lr35902::LD_B_D()
{
    PC++;

    B = D;

    cycles = 1;
}

void lr35902::LD_B_E()
{
    PC++;

    B = E;

    cycles = 1;
}

void lr35902::LD_B_H()
{
    PC++;

    B = H;

    cycles = 1;
}

void lr35902::LD_B_L()
{
    PC++;

    B = L;

    cycles = 1;
}

void lr35902::LD_B_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    B = read(HL);

    cycles = 1;
}

void lr35902::LD_B_A()
{
    PC++;

    B = A;

    cycles = 1;
}

void lr35902::LD_C_B()
{
    PC++;

    C = B;

    cycles = 1;
}

void lr35902::LD_C_C()
{
    PC++;

    C = C;

    cycles = 1;
}

void lr35902::LD_C_D()
{
    PC++;

    C = D;

    cycles = 1;
}

void lr35902::LD_C_E()
{
    PC++;

    C = E;

    cycles = 1;
}

void lr35902::LD_C_H()
{
    PC++;

    C = H;

    cycles = 1;
}

void lr35902::LD_C_L()
{
    PC++;

    C = L;

    cycles = 1;
}

void lr35902::LD_C_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    C = read(HL);

    cycles = 1;
}

void lr35902::LD_C_A()
{
    PC++;

    C = A;

    cycles = 1;
}


void lr35902::LD_D_B()
{
    PC++;

    D = B;

    cycles = 1;
}

void lr35902::LD_D_C()
{
    PC++;

    D = C;

    cycles = 1;
}


void lr35902::LD_D_D()
{
    PC++;

    D = D;

    cycles = 1;
}

void lr35902::LD_D_E()
{
    PC++;

    D = E;

    cycles = 1;
}

void lr35902::LD_D_H()
{
    PC++;

    D = H;

    cycles = 1;
}

void lr35902::LD_D_L()
{
    PC++;

    D = L;

    cycles = 1;
}

void lr35902::LD_D_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    D = read(HL);

    cycles = 1;
}

void lr35902::LD_D_A()
{
    PC++;

    D = A;

    cycles = 1;
}

void lr35902::LD_E_B()
{
    PC++;

    E = B;

    cycles = 1;
}

void lr35902::LD_E_C()
{
    PC++;

    E = C;

    cycles = 1;
}

void lr35902::LD_E_D()
{
    PC++;

    E = D;

    cycles = 1;
}

void lr35902::LD_E_E()
{
    PC++;

    E = E;

    cycles = 1;
}

void lr35902::LD_E_H()
{
    PC++;

    E = H;

    cycles = 1;
}

void lr35902::LD_E_L()
{
    PC++;

    E = L;

    cycles = 1;
}

void lr35902::LD_E_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    E = read(HL);

    cycles = 1;
}

void lr35902::LD_E_A()
{
    PC++;

    E = A;

    cycles = 1;
}


void lr35902::LD_H_B()
{
    PC++;

    H = B;

    cycles = 1;
}

void lr35902::LD_H_C()
{
    PC++;

    H = C;

    cycles = 1;
}

void lr35902::LD_H_D()
{
    PC++;

    H = D;

    cycles = 1;
}

void lr35902::LD_H_E()
{
    PC++;

    H = E;

    cycles = 1;
}

void lr35902::LD_H_H()
{
    PC++;

    H = H;

    cycles = 1;
}

void lr35902::LD_H_L()
{
    PC++;

    H = L;

    cycles = 1;
}

void lr35902::LD_H_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    H = read(HL);

    cycles = 1;
}

void lr35902::LD_H_A()
{
    PC++;

    H = A;

    cycles = 1;
}

void lr35902::LD_L_B()
{
    PC++;

    L = B;

    cycles = 1;
}

void lr35902::LD_L_D()
{
    PC++;

    L = D;

    cycles = 1;
}

void lr35902::LD_L_E()
{
    PC++;

    L = E;

    cycles = 1;
}

void lr35902::LD_L_H()
{
    PC++;

    L = H;

    cycles = 1;
}

void lr35902::LD_L_L()
{
    PC++;

    L = L;

    cycles = 1;
}

void lr35902::LD_L_HL()
{
    uint16_t HL = (H << 8 | L);

    L = read(HL);

    PC++;

    cycles = 1;
}

void lr35902::LD_L_C()
{
    PC++;

    L = A;

    cycles = 1;
}

void lr35902::LD_L_A()
{
    L = A;

    PC++;

    cycles = 1;
}


void lr35902::LD_HL_B()
{
    PC++;

    ld(&H, &L, &B);

    cycles = 2;
}

void lr35902::LD_HL_C()
{
    PC++;

    ld(&H, &L, &C);

    cycles = 2;
}

void lr35902::LD_HL_D()
{
    PC++;

    ld(&H, &L, &D);

    cycles = 2;
}

void lr35902::LD_HL_E()
{
    PC++;

    ld(&H, &L, &E);

    cycles = 2;
}

void lr35902::LD_HL_H()
{
    PC++;

    ld(&H, &L, &H);

    cycles = 2;
}

void lr35902::LD_HL_L()
{
    PC++;

    ld(&H, &L, &L);

    cycles = 2;
}

void lr35902::HALT()
{
    PC++;
    halt = true;
    cycles = 2;
}


void lr35902::LD_HL_A()
{
    PC++;

    ld(&H, &L, &A);

    cycles = 2;
}

void lr35902::LD_A_B()
{
    PC++;

    A = B;

    cycles = 1;
}

void lr35902::LD_A_C()
{
    PC++;

    A = C;

    cycles = 1;
}

void lr35902::LD_A_D()
{
    PC++;

    A = D;

    cycles = 1;
}

void lr35902::LD_A_H()
{
    PC++;

    A = H;

    cycles = 1;
}

void lr35902::LD_A_E()
{
    PC++;

    A = E;

    cycles = 1;
}

void lr35902::LD_A_L()
{
    PC++;

    A = L;

    cycles = 1;
}

void lr35902::LD_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    ld(&A, &HL);

    cycles = 2;
}

void lr35902::LD_A_A()
{
    PC++;

    A = A;

    cycles = 1;
}


void lr35902::ADD_A_H()
{
    PC++;

    A = add(A, H);

    cycles = 1;
}

void lr35902::ADD_A_L()
{
    PC++;

    A = add(A, L);

    cycles = 1;
}

void lr35902::ADD_A_B()
{
    PC++;

    A = add(A, B);

    cycles = 1;
}

void lr35902::ADD_A_C()
{
    PC++;

    A = add(A, C);

    cycles = 1;
}

void lr35902::ADD_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = add(A, HL);

    cycles = 2;
}

void lr35902::ADD_A_D()
{
    PC++;

    A = add(A, D);

    cycles = 1;
}

void lr35902::ADD_A_E()
{
    PC++;

    A = add(A, D);

    cycles = 1;
}

void lr35902::ADD_A_A()
{
    PC++;

    A = add(A, A);

    cycles = 1;
}


void lr35902::ADC_A_B()
{
    PC++;

    A = adc(A, B);

    cycles = 1;
}

void lr35902::ADC_A_C()
{
    PC++;

    A = adc(A, C);

    cycles = 1;
}

void lr35902::ADC_A_D()
{
    PC++;

    A = adc(A, D);

    cycles = 1;
}

void lr35902::ADC_A_E()
{
    PC++;

    A = adc(A, E);

    cycles = 1;
}

void lr35902::ADC_A_H()
{
    PC++;

    A = adc(A, H);

    cycles = 1;
}

void lr35902::ADC_A_L()
{
    PC++;

    A = adc(A, L);

    cycles = 1;
}

void lr35902::ADC_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = adc(A, HL);

    cycles = 2;
}


void lr35902::ADC_A_A()
{
    PC++;

    A = adc(A, A);

    cycles = 1;
}


void lr35902::SUB_A_B()
{
    PC++;

    A = sub(A, B);

    cycles = 1;
}

void lr35902::SUB_A_C()
{
    PC++;

    A = sub(A, C);

    cycles = 1;
}

void lr35902::SUB_A_D()
{
    PC++;

    A = sub(A, D);

    cycles = 1;
}


void lr35902::SUB_A_H()
{
    PC++;

    A = sub(A, H);

    cycles = 1;
}

void lr35902::SUB_A_E()
{
    PC++;

    A = sub(A, E);

    cycles = 1;
}

void lr35902::SUB_A_L()
{
    PC++;

    A = sub(A, L);

    cycles = 1;
}

void lr35902::SUB_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = sub(A, HL);

    cycles = 2;
}

void lr35902::SUB_A_A()
{
    PC++;

    A = sub(A, A);

    cycles = 1;
}

void lr35902::SBC_A_B()
{
    PC++;

    A = sbc(A, B);

    cycles = 1;
}

void lr35902::SBC_A_C()
{
    PC++;

    A = sbc(A, C);

    cycles = 1;
}

void lr35902::SBC_A_D()
{
    PC++;

    A = sbc(A, D);

    cycles = 1;
}

void lr35902::SBC_A_E()
{
    PC++;

    A = sbc(A, E);

    cycles = 1;
}

void lr35902::SBC_A_H()
{
    PC++;

    A = sbc(A, H);

    cycles = 1;
}

void lr35902::SBC_A_L()
{
    PC++;

    A = sbc(A, L);

    cycles = 1;
}

void lr35902::SBC_A_HL()
{
    PC++;

    uint16_t HL = (8 << H | L);

    A = sbc(A, HL);

    cycles = 1;
}

void lr35902::SBC_A_A()
{
    PC++;

    A = sbc(A, A);

    cycles = 1;
}


void lr35902::AND_A_B()
{
    PC++;

    A = and_op(A, B);

    cycles = 1;
}

void lr35902::AND_A_C()
{
    PC++;

    A = and_op(A, C);

    cycles = 1;
}

void lr35902::AND_A_D()
{
    PC++;

    A = and_op(A, D);

    cycles = 1;
}

void lr35902::AND_A_E()
{
    PC++;

    A = and_op(A, E);

    cycles = 1;
}

void lr35902::AND_A_H()
{
    PC++;

    A = and_op(A, H);

    cycles = 1;
}

void lr35902::AND_A_L()
{
    PC++;

    A = and_op(A, L);

    cycles = 1;
}

void lr35902::AND_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = and_op(A, HL);

    cycles = 1;
}

void lr35902::AND_A_A()
{
    PC++;

    A = and_op(A, A);

    cycles = 1;
}

void lr35902::XOR_A_B()
{
    PC++;

    A = xor_op(A, B);

    cycles = 1;
}

void lr35902::XOR_A_C()
{
    PC++;

    A = xor_op(A, C);

    cycles = 1;
}

void lr35902::XOR_A_D()
{
    PC++;

    A = xor_op(A, D);

    cycles = 1;
}

void lr35902::XOR_A_E()
{
    PC++;

    A = xor_op(A, E);

    cycles = 1;
}

void lr35902::XOR_A_H()
{
    PC++;

    A = xor_op(A, H);

    cycles = 1;
}

void lr35902::XOR_A_L()
{
    PC++;

    A = xor_op(A, L);

    cycles = 1;
}

void lr35902::XOR_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = xor_op(A, HL);

    cycles = 2;
}

void lr35902::XOR_A_A()
{
    PC++;

    A = xor_op(A, A);

    cycles = 1;
}

void lr35902::OR_A_C()
{
    A = or_op(A, C);

    PC++;

    cycles = 1;
}

void lr35902::OR_A_B()
{
    PC++;

    A = or_op(A, B);

    cycles = 1;
}

void lr35902::OR_A_D()
{
    PC++;

    A = or_op(A, D);

    cycles = 1;
}

void lr35902::OR_A_E()
{
    PC++;

    A = or_op(A, E);

    cycles = 1;
}

void lr35902::OR_A_H()
{
    PC++;

    A = or_op(A, H);

    cycles = 1;
}

void lr35902::OR_A_L()
{
    PC++;

    A = or_op(A, L);

    cycles = 1;
}

void lr35902::OR_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    A = or_op(A, HL);

    cycles = 2;
}

void lr35902::OR_A_A()
{
    PC++;

    A = or_op(A, A);

    cycles = 1;
}

void lr35902::CP_A_B()
{
    PC++;

    cp(A, B);

    cycles = 1;
}

void lr35902::CP_A_C()
{
    PC++;

    cp(A, C);

    cycles = 1;
}

void lr35902::CP_A_D()
{
    PC++;

    cp(A, D);

    cycles = 1;
}

void lr35902::CP_A_E()
{
    PC++;

    cp(A, E);

    cycles = 1;
}

void lr35902::CP_A_H()
{
    PC++;

    cp(A, H);

    cycles = 1;
}

void lr35902::CP_A_L()
{
    PC++;

    cp(A, L);

    cycles = 1;
}

void lr35902::CP_A_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    cp(A, HL);

    cycles = 2;
}

void lr35902::CP_A_A()
{
    PC++;

    cp(A, A);

    cycles = 2;
}

void lr35902::RET_NZ()
{
    PC++;

    if (F.bits.Z == 0x00) {

        pop(&PC);

        cycles = 5;
    }
    else {

        cycles = 2;
    }
}

void lr35902::POP_BC()
{
    PC++;

    pop(&B, &C);

    cycles = 3;
}


void lr35902::JP_NZ_u16()
{
    PC++;

    if (F.bits.Z == 0) {

        jp(&PC);

        cycles = 4;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }
}

// JP u16
// Jump to address u16; effectively, store u16 in PC
void lr35902::JP_u16()
{
    PC++;

    jp(&PC);

    PC++;
    PC++;

    cycles = 4;
}

void lr35902::CALL_NZ_u16()
{
    PC++;

    if (F.bits.Z == 0x00) {

        call(&PC);

        cycles = 6;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }

}


void lr35902::PUSH_BC()
{
    PC++;

    push(&B, &C);

    cycles = 4;
}

void lr35902::ADD_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    A = add(A, value);

    PC++;

    cycles = 2;
}


void lr35902::RST_00h()
{
    PC++;

    push(&PC);

    PC = 0x0000;

    cycles = 4;
}


void lr35902::RET_Z()
{
    PC++;

    if (F.bits.Z == 0x01) {

        pop(&PC);

        cycles = 5;
    }
    else {

        cycles = 2;
    }
}

void lr35902::RET()
{
    PC++;

    pop(&PC);

    cycles = 4;
}

void lr35902::JP_Z_u16()
{
    PC++;

    if (F.bits.Z == 0x01) {

        jp(&PC);

        cycles = 6;

    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }

}

void lr35902::PREFIX_CB()
{
    PC++;

    cb.process(PC);

    cycles = 1;
}

void lr35902::CALL_Z_u16()
{
    PC++;

    if (F.bits.Z == 0x01) {

        call(&PC);

        cycles = 6;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }

}


void lr35902::CALL_u16()
{
    PC++;

    call(&PC);

    cycles = 6;
}

void lr35902::ADC_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    A = adc(A, value);

    PC++;

    cycles = 2;
}

void lr35902::RST_08h()
{
    PC++;

    push(&PC);

    PC = 0x0008;

    cycles = 4;
}


void lr35902::RET_NC()
{
    PC++;

    if (F.bits.C == 0x00) {

        pop(&PC);

        cycles = 5;

    }
    else {
        cycles = 2;
    }


}

void lr35902::POP_DE()
{
    PC++;

    pop(&D, &E);

    cycles = 3;
}


void lr35902::JP_NC_u16()
{
    PC++;

    if (F.bits.C == 0x00) {

        jp(&PC);

        cycles = 4;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }

}


void lr35902::CALL_NC_u16()
{
    PC++;

    if (F.bits.C == 0x00) {

        call(&PC);

        cycles = 6;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }
}

void lr35902::PUSH_DE()
{
    PC++;

    push(&D, &E);

    cycles = 4;
}

void lr35902::SUB_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    A = sub(A, value);

    PC++;

    cycles = 2;
}

void lr35902::RST_10h()
{
    PC++;

    push(&PC);

    PC = 0x0010;

    cycles = 4;
}


void lr35902::RET_C()
{
    PC++;

    if (F.bits.C == 0x01) {

        pop(&PC);

        cycles = 5;
    }
    else {

        cycles = 2;
    }

}

void lr35902::RETI()
{
    PC++;

    pop(&PC);
    interruption = true;
}


void lr35902::JP_C_u16()
{
    PC++;

    if (F.bits.C == 0x01) {

        jp(&PC);

        cycles = 4;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }

}

void lr35902::CALL_C_u16()
{
    PC++;

    if (F.bits.C == 0x01) {

        call(&PC);

        cycles = 6;
    }
    else {
        PC++;
        PC++;

        cycles = 3;
    }

}

void lr35902::SBC_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    A = sbc(A, value);

    PC++;

    cycles = 2;
}

void lr35902::RST_18h()
{
    PC++;

    push(&PC);

    PC = 0x0018;

    cycles = 4;
}



void lr35902::LD_FF00_u8_A()
{
    PC++;

    uint16_t addr = static_cast<uint16_t>(0xFF00 + read(PC));

    write(addr, A);

    PC++;

    cycles = 3;
}

void lr35902::POP_HL()
{
    PC++;

    pop(&H, &L);

    cycles = 3;
}

void lr35902::LD_FF00_C_A()
{
    PC++;

    uint16_t addr = static_cast<uint16_t>(0xFF00 + C);

    write(addr, A);

    cycles = 2;
}

void lr35902::PUSH_HL()
{
    PC++;

    push(&H, &L);

    cycles = 4;
}

void lr35902::AND_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    A = and_op(A, value);

    PC++;

    cycles = 2;

}

void lr35902::RST_20h()
{
    PC++;

    push(&PC);

    PC = 0x0020;

    cycles = 4;
}

void lr35902::ADD_SP_i8()
{
    PC++;

    uint16_t SP = (S << 8 | P);
    uint8_t value = read(PC);

    uint16_t result = SP + value;

    F.value = 0x00;

    if (((SP ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100) {
        F.bits.C = 1;
    }

    if (((SP ^ value ^ (result & 0xFFFF)) & 0x010) == 0x010) {
        F.bits.H = 1;
    }

    SP = static_cast<uint16_t>(result);

    S = (SP >> 8 & 0x00FF);
    P = (SP & 0x00FF);

    PC++;

    cycles = 4;
}

void lr35902::JP_HL()
{
    PC++;

    uint16_t HL = (H << 8 | L);

    PC = HL;

    cycles = 1;
}

void lr35902::LD_u16_A()
{
    PC++;

    uint8_t lower = read(PC);
    PC++;
    uint8_t upper = read(PC);
    PC++;

    uint16_t addr = (upper << 8 | lower);

    write(addr, A);

    cycles = 4;
}

void lr35902::XOR_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    A = xor_op(A, value);

    PC++;

    cycles = 2;
}

void lr35902::RST_28h()
{
    PC++;

    push(&PC);

    PC = 0x0028;

    cycles = 4;
}


void lr35902::LD_A_FF00_u8()
{
    PC++;

    uint16_t addr = static_cast<uint16_t>(0xFF00 + read(PC));

    uint8_t value = read(addr);

    A = static_cast<uint8_t>(value);

    PC++;

    cycles = 3;
}


void lr35902::POP_AF()
{
    PC++;

    pop(&A, &F.value);

    cycles = 4;
}


void lr35902::LD_A_FF00_C()
{
    PC++;

    uint16_t addr = static_cast<uint16_t>(0xFF00 + C);

    uint8_t value = read(addr);

    PC++;

    A = static_cast<uint8_t>(value);

    cycles = 2;
}

void lr35902::DI()
{
    PC++;

    interruption = false;

    cycles = 1;
}


void lr35902::PUSH_AF()
{
    PC++;

    push(&A, &F.value);

    cycles = 4;
}



void lr35902::OR_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    PC++;

    A = or_op(A, value);

    cycles = 2;
}

void lr35902::RST_30h()
{
    PC++;

    push(&PC);

    PC = 0x0030;

    cycles = 4;
}

void lr35902::LD_HL_SP_i8()
{
    PC++;

    uint16_t SP = (S << 8 | P);

    uint8_t value = read(PC);

    uint16_t result = static_cast<uint16_t>(SP + value);

    F.value = 0x00;

    if (((SP ^ value ^ result) & 0x100) == 0x100) {
        F.bits.C = 1;
    }

    if (((SP ^ value ^ result) & 0x10) == 0x10) {
        F.bits.H = 1;
    }

    H = (result >> 8 & 0x00FF);
    L = (result & 0x00FF);

    PC++;

    cycles = 2;
}

void lr35902::LD_SP_HL()
{
    PC++;

    S = H;
    P = L;

    cycles = 2;
}

void lr35902::LD_A_u16()
{
    PC++;
    uint8_t lower = read(PC);
    PC++;
    uint8_t upper = read(PC);

    uint16_t addr = static_cast<uint16_t>(upper << 8 | lower);

    A = read(addr);

    PC++;

    cycles = 4;
}

void lr35902::EI()
{
    PC++;

    interruption = true;

    cycles = 1;
}


void lr35902::CP_A_u8()
{
    PC++;

    uint8_t value = read(PC);

    cp(A, value);

    PC++;

    cycles = 2;
}

void lr35902::RST_38h()
{
    PC++;

    push(&PC);

    PC = 0x0038;

    cycles = 1;
}

void lr35902::clock() {

    std::cout << "Teste Clock" << std::endl;

    if (cycles == 0) {
        std::cout << "PC : " << std::hex << PC << std::endl;
        opcode = read(PC);
        std::cout << "OPCODE : " << std::hex << opcode << std::endl;

        process(opcode);

    }

    cycles--;
}



void lr35902::reset()
{
    A = 0x01;
    F.value = 0xB0;

    B = 0x00;
    C = 0x13;

    D = 0x00;
    E = 0xD8;

    H = 0x01;
    L = 0x4D;

    S = 0xFF;
    P = 0xFE;

    PC = 0x0100;
}

void lr35902::process(uint16_t opcode)
{

    switch (opcode)
    {
    case 0x00:
        NOP();
        break;
    case 0x01:
        LD_BC_u16();
        break;
    case 0x02:
        LD_BC_A();
        break;
    case 0x03:
        INC_BC();
        break;
    case 0x04:
        INC_B();
        break;
    case 0x05:
        DEC_B();
        break;
    case 0x06:
        LD_B_u8();
        break;
    case 0x07:
        RLCA();
        break;
    case 0x08:
        LD_u16_SP();
        break;
    case 0x09:
        ADD_HL_BC();
        break;
    case 0x0A:
        LD_A_BC();
        break;
    case 0x0B:
        DEC_BC();
        break;
    case 0x0C:
        INC_C();
        break;
    case 0x0D:
        DEC_C();
        break;
    case 0x0E:
        LD_C_u8();
        break;
    case 0x0F:
        RRCA();
        break;
    case 0x10:
        STOP();
        break;
    case 0x11:
        LD_DE_u16();
        break;
    case 0x12:
        LD_DE_A();
        break;
    case 0x13:
        INC_DE();
        break;
    case 0x14:
        INC_D();
        break;
    case 0x15:
        DEC_D();
        break;
    case 0x16:
        LD_D_u8();
        break;
    case 0x17:
        RLA();
        break;
    case 0x18:
        JR_i8();
        break;
    case 0x19:
        ADD_HL_DE();
        break;
    case 0x1A:
        LD_A_DE();
        break;
    case 0x1B:
        DEC_DE();
        break;
    case 0x1C:
        INC_E();
        break;
    case 0x1D:
        DEC_E();
        break;
    case 0x1E:
        LD_E_u8();
        break;
    case 0x1F:
        RRA();
        break;
    case 0x20:
        JR_NZ_i8();
        break;
    case 0x21:
        LD_HL_u16();
        break;
    case 0x22:
        LD_HLp_A();
        break;
    case 0x23:
        INC_HL();
        break;
    case 0x24:
        INC_H();
        break;
    case 0x25:
        DEC_H();
        break;
    case 0x26:
        LD_H_u8();
        break;
    case 0x27:
        DAA();
        break;
    case 0x28:
        JR_Z_i8();
        break;
    case 0x29:
        ADD_HL_HL();
        break;
    case 0x2A:
        LD_A_HLp();
        break;
    case 0x2B:
        DEC_HL();
        break;
    case 0x2C:
        INC_L();
        break;
    case 0x2D:
        DEC_L();
        break;
    case 0x2E:
        LD_L_u8();
        break;
    case 0x2F:
        CPL();
        break;
    case 0x30:
        JR_NC_i8();
        break;
    case 0x31:
        LD_SP_u16();
        break;
    case 0x32:
        LD_HLm_A();
        break;
    case 0x33:
        INC_SP();
        break;
    case 0x34:
        INC_HLa();
        break;
    case 0x35:
        DEC_HLa();
        break;
    case 0x36:
        LD_HL_u8();
        break;
    case 0x37:
        SCF();
        break;
    case 0x38:
        JR_C_i8();
        break;
    case 0x39:
        ADD_HL_SP();
        break;
    case 0x3A:
        LD_A_HLm();
        break;
    case 0x3B:
        DEC_SP();
        break;
    case 0x3C:
        INC_A();
        break;
    case 0x3D:
        DEC_A();
        break;
    case 0x3E:
        LD_A_u8();
        break;
    case 0x3F:
        CCF();
        break;
    case 0x40:
        LD_B_B();
        break;
    case 0x41:
        LD_B_C();
        break;
    case 0x42:
        LD_B_D();
        break;
    case 0x43:
        LD_B_E();
        break;
    case 0x44:
        LD_B_H();
        break;
    case 0x45:
        LD_B_L();
        break;
    case 0x46:
        LD_B_HL();
        break;
    case 0x47:
        LD_B_A();
        break;
    case 0x48:
        LD_C_B();
        break;
    case 0x49:
        LD_C_C();
        break;
    case 0x4A:
        LD_C_D();
        break;
    case 0x4B:
        LD_C_E();
        break;
    case 0x4C:
        LD_C_H();
        break;
    case 0x4D:
        LD_C_L();
        break;
    case 0x4E:
        LD_C_HL();
        break;
    case 0x4F:
        LD_C_A();
        break;
    case 0x50:
        LD_D_B();
        break;
    case 0x51:
        LD_D_C();
        break;
    case 0x52:
        LD_D_D();
        break;
    case 0x53:
        LD_D_E();
        break;
    case 0x54:
        LD_D_H();
        break;
    case 0x55:
        LD_D_L();
        break;
    case 0x56:
        LD_D_HL();
        break;
    case 0x57:
        LD_D_A();
        break;
    case 0x58:
        LD_E_B();
        break;
    case 0x59:
        LD_E_C();
        break;
    case 0x5A:
        LD_E_D();
        break;
    case 0x5B:
        LD_E_E();
        break;
    case 0x5C:
        LD_E_H();
        break;
    case 0x5D:
        LD_E_L();
        break;
    case 0x5E:
        LD_E_HL();
        break;
    case 0x5F:
        LD_E_A();
        break;
    case 0x60:
        LD_H_B();
        break;
    case 0x61:
        LD_H_C();
        break;
    case 0x62:
        LD_H_D();
        break;
    case 0x63:
        LD_H_E();
        break;
    case 0x64:
        LD_H_H();
        break;
    case 0x65:
        LD_H_L();
        break;
    case 0x66:
        LD_H_HL();
        break;
    case 0x67:
        LD_H_A();
        break;
    case 0x68:
        LD_L_B();
        break;
    case 0x69:
        LD_L_C();
        break;
    case 0x6A:
        LD_L_D();
        break;
    case 0x6B:
        LD_L_E();
        break;
    case 0x6C:
        LD_L_H();
        break;
    case 0x6D:
        LD_L_L();
        break;
    case 0x6E:
        LD_L_HL();
        break;
    case 0x6F:
        LD_L_A();
        break;
    case 0x70:
        LD_HL_B();
        break;
    case 0x71:
        LD_HL_C();
        break;
    case 0x72:
        LD_HL_D();
        break;
    case 0x73:
        LD_HL_E();
        break;
    case 0x74:
        LD_HL_H();
        break;
    case 0x75:
        LD_HL_L();
        break;
    case 0x76:
        HALT();
        break;
    case 0x77:
        LD_HL_A();
        break;
    case 0x78:
        LD_A_B();
        break;
    case 0x79:
        LD_A_C();
        break;
    case 0x7A:
        LD_A_D();
        break;
    case 0x7B:
        LD_A_E();
        break;
    case 0x7C:
        LD_A_H();
        break;
    case 0x7D:
        LD_A_L();
        break;
    case 0x7E:
        LD_A_HL();
        break;
    case 0x7F:
        LD_A_A();
        break;
    case 0x80:
        ADD_A_B();
        break;
    case 0x81:
        ADD_A_C();
        break;
    case 0x82:
        ADD_A_D();
        break;
    case 0x83:
        ADD_A_E();
        break;
    case 0x84:
        ADD_A_H();
        break;
    case 0x85:
        ADD_A_L();
        break;
    case 0x86:
        ADD_A_HL();
        break;
    case 0x87:
        ADD_A_A();
        break;
    case 0x88:
        ADC_A_B();
        break;
    case 0x89:
        ADC_A_C();
        break;
    case 0x8A:
        ADC_A_D();
        break;
    case 0x8B:
        ADC_A_E();
        break;
    case 0x8C:
        ADC_A_H();
        break;
    case 0x8D:
        ADC_A_L();
        break;
    case 0x8E:
        ADC_A_HL();
        break;
    case 0x8F:
        ADC_A_A();
        break;
    case 0x90:
        SUB_A_B();
        break;
    case 0x91:
        SUB_A_C();
        break;
    case 0x92:
        SUB_A_D();
        break;
    case 0x93:
        SUB_A_E();
        break;
    case 0x94:
        SUB_A_H();
        break;
    case 0x95:
        SUB_A_L();
        break;
    case 0x96:
        SUB_A_HL();
        break;
    case 0x97:
        SUB_A_A();
        break;
    case 0x98:
        SBC_A_B();
        break;
    case 0x99:
        SBC_A_C();
        break;
    case 0x9A:
        SBC_A_D();
        break;
    case 0x9B:
        SBC_A_E();
        break;
    case 0x9C:
        SBC_A_H();
        break;
    case 0x9D:
        SBC_A_L();
        break;
    case 0x9E:
        SBC_A_HL();
        break;
    case 0x9F:
        SBC_A_A();
        break;
    case 0xA0:
        AND_A_B();
        break;
    case 0xA1:
        AND_A_C();
        break;
    case 0xA2:
        AND_A_D();
        break;
    case 0xA3:
        AND_A_E();
        break;
    case 0xA4:
        AND_A_H();
        break;
    case 0xA5:
        AND_A_L();
        break;
    case 0xA6:
        AND_A_HL();
        break;
    case 0xA7:
        AND_A_A();
        break;
    case 0xA8:
        XOR_A_B();
        break;
    case 0xA9:
        XOR_A_C();
        break;
    case 0xAA:
        XOR_A_D();
        break;
    case 0xAB:
        XOR_A_E();
        break;
    case 0xAC:
        XOR_A_H();
        break;
    case 0xAD:
        XOR_A_L();
        break;
    case 0xAE:
        XOR_A_HL();
        break;
    case 0xAF:
        XOR_A_A();
        break;
    case 0xB0:
        OR_A_B();
        break;
    case 0xB1:
        OR_A_C();
        break;
    case 0xB2:
        OR_A_D();
        break;
    case 0xB3:
        OR_A_E();
        break;
    case 0xB4:
        OR_A_H();
        break;
    case 0xB5:
        OR_A_L();
        break;
    case 0xB6:
        OR_A_HL();
        break;
    case 0xB7:
        OR_A_A();
        break;
    case 0xB8:
        CP_A_B();
        break;
    case 0xB9:
        CP_A_C();
        break;
    case 0xBA:
        CP_A_D();
        break;
    case 0xBB:
        CP_A_E();
        break;
    case 0xBC:
        CP_A_H();
        break;
    case 0xBD:
        CP_A_L();
        break;
    case 0xBE:
        CP_A_HL();
        break;
    case 0xBF:
        CP_A_A();
        break;
    case 0xC0:
        RET_NZ();
        break;
    case 0xC1:
        POP_BC();
        break;
    case 0xC2:
        JP_NZ_u16();
        break;
    case 0xC3:
        JP_u16();
        break;
    case 0xC4:
        CALL_NZ_u16();
        break;
    case 0xC5:
        PUSH_BC();
        break;
    case 0xC6:
        ADD_A_u8();
        break;
    case 0xC7:
        RST_00h();
        break;
    case 0xC8:
        RET_Z();
        break;
    case 0xC9:
        RET();
        break;
    case 0xCA:
        JP_Z_u16();
        break;
    case 0xCB:
        PREFIX_CB();
        break;
    case 0xCC:
        CALL_Z_u16();
        break;
    case 0xCD:
        CALL_u16();
        break;
    case 0xCE:
        ADC_A_u8();
        break;
    case 0xCF:
        RST_08h();
        break;
    case 0xD0:
        RET_NC();
        break;
    case 0xD1:
        POP_DE();
        break;
    case 0xD2:
        JP_NC_u16();
        break;
    case 0xD3:
        std::cout << "INVALID OPCODE: " << "0xD3" << std::endl;
        break;
    case 0xD4:
        CALL_NC_u16();
        break;
    case 0xD5:
        PUSH_DE();
        break;
    case 0xD6:
        SUB_A_u8();
        break;
    case 0xD7:
        RST_10h();
        break;
    case 0xD8:
        RET_C();
        break;
    case 0xD9:
        RETI();
        break;
    case 0xDA:
        JP_C_u16();
        break;
    case 0xDB:
        std::cout << "INVALID OPCODE: " << "0xDB" << std::endl;
        break;
    case 0xDC:
        CALL_C_u16();
        break;
    case 0xDD:
        std::cout << "INVALID OPCODE: " << "0xDE" << std::endl;
        break;
    case 0xDE:
        SBC_A_u8();
        break;
    case 0xDF:
        RST_18h();
        break;
    case 0xE0:
        LD_A_FF00_u8();
        break;
    case 0xE1:
        POP_HL();
        break;
    case 0xE2:
        LD_FF00_C_A();
        break;
    case 0xE3:
        std::cout << "INVALID OPCODE: " << "0xE3" << std::endl;
        break;
    case 0xE4:
        std::cout << "INVALID OPCODE: " << "0xE4" << std::endl;
        break;
    case 0xE5:
        PUSH_HL();
        break;
    case 0xE6:
        AND_A_u8();
        break;
    case 0xE7:
        RST_20h();
        break;
    case 0xE8:
        ADD_SP_i8();
        break;
    case 0xE9:
        JP_HL();
        break;
    case 0xEA:
        LD_u16_A();
        break;
    case 0xEB:
        std::cout << "INVALID OPCODE: " << "0xEB" << std::endl;
        break;
    case 0xEC:
        std::cout << "INVALID OPCODE: " << "0xEC" << std::endl;
        break;
    case 0xED:
        std::cout << "INVALID OPCODE: " << "0xED" << std::endl;
        break;
    case 0xEE:
        XOR_A_u8();
        break;
    case 0xEF:
        RST_28h();
        break;
    case 0xF0:
        LD_A_FF00_u8();
        break;
    case 0xF1:
        POP_AF();
        break;
    case 0xF2:
        LD_A_FF00_C();
        break;
    case 0xF3:
        DI();
        break;
    case 0xF4:
        std::cout << "INVALID OPCODE: " << "0xF4" << std::endl;
        break;
    case 0xF5:
        PUSH_AF();
        break;
    case 0xF6:
        OR_A_u8();
        break;
    case 0xF7:
        RST_30h();
        break;
    case 0xF8:
        LD_HL_SP_i8();
        break;
    case 0xF9:
        LD_SP_HL();
        break;
    case 0xFA:
        LD_A_u16();
        break;
    case 0xFB:
        EI();
        break;
    case 0xFC:
        std::cout << "INVALID OPCODE: " << "0xFC" << std::endl;
        break;
    case 0xFD:
        std::cout << "INVALID OPCODE: " << "0xFD" << std::endl;
        break;
    case 0xFE:
        CP_A_u8();
        break;
    case 0xFF:
        RST_38h();
        break;
    }
}


