# ---- Dependencies ----

set(extract_timestamps "")
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24")
  set(extract_timestamps DOWNLOAD_EXTRACT_TIMESTAMP YES)
endif()

# ---- Declare documentation target ----

set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/docs")

set(working_dir "${PROJECT_BINARY_DIR}/docs")

foreach(file IN ITEMS Doxyfile)
  configure_file("docs/${file}.in" "${working_dir}/${file}" @ONLY)
endforeach()

set(config "${working_dir}/Doxyfile")

add_custom_target(
  app_docs
  COMMAND "${CMAKE_COMMAND}" -E remove_directory
          "${DOXYGEN_OUTPUT_DIRECTORY}/html"
  COMMAND "doxygen" "${config}"
  COMMENT "Building documentation using Doxygen"
  WORKING_DIRECTORY "${working_dir}"
  VERBATIM)
