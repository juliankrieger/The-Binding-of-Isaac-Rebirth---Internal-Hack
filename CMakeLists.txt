cmake_minimum_required(VERSION 3.0)
project(IsaacInternal)

set(CMAKE_CXX_STANDARD 20)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (demo)
add_subdirectory (dll)
add_subdirectory(lib)