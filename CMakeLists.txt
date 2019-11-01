cmake_minimum_required(VERSION 3.15)
project("utilz" VERSION 0.1 LANGUAGES CXX)


# compiler specific stuff
set(utilz_compiler_flags "")
set(utilz_linker_flags "")
#
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

	set(utilz_compiler_flags
        /std:c++17
        /permissive-
        /fp:fast
        -DWIN32_LEAN_AND_MEAN
        /MP
        /W4
        /w14254
        /w14263
        /w14287
        /we4289
        /w14296
        /w14311
        /w14545
        /w14546
        /w14547
        /w14549
        /w14555
        /w14640
        /w14826
        /w14905
        /w14906
        /w14928)

    set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ${MATH_TEST_NAME})

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

	set(utilz_compiler_flags
        -DNDEBUG
        -O3
        -std=c++17
        -ffast-math
        -lstdc++
        -Weverything
        -Wno-error
        -Wno-unused-command-line-argument
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-global-constructors
        -Wno-exit-time-destructors
        -Wno-padded
        -Wno-weak-vtables
        -Wno-disabled-macro-expansion
        -Wno-deprecated
        -Wno-covered-switch-default
        -Wno-inconsistent-missing-destructor-override)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

	set(utilz_compiler_flags
        -DNDEBUG
        -O3
        -std=c++17
        -ffast-math
        -lstdc++
        -DBOOST_NO_AUTO_PTR
        -pedantic
        -Wall
        -Wextra
        -Wshadow
        -Wfloat-equal
        -Wundef
        -Wswitch-default
        -Wswitch-enum
        -Wunreachable-code
        -Weffc++
        -Wunused-parameter
        -Wfatal-errors
        -Wstrict-null-sentinel
        -Wconversion
        -Wsign-conversion)

else()
    message(FATAL_ERROR " Unknwon Compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()


# print all custom flags
message(${CMAKE_CXX_COMPILER_ID} " Custom Compile Flags: " ${utilz_compiler_flags})
message(${CMAKE_CXX_COMPILER_ID} " Custom Link Flags   : " ${utilz_linker_flags})


# find all utilz headers (utilz/*.hpp) and their corresponding test files (test/*.cpp)
# WARNING: The use of cmake file globs may increase your risk of anal clenching, pretentious tirades, and hate crimes.
file(GLOB utilz_header_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utilz/*.?pp")
file(GLOB utilz_test_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")


# setup the target and test for each utilz header
include(CTest)
foreach(utilz_test_file ${utilz_test_files})
    
    get_filename_component(utilz_test_name ${utilz_test_file} NAME_WE)

    set(utilz_test_all_files "${utilz_test_file}" "${utilz_header_files}")
    add_executable(${utilz_test_name} ${utilz_test_all_files})

    target_compile_options(${utilz_test_name} PUBLIC ${utilz_compiler_flags})
    target_compile_features(${utilz_test_name} PUBLIC cxx_std_17)
    target_link_options(${utilz_test_name} PUBLIC ${utilz_linker_flags})
    target_include_directories(${utilz_test_name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
    target_include_directories(${utilz_test_name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/test")
    
    add_test(NAME ${utilz_test_name} COMMAND ${utilz_test_name})
endforeach()
