#include <iostream>
#include "cartridge.h"


using namespace std;


Cartridge::Cartridge(vector<uint8_t> value){
    game_data = value;

    // Cartridge Address - Game Title
    // Hexadecimal -> 0x0104~0x0143
    // Decimal     -> 308~323
    game_title = {&value[308], &value[323]};
    
    // Cartridge Address - Manufacturer Code
    // Hexadecimal -> 0x013F~0x0142
    // Decimal     -> 319~322
    manufacturer_code = {&value[319], &value[322]};

    cgb_flag = { value.at(323) };

    // Converts the value of addresses 324 and 325 to ASCII characters and concatenate them
    string s_lic;
    s_lic+=value.at(324);
    s_lic+=value.at(325);
    licensee_code = { s_lic };

    sgb_flag = { value.at(326) };

    cartridge_type = { value.at(327) };

    rom_size = { value.at(328) };

    ram_size = { value.at(329) };

    destination_code = { value.at(330) };

    old_licensee_code = { value.at(331) };

    mask_rom_version_number = { value.at(332) };

    header_checksum = { value.at(333) };

    global_checksum = { &value[334], &value[335] };

    //show_cartridge_info();
};


Cartridge::~Cartridge(){
    
}
