include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
  Renderer
  GIT_REPOSITORY https://github.com/SeriousMeow/3D-Renderer
  GIT_TAG 67ccf0bef226c0292a5b5f823ce8b57f516c4182
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(Renderer)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)
