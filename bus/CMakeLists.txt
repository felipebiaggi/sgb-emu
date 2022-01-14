add_library(
    bus
    src/bus.h
    src/bus.cpp
    )
 
target_link_libraries(bus PRIVATE cpu)
target_link_libraries(bus PRIVATE cartridge)
target_include_directories(bus PUBLIC "src")