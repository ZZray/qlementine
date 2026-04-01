# Declare files.
file(GLOB_RECURSE QRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/*.qrc")
file(GLOB_RECURSE HPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/include/oclero/qlementine/icons/*.hpp")
file(GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/icons/*.cpp")

# Create target.
add_library(qlementine-icons STATIC
  ${HPP_FILES}
  ${CPP_FILES}
  ${QRC_FILES}
)

target_include_directories(qlementine-icons
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(qlementine-icons
  PUBLIC
    ${QLEMENTINE_QT_PACKAGE_PREFIX}::Core
  PRIVATE
    ${QLEMENTINE_QT_PACKAGE_PREFIX}::Svg
)

set_target_properties(qlementine-icons
  PROPERTIES
    LINKER_LANGUAGE CXX
    AUTOMOC ON
    AUTORCC ON
    OUTPUT_NAME qlementine-icons
    PROJECT_LABEL qlementine-icons
    FOLDER dependencies
    DEBUG_POSTFIX _debug
)

target_compile_features(qlementine-icons PUBLIC cxx_std_17)

target_compile_options(qlementine-icons
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/MP /utf-8 /WX /W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
  FILES
    ${HPP_FILES}
    ${CPP_FILES}
    ${QRC_FILES}
)
