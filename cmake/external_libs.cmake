include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Renderer
  GIT_REPOSITORY https://github.com/SeriousMeow/3D-Renderer
  GIT_TAG e00a1ae3b033c4a624eef617078c0ff4b1f97122
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(Renderer)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
