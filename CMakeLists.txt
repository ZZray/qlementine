cmake_minimum_required(VERSION 3.21.0)

# Enable parallel build (not enabled by default on Windows).
set(CMAKE_BUILD_PARALLEL_LEVEL $ENV{NUMBER_OF_PROCESSORS})

# Set project information.
project("qlementine"
  LANGUAGES CXX
  VERSION 1.4.2.0
  DESCRIPTION "Modern QStyle for desktop Qt applications."
)
set(PROJECT_COPYRIGHT "© Olivier Cléro, MIT License.")

include(GNUInstallDirs)

# Build options.
option(QLEMENTINE_SANDBOX "Build the sandbox application." ON)
option(QLEMENTINE_SHOWCASE "Build the showcase application." ON)
option(QLEMENTINE_ICONS "Build the vendored qlementine-icons library." ON)

# Accept both Qt root paths and lib/cmake/Qt{5,6} paths on Windows.
if(WIN32 AND CMAKE_PREFIX_PATH)
  set(_qlementine_prefix_path "${CMAKE_PREFIX_PATH}")
  string(REPLACE "\\" "/" _qlementine_prefix_path "${_qlementine_prefix_path}")
  foreach(_qlementine_qt_package Qt5 Qt6)
    string(REPLACE "/lib/cmake/${_qlementine_qt_package}" "" _qlementine_normalized_prefix_path
      "${_qlementine_prefix_path}")
    if(NOT _qlementine_normalized_prefix_path STREQUAL _qlementine_prefix_path)
      set(CMAKE_PREFIX_PATH "${_qlementine_normalized_prefix_path}")
      break()
    endif()
  endforeach()
endif()

# Global flags.
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if(NOT CMAKE_OSX_DEPLOYMENT_TARGET)
  set(CMAKE_OSX_DEPLOYMENT_TARGET "13.6")
endif()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Find Qt.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Svg)
set(QLEMENTINE_QT_PACKAGE_PREFIX "Qt${QT_VERSION_MAJOR}")

if(QT_VERSION_MAJOR EQUAL 6)
  qt_standard_project_setup()
endif()

# The library.
add_subdirectory(lib)

if(QLEMENTINE_ICONS OR QLEMENTINE_SHOWCASE)
  add_subdirectory(icons)
endif()

# Example apps using the lib.
if(QLEMENTINE_SANDBOX)
  add_subdirectory(sandbox)
endif()

if(QLEMENTINE_SHOWCASE)
  add_subdirectory(showcase)
endif()
