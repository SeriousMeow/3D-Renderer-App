include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Renderer
  GIT_REPOSITORY https://github.com/SeriousMeow/3D-Renderer
  GIT_TAG 15a9e77770ac29fc20784b2c22122f20e23c33d1
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(Renderer)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
