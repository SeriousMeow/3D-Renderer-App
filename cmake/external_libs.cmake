include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Renderer
  GIT_REPOSITORY https://github.com/SeriousMeow/3D-Renderer
  GIT_TAG 02e52865ef03419a0e0104f529c29b83a04d61be
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(Renderer)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
