﻿# CMakeList.txt : CMake project for POGengine, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

# project name
project ("POGengine")

# dirs of where sdl is on my machine
set(SDL2_DIR		"/SDL2-2.0.22-d")
set(SDL2_image_DIR	"/SDL2_image-2.6.0")
set(SDL2_ttf_DIR	"/SDL2_ttf-2.20.1")

add_executable (	
 POGengine

 "src/main.cpp"

 "src/base/helper_macos.h"
 "src/base/engine.h" 
 "src/base/engine.cpp"
 "src/base/console.h"

 "src/event/event.h"
 "src/event/private/event.cpp"

 "src/game/game-inl.h"
 "src/game/game.cpp"
 "src/game/game.h"

 "src/game/ai/ai.h"
 "src/game/ai/private/ai.cpp"

 "src/game/logic/collision.h"
 "src/game/logic/private/collision.cpp"

 "src/game/world/game-object.h"
 "src/game/world/game-object-inl.h"

 "src/game/world/component/texture.h"
 "src/game/world/component/texture-inl.h"
 "src/game/world/component/transform.h"
 "src/game/world/component/transform-inl.h"
 "src/game/world/component/aabb.h"
 "src/game/world/component/aabb-inl.h"
 "src/game/world/component/triangle.h"
 "src/game/world/component/triangle-inl.h"
 "src/game/world/component/geometry.h"
 "src/game/world/component/geometry-inl.h"
 "src/game/world/component/private/texture.cpp"
 "src/game/world/component/private/aabb.cpp"
 "src/game/world/component/private/transform.cpp"
 "src/game/world/component/private/geometry.cpp"
 
 "src/game/world/entities/player.h"
 "src/game/world/entities/private/player.cpp"
 "src/game/world/entities/agent.h"
 "src/game/world/entities/private/agent.cpp"
 "src/game/world/entities/camera.h"
 "src/game/world/entities/private/camera.cpp"
 "src/game/world/entities/food.h"
 "src/game/world/entities/private/food.cpp"

 "src/game/world/objects/text-object.h"
 "src/game/world/objects/texture-object.h"
 "src/game/world/objects/texture-object-inl.h"
 "src/game/world/objects/geometry-object.h"
 "src/game/world/objects/geometry-object-inl.h"
 "src/game/world/objects/private/text-object.cpp"
 "src/game/world/objects/private/texture-object.cpp"
 "src/game/world/objects/private/geometry-object.cpp"

 "src/updater/updater.h" 
 "src/updater/updater-inl.h"
 "src/updater/controller.h"
 "src/updater/controller-inl.h"
 "src/updater/input.h"
 "src/updater/private/controller.cpp"
 "src/updater/private/updater.cpp" 
 "src/updater/private/input.cpp" 

 "src/renderer/renderer.h"
 
 "src/renderer/assets.h" 
 
 "src/renderer/private/assets.cpp"
 "src/renderer/private/renderer.cpp"

 "src/util/timer.h"
 "src/util/size.h"
 "src/util/vector2d.h" 
 "src/util/vector3d.h"
 "src/util/private/timer.cpp" 
 "src/util/maths.h" 
 "src/util/file.h"
  "src/game/world/objects/biome-object.h" "src/game/world/objects/private/biome-object.cpp" "src/renderer/camera.h" "src/renderer/private/camera.cpp" "src/game/ai/god.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# makes debugging ez
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
 -E copy_directory "${PROJECT_SOURCE_DIR}/libs" $<TARGET_FILE_DIR:POGengine>) 

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_subdirectory("${PROJECT_SOURCE_DIR}/libs/eventbus/lib")

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} Dexode::EventBus)