cmake_minimum_required(VERSION 3.16.3)
project(hash_enc1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER "g++")

set(CMAKE_BUILD_TYPE release)

#DO NOT REMOVE "#" :(
#ADD_COMPILE_OPTIONS(-g -Wall)
#SET(CMAKE_EXE_LINKER_FLAGS "-static -Wl,--gc-sections")

IF (WIN32)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
ELSE()
    LINK_DIRECTORIES(/usr/lib)
ENDIF()

add_executable(hash_enc1 hash_enc.h hash_enc_linux_support.h hash_enc_linux_support.cpp hash_enc.cpp hash_enc_def.h main.cpp)
