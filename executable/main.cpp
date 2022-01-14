#include <vector>
#include <cstdint>
#include "cartridge.h"
#include "bus.h"
#include "load_file.h"


int main(int argc, char *argv[])
{

   auto game_data = load_game_file(argc, argv);

   auto cartridge = Cartridge(game_data);

   auto bus = Bus(cartridge);

   return 0;
}


