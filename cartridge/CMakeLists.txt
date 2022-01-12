add_library(
    cartridge
    src/cartridge.h
    src/cartridge.cpp
    )

target_include_directories(cartridge PUBLIC "src")