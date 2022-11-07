cmake_minimum_required(VERSION 3.16)
project(archiver)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        archiver
        archiver.cpp
        CommandLineParser.cpp CommandLineParser.h
        archivate.cpp archivate.h
        dearchivate.cpp dearchivate.h
        write_eight_bits.cpp write_eight_bits.h
        write_encoded.cpp write_encoded.h
        haffman.cpp haffman.h
        node.cpp node.h
        read_nine_bits.cpp read_nine_bits.h
        bitstring.cpp bitstring.h
        accumulator.cpp accumulator.h
        helper.cpp helper.h)