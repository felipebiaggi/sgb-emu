#ifndef LOAD_FILE_H
#define LOAD_FILE_H
#include <filesystem>
#include <exception>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

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

void load_game_file(int argc, char *argv[]){

    if (argc <= 1){
        throw GameRomException();
    }
    
    filesystem::path f_path(argv[1]);

    ifstream s_file(filesystem::absolute(f_path), ios::binary|ios::ate);

    if (!s_file.good()){
        throw GameRomNotFoundException();
    } else {
        cout << "Filename and extension: " << f_path.filename() << endl;
        cout << "File size: " << s_file.tellg() << endl; 
        cout << "Current path: " << filesystem::current_path() << endl;
        cout << "Absolute path: " << filesystem::absolute(f_path) << endl;
    }

}

#endif
