#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include <iostream>
#include <sstream>
#include <cstdint>
#include <vector>
#include <string>

using namespace std;


class Cartridge {
public:
    Cartridge(vector<uint8_t> value);    
    ~Cartridge();

public:
    

private:
    vector<uint8_t> game_data {};
    string game_title {};
    string manufacturer_code {};
    uint8_t cgb_flag {};
    string licensee_code {};
    uint8_t sgb_flag {};
    uint8_t cartridge_type {};
    uint8_t rom_size {};
    uint8_t ram_size {};
    uint8_t destination_code {};
    uint8_t old_licensee_code {};
    uint8_t mask_rom_version_number {};
    uint8_t header_checksum {};
    string global_checksum {};
    
    void show_cartridge_info() {
        cout << "Title: " << game_title << endl;
        cout << "Manufacturer Code: " << manufacturer_code << endl;
        cout << "CGB Flag: " << hex << static_cast<int>(cgb_flag) << endl;
        cout << "Licensee Code: " << licensee_code << endl;
        cout << "SGB Flag: " << hex << static_cast<int>(sgb_flag) << endl;
        cout << "Cartridge Type: " << hex << static_cast<int>(cartridge_type) << endl;
        cout << "ROM Size: " << hex << static_cast<int>(rom_size) << endl;
        cout << "RAM Size: " << hex << static_cast<int>(ram_size) << endl;
        cout << "Destination Code: " << hex << static_cast<int>(destination_code) << endl;
        cout << "Old Licensee Code: " << hex << static_cast<int>(old_licensee_code) << endl;
        cout << "Header Checksum: " << hex << static_cast<int>(header_checksum) << endl;
        cout << "Global Checksum: " << global_checksum << endl;
    }

};


#endif