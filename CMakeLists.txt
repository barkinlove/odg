cmake_minimum_required (VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CONFIG_FILE_NAME "config.json")
set(BIN "${CMAKE_BINARY_DIR}/bin")
set(CONFIG_PATH "${BIN}/${CONFIG_FILE_NAME}")
set(CONFIG_CONTENT "{ \"shaderPath\": \"${CMAKE_SOURCE_DIR}/src/shaders/\" }")

project("odg")

find_package(SDL2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

message("${CMAKE_BINARY_DIR}")

add_executable(
  ${PROJECT_NAME} 
  ${PROJECT_SOURCE_DIR}/src/main.cxx
  ${PROJECT_SOURCE_DIR}/src/Game.cxx
  ${PROJECT_SOURCE_DIR}/src/Window.cxx
  ${PROJECT_SOURCE_DIR}/src/Renderer.cxx
  ${PROJECT_SOURCE_DIR}/src/Shader.cxx
  ${PROJECT_SOURCE_DIR}/src/ShaderFactory.cxx
  ${PROJECT_SOURCE_DIR}/src/Config.cxx
  ${PROJECT_SOURCE_DIR}/src/Math.cxx
  ${PROJECT_SOURCE_DIR}/src/Object.cxx
  ${PROJECT_SOURCE_DIR}/src/Camera.cxx
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic -Werror>
  )

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${BIN}")

file(CONFIGURE OUTPUT "${CONFIG_PATH}" CONTENT "${CONFIG_CONTENT}")

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src/include")

target_link_libraries(
  ${PROJECT_NAME} 
  PRIVATE 
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  spdlog::spdlog spdlog::spdlog_header_only
  GLEW::GLEW
  glm::glm
)
