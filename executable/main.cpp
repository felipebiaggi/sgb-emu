#include <iostream>
#include <memory>
#include "bus.h"

int main()
{

   Bus barramento = Bus();

   std::cout << "Olá 123" << std::endl;


   std::cout << "Addr Bus: " << &barramento << std::endl;
   std::cout << "Addr Bus: " << barramento.cpu.bus << std::endl;
   std::cout << "Addr Bus: " << barramento.cpu.cb.bus << std::endl;

   return 0;
}
