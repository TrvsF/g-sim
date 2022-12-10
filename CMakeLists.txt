# CMakeList.txt : CMake project for POGengine, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

project ("POGengine")

set(SDL2_DIR "/SDL2-2.0.22-d") # CHANGE THIS TO WHERE YOUR SDL IS
set(SDL2_image_DIR "/SDL2_image-2.6.0")

add_executable (	
 POGengine

 "src/main.cpp"

 "src/base/helper_macos.h"
 "src/base/engine.h" 
 "src/base/engine.cpp"

 "src/game/game-inl.h"
 "src/game/game.cpp"
 "src/game/game.h"

 "src/game/logic/level.h"

 "src/game/object/game-object.h"
 "src/game/object/game-object-inl.h"

 "src/game/object/component/texture.h"
 "src/game/object/component/texture-inl.h"
 "src/game/object/component/transform.h"
 "src/game/object/component/transform-inl.h"
 "src/game/object/component/aabb.h"
 "src/game/object/component/aabb-inl.h"
 "src/game/object/component/triangle.h"
 "src/game/object/component/triangle-inl.h"
 "src/game/object/component/geometry.h"
 "src/game/object/component/geometry-inl.h"
 "src/game/object/component/private/texture.cpp"
 "src/game/object/component/private/aabb.cpp"
 "src/game/object/component/private/transform.cpp"
 "src/game/object/component/private/geometry.cpp"
 
 "src/game/object/objects/player.h"
 "src/game/object/objects/private/player.cpp"
 "src/game/object/objects/agent.h"
 "src/game/object/objects/private/agent.cpp"
 "src/game/object/objects/camera.h"
 "src/game/object/objects/private/camera.cpp"
  
 "src/game/object/objects/abs/texture-object.h"
 "src/game/object/objects/abs/texture-object-inl.h"
 "src/game/object/objects/abs/geometry-object.h"
 "src/game/object/objects/abs/geometry-object-inl.h"
 "src/game/object/objects/abs/private/texture-object.cpp"
 "src/game/object/objects/abs/private/geometry-object.cpp"

 "src/updater/updater.h" 
 "src/updater/updater-inl.h"
 "src/updater/controller.h"
 "src/updater/controller-inl.h"
 "src/updater/input.h"
 "src/updater/private/controller.cpp"
 "src/updater/private/updater.cpp" 
 "src/updater/private/input.cpp" 

 "src/renderer/renderer.h"
 "src/renderer/renderer-inl.h"
 "src/renderer/assets.h" 
 
 "src/renderer/private/assets.cpp"
 "src/renderer/private/renderer.cpp"

 "src/util/timer.h"
 "src/util/size.h"
 "src/util/vector2d.h" 
 "src/util/vector3d.h"
 "src/util/private/timer.cpp" 
 "src/util/maths.h" 
 "src/game/object/objects/food.h" "src/game/object/objects/private/food.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
 -E copy_directory "${PROJECT_SOURCE_DIR}/libs" $<TARGET_FILE_DIR:POGengine>) # makes debugging ez

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${PROJECT_NAME} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})