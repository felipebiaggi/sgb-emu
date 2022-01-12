#ifndef LOAD_FILE_H
#define LOAD_FILE_H
#include <filesystem>
#include <string>
#include <cstdint>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct GameRomException: public exception{
    virtual const char *what() const throw()
    {
        return "Game ROM doesn't exist!";
    } 
};

struct GameRomNotFoundException: public exception{
    virtual const char *what() const throw()
    {
        return "Game ROM not found";
    } 
};


struct FileStruct {
    string filename;
    string extension;
    string path;
    vector<string> argv;
};


void validate_rom_name(char *argv[]){
    std::string filename = argv[1];

}

vector<uint8_t> load_game_file(int argc, char *argv[]){
    string debug;
    

    if (argc <= 1){
        throw GameRomException();
    } else if(argc >= 3){
        debug = argv[2];
    }
    
    filesystem::path f_path(argv[1]);

    ifstream s_file(filesystem::absolute(f_path), ios::binary);

    if (!s_file.good()){
        throw GameRomNotFoundException();
    } else {

        int count = 0;
        stringstream c_string;

        if(debug == "--debug"){
            while(!s_file.eof()){
                int value = s_file.get();
                
                if (count < 32){
                    c_string << setfill('0') << setw(2) << hex << value << " "; 
                } else{
                    count = 0;
                    cout << c_string.str() << endl;
                    c_string.str(string());
                    c_string << hex << value << " "; 
                }
                count++;
            }

            s_file = ifstream(filesystem::absolute(f_path), ios::binary);
        }

        s_file.seekg(0, ios::end);
        cout << "Filename and extension: " << f_path.filename() << endl;
        cout << "File size: " << s_file.tellg() << endl; 
        cout << "Current path: " << filesystem::current_path() << endl;
        cout << "Absolute path: " << filesystem::absolute(f_path) << endl;
    }

    s_file.seekg(0, ios::beg);

    vector<uint8_t> game_data((istreambuf_iterator<char>(s_file)), istreambuf_iterator<char>());

    s_file.close();

    return game_data;
}

#endif
