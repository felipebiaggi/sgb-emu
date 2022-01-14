#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "bus.h"
#include "cartridge.h"

Bus::Bus(Cartridge cartridge)
{
    for (auto& i : ram) i = 0x00;
    cpu.ConnectBus(this);
    std::cout << "RAM: " << ram.size() << std::endl;
    std::cout << "Cartridge Size: " << cartridge.game_data.size() << std::endl;
}

void Bus::write(uint16_t addr, uint8_t data) {
    if (addr >= 0x0000 && addr <= 0xFFFF) {
        ram[addr] = data;
    }
}

uint8_t Bus::read(uint16_t addr)
{
       if (addr >= 0x0000 && addr <= 0xFFFF) {
           return ram[addr];
       }
       return 0x00;
}

