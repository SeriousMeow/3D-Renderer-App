include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Renderer
  GIT_REPOSITORY https://github.com/SeriousMeow/3D-Renderer
  GIT_TAG e115cd9507f5865204b3ddbb629016a54cfd04b1
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(Renderer)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
