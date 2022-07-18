# CMakeList.txt : CMake project for POGengine, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

project ("POGengine")

set(SDL2_DIR "/SDL2-2.0.22-d") # CHANGE THIS TO WHERE YOUR SDL IS

add_executable (	
 POGengine

 "src/main.cpp"

 "src/engine/helper_macos.h"
 "src/engine/engine.h" 
 "src/engine/private/engine.cpp"

 "src/renderer/renderer.h"
 "src/renderer/renderer-inl.h"
 "src/renderer/private/renderer.cpp"

 "src/util/timer.h"
 "src/util/private/timer.cpp" "src/physics/updater.h" "src/physics/private/updater.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET POGengine PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(TARGET POGengine POST_BUILD COMMAND ${CMAKE_COMMAND}
 -E copy_directory "${PROJECT_SOURCE_DIR}/libs" $<TARGET_FILE_DIR:POGengine>) # makes debugging ez

find_package(SDL2 REQUIRED)

include_directories(POGengine ${SDL2_INCLUDE_DIRS})
target_link_libraries(POGengine ${SDL2_LIBRARIES})