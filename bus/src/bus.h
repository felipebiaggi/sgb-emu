#ifndef BUS_H
#define BUS_H
#include <cstdint>
#include <array>
#include "lr35902.h"

class Bus {
public:
    Bus();

public:
    std::array<uint8_t, 64 * 1024> ram;
    lr35902 cpu;

public:
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
};

#endif // BUS_H
