cmake_minimum_required(VERSION 3.21)
project(KiDefend LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
add_executable(KiDefend 
src/utility.cpp 
src/game_object.cpp
src/bullet.cpp
src/enemy.cpp 
src/button.cpp 
src/turret.cpp 
src/path.cpp 
src/level.cpp 
src/core.cpp 
src/main.cpp 
)
target_link_libraries(KiDefend PRIVATE sfml-graphics)
target_compile_features(KiDefend PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET KiDefend POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:KiDefend> $<TARGET_FILE_DIR:KiDefend> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS KiDefend)
