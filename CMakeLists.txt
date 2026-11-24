cmake_minimum_required(VERSION 3.25)
project(O_o_OOS LANGUAGES C CXX)

# Standalone builds fetch the compatible core. When integrated, the host supplies it.
if(NOT TARGET oor::core)
    include(FetchContent)
    set(OOR_FORMATS "")
    set(OOR_BUILD_TESTS OFF)
    set(OOR_BUILD_PYTHON OFF)
    set(OOR_BUILD_WASM OFF)
    FetchContent_Declare(oor_reader
        GIT_REPOSITORY https://github.com/jcdulas/O_o_Reader.git
        GIT_TAG 492ad01cf4930f29449b981c3d82f1433ce09a68)
    FetchContent_MakeAvailable(oor_reader)
endif()

add_library(oor_format_oos STATIC
    src/formats/Oos.cpp
    src/deck/records/ModelFileLexer.cpp
    src/model/core/ModelFileReader.cpp
    src/model/core/ModelFileWriter.cpp)
add_library(oor::oos ALIAS oor_format_oos)
target_compile_features(oor_format_oos PUBLIC cxx_std_20)
set_target_properties(oor_format_oos PROPERTIES POSITION_INDEPENDENT_CODE ON CXX_EXTENSIONS OFF)
target_include_directories(oor_format_oos PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(oor_format_oos PUBLIC oor::core)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(oor_format_oos PRIVATE -Wall -Wextra -Wpedantic)
    if(OOR_WARNINGS_AS_ERRORS)
        target_compile_options(oor_format_oos PRIVATE -Werror)
    endif()
endif()
if(EMSCRIPTEN)
    target_compile_options(oor_format_oos PUBLIC -sMEMORY64=1 -fwasm-exceptions)
    target_link_options(oor_format_oos PUBLIC -sMEMORY64=1 -fwasm-exceptions)
endif()

if(PROJECT_IS_TOP_LEVEL)
    include(CTest)
    if(BUILD_TESTING AND NOT EMSCRIPTEN)
        add_executable(oos_round_trip tests/RoundTrip.cpp)
        target_link_libraries(oos_round_trip PRIVATE oor::oos)
        add_test(NAME oos.round-trip COMMAND oos_round_trip "${CMAKE_CURRENT_BINARY_DIR}/round-trip.oos")
    endif()
endif()
