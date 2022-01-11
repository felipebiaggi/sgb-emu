#include <vector>
#include <cstdint>
#include "bus.h"
#include "load_file.h"


int main(int argc, char *argv[])
{

   vector<uint8_t> game_data = load_game_file(argc, argv);

   

   return 0;
}


