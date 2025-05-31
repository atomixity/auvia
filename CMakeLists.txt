cmake_minimum_required(VERSION 3.14)

project(Auvia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include headers
include_directories(
    auvia
)

# static library: auvia
set(AUVIA_SOURCES
    auvia/libs/asm.h
    auvia/libs/device.h
    auvia/libs/trap.h
    auvia/libs/type.h

    auvia/modules/bus/matu.h
    auvia/modules/memory/bank.h
    auvia/modules/storage/flash.h
)
set(AUVIA_CPP_SOURCES
    auvia/modules/bus/matu.cc
)
add_library(auvia STATIC ${AUVIA_CPP_SOURCES})

