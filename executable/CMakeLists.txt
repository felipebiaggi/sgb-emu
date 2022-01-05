add_executable(sgb-emu main.cpp)
target_link_libraries(sgb-emu PRIVATE cpu)
target_link_libraries(sgb-emu PRIVATE bus)

