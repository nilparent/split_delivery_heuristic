cmake_minimum_required(VERSION 2.6)
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

project(split_delivery_heuristic)

add_executable(split_delivery_heuristic instance_generator.cpp main.cpp Solution.cpp Solution.h instance_generator.h heuristique.h heuristique.cpp tools.cpp tools.h constante_proj.h)
ImagineUseModules(split_delivery_heuristic Graphics)

