cmake_minimum_required(VERSION 3.26)
project(RUNE)

set(CMAKE_CXX_STANDARD 11)

add_executable(rune src/main.cpp
        src/k_bin.cpp
        src/k_bin.h
        src/fasta_io.cpp
        src/fasta_io.h
        src/msg.h
        src/bin_io.cpp
        src/bin_io.h
        src/kite.h
        src/dumper.cpp
        src/dumper.h
        src/loader.cpp
        src/loader.h
)

install(TARGETS rune
        DESTINATION bin)
