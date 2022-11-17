cmake_minimum_required (VERSION 3.8.2)

add_library (STB STATIC "Source/STB.cpp")
target_include_directories (STB PUBLIC "Include")
