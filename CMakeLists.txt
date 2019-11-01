cmake_minimum_required(VERSION 3.15)
project("utilz" VERSION 0.1 LANGUAGES CXX)


# sfml
find_package(SFML 2.5 COMPONENTS window graphics REQUIRED)


# compiler specific stuff
set(compiler_flags "")
set(linker_flags "")
#
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

	set(compiler_flags
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

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

	set(compiler_flags
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

	set(compiler_flags
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
message(${CMAKE_CXX_COMPILER_ID} " Custom Compile Flags: " ${compiler_flags})
message(${CMAKE_CXX_COMPILER_ID} " Custom Link Flags: " ${linker_flags})


# find all utilz headers (utilz/*.hpp) and their corresponding test files (test/*.cpp)
# WARNING: The use of cmake file globs may increase your risk of anal clenching, pretentious tirades, and hate crimes.
file(GLOB lib_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utilz/*.?pp")
file(GLOB catch_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/catch/*.?pp")
file(GLOB test_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")


# just a helper function to eliminate lots of duplicated code
function(setup_target name)
    target_link_options(${name} PUBLIC ${linker_flags})
    target_link_libraries(${name} sfml-window sfml-graphics sfml-audio)
    target_compile_options(${name} PUBLIC ${compiler_flags})
    target_compile_features(${name} PUBLIC cxx_std_17)
    target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
    target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/test")
    target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/catch")
endfunction()


# This library is not required, but it speeds up compile times significantly.
# Compiling Catch2's header and main() takes 10-20 seconds -even all by itself without any testing code!
# This is not a big deal with only one test.cpp, but with many it get ridiculous.
# So this library allows Catch2 to be compiled only once for each test.
add_library(catch_main OBJECT "${catch_files}")
setup_target(catch_main)


# make utilz tests
include(CTest)
foreach(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    set(test_all_files "${test_file}" "${lib_files}")
    add_executable(${test_name} ${test_all_files} $<TARGET_OBJECTS:catch_main>)
    setup_target(${test_name})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
