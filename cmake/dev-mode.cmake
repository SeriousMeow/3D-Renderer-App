include(cmake/folders.cmake)

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(test)
endif()

add_custom_target(
  run-exe
  COMMAND Renderer_App_exe
  VERBATIM)
add_dependencies(run-exe Renderer_App_exe)

option(BUILD_DOCS "Build documentation using Doxygen" OFF)
if(BUILD_DOCS)
  include(cmake/docs.cmake)
endif()

option(ENABLE_COVERAGE "Enable coverage support separate from CTest's" OFF)
if(ENABLE_COVERAGE)
  include(cmake/coverage.cmake)
endif()

include(cmake/lint-targets.cmake)
include(cmake/spell-targets.cmake)

add_folders(Project)
