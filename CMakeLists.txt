###
# Acrostica - Simple acrostic creator
# Copyright © 2014-2018 James McCoy <jamessan@jamessan.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
###

cmake_minimum_required(VERSION 2.8)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
      "None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

project(acrostica)
set(PROJECT_LONGNAME "Acrostica")
set(PROJECT_VERSION "0.2.0")

# Do not recursively expand variables
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  add_definitions(/W4 /WX /FIacrostica/pragma.h)
  add_definitions(/MP)
else()
  add_definitions(-Wall -Werror)
endif()

# Do not implicitly link to qmain
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

set(CMAKE_AUTOMOC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Acrostica is an acrostic creator")
  set(CPACK_PACKAGE_VENDOR "James McCoy <jamessan@jamessan.com>")
  set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
  set(CPACK_PACKAGE_CONTACT "jamessan@jamessan.com")
  set(CPACK_PACKAGE_EXECTUABLES "acrostica;Acrostica")
  if (APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_FORMAT "UDZO")
    include(CPackDMG)
  elseif(MSVC)
    set(CPACK_GENERATOR "ZIP")
  else()
    set(CPACK_GENERATOR "TGZ")
  endif()
  include(CPack)
endif()

find_package(Qt5Widgets REQUIRED)

include_directories(include)
add_subdirectory(src)
