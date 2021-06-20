# cmake version to be used
cmake_minimum_required(VERSION 3.12)

# project name
project(ndn-chord
        VERSION 0.1
        DESCRIPTION "A chord DHT based on NDN")

# flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Output binaries to a sub directory "bin"
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(NDN_CXX REQUIRED libndn-cxx)

# files
set(NDN_CHORD_LIB_SOURCE_FILES
        src/storage_memory.cpp)
# include
include_directories(${NDN_CXX_INCLUDE_DIRS})

# link
link_directories(${NDN_CXX_LIBRARY_DIRS})

include_directories(include)

# target
add_library(chord_lib STATIC ${NDN_CHORD_LIB_SOURCE_FILES})
target_compile_options(chord_lib PUBLIC ${NDN_CXX_CFLAGS})
target_link_libraries(chord_lib PUBLIC ${NDN_CXX_LIBRARIES})

# Executable name, srcs, and deps
add_executable(chord_node src/node_main.cpp)
target_compile_options(chord_node PUBLIC ${NDN_CXX_CFLAGS})
target_link_libraries(chord_node PUBLIC ${NDN_CXX_LIBRARIES} chord_lib)


# Enable cmake testing
include(CTest)
enable_testing()

# Enable GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Test executable name, srcs, and deps
add_executable(chord_test
        test/storage_memory_test.cpp)
target_link_libraries(chord_test chord_lib gtest_main gmock_main)

# Test binary
gtest_discover_tests(chord_test WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

# target/test targets
include(cmake/CodeCoverageReportConfig.cmake)
generate_coverage_report(TARGETS server server_lib TESTS server_test)

#configure
include(GNUInstallDirs)

install(TARGETS chord_node
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})