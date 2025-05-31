cmake_minimum_required(VERSION 3.14)

project(Auvia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include headers
include_directories(
    src
)

# static library: auvia
set(AUVIA_SOURCES
    src/libs/asm.h
    src/libs/device.h
    src/libs/trap.h
    src/libs/type.h

    src/modules/bus/matu.h
    src/modules/memory/bank.h
    src/modules/storage/flash.h
)
set(AUVIA_CPP_SOURCES
    src/modules/bus/matu.cc
)
add_library(auvia STATIC ${AUVIA_CPP_SOURCES})

