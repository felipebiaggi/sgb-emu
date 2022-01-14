add_library(
    cpu
    src/lr35902.h
    src/lr35902.cpp
    src/cb.h
    src/cb.cpp
    )


target_link_libraries(cpu PRIVATE cartridge)
target_link_libraries(cpu PRIVATE bus)
target_include_directories(cpu PUBLIC "src")
