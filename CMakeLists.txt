cmake_minimum_required(VERSION 4.1)
project(DataStructure_Experiment)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructure_Experiment
        Josephus/Josephus.cpp
        ParkingProblem/ParkingProblem.cpp
        HuffmanTree/HuffmanTree.cpp
        CountyRoad/CountyRoad.cpp)
