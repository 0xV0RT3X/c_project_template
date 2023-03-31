# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and supported languages
project(my_project C ASM_NASM)

# Create output directories for different operating systems
if(WIN32)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/windows)
elseif(APPLE)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/macos)
elseif(UNIX)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/linux)
endif()

# Set C standard to C11 and disable C extensions
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set NASM object format to ELF64
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

# C source files
set(C_SOURCES
    src/main.c
    src/calculations.c
)

# NASM source files
set(ASM_SOURCES
    src/add.asm
)

# Executable name
set(EXECUTABLE_NAME main)

# NASM compiler options
set(ASM_COMPILER_OPTIONS
    -f elf64
)

# C compiler options
set(C_COMPILER_OPTIONS
    -Wall
    -Wextra
    -Wpedantic
)

# Add executable target
add_executable(${EXECUTABLE_NAME} ${C_SOURCES} ${ASM_SOURCES})

# Add compiler options to target
target_compile_options(${EXECUTABLE_NAME} PRIVATE ${C_COMPILER_OPTIONS})

# Add NASM object target
add_custom_target(nasm_object
    COMMAND nasm ${ASM_COMPILER_OPTIONS} -o ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.o ${ASM_SOURCES}
    DEPENDS ${ASM_SOURCES}
)

# Add linker target
add_custom_target(linker
    COMMAND ${CMAKE_C_COMPILER} -o ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME} ${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}.o
    DEPENDS nasm_object ${EXECUTABLE_NAME}
)

# Add math library
target_link_libraries(${EXECUTABLE_NAME} m)

# Include directories
include_directories(include)

# Set output directory based on operating system
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<IF:$<PLATFORM_ID:Windows>,windows,$<IF:$<PLATFORM_ID:Darwin>,macos,linux>>
)

# Enable AddressSanitizer for debugging memory issues
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -fsanitize=address)
    target_link_libraries(${EXECUTABLE_NAME} asan)
endif()
