# CMakeList.txt : CMake project for aes_string_pass, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("aes_string_pass")

# Add source to this project's executable.
add_executable (aes_string_pass "aes_string_pass.cpp" "aes_string_pass.h" "aes.cpp" "aes_class.cpp")

# TODO: Add tests and install targets if needed.
