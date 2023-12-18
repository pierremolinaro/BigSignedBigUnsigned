cmake_minimum_required (VERSION 3.13)

project(CANMolinaroAnalyzer)

#add_definitions( -DLOGIC2 )

# enable generation of compile_commands.json, helpful for IDEs to locate include files.
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# custom CMake Modules are located in the cmake directory.
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#include(ExternalAnalyzerSDK)

set(SOURCES
sources/BigSigned-add.cpp
sources/BigSigned-bit.cpp
sources/BigSigned-chunk-operations.cpp
sources/BigSigned-constructors.cpp
sources/BigSigned-conversions.cpp
sources/BigSigned-divide.cpp
sources/BigSigned-logic-operations.cpp
sources/BigSigned-multiply.cpp
sources/BigSigned-print.cpp
sources/BigSigned-shifts.cpp
sources/BigSigned-subtract.cpp
sources/BigSigned-utilities.cpp
sources/BigSigned.cpp
sources/BigSigned.h
sources/BigUnsigned-add.cpp
sources/BigUnsigned-bit.cpp
sources/BigUnsigned-chunk-operations.cpp
sources/BigUnsigned-constructors.cpp
sources/BigUnsigned-conversions.cpp
sources/BigUnsigned-divide-naive.cpp
sources/BigUnsigned-divide.cpp
sources/BigUnsigned-logic-operations.cpp
sources/BigUnsigned-multiply.cpp
sources/BigUnsigned-print.cpp
sources/BigUnsigned-shifts.cpp
sources/BigUnsigned-subtract.cpp
sources/BigUnsigned-utilities.cpp
sources/ChunkSharedArray.cpp
sources/MF_Assert.cpp
sources/galgas-random.cpp
)

#add_analyzer_plugin(${PROJECT_NAME} SOURCES ${SOURCES})
