# File        tests/CMakeLists.txt
# Author      GPT-6.2 Sol
# About       Builds the Ulang test executable.

add_executable(ulang_test main.cpp)
target_link_libraries(ulang_test PRIVATE ulang)

add_test(NAME ulang_test COMMAND ulang_test)
