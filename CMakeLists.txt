###
# Acrostica - Simple acrostic creator
# Copyright (C) 2014-2015 James McCoy <jamessan@jamessan.com>
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
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

project(acrostica)
set(PROJECT_LONGNAME "Acrostica")
set(PROJECT_VERSION "1.0.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Acrostica is an acrostic creator")
  set(CPACK_PACKAGE_VENDOR "James McCoy <jamessan@jamessan.com>")
  set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
  set(CPACK_PACKAGE_CONTACT "jamessan@jamessan.com")
  set(CPACK_PACKAGE_EXECTUABLES "acrostica;Acrostica")
  if (APPLE)
    set(CPACK_GENERATOR "TGZ;DragNDrop")
    set(CPACK_DMG_FORMAT "UDZO")
    include(CPackDMG)
  else()
    set(CPACK_GENERATOR "TGZ")
  endif()
  include(CPack)
endif()

find_package(Qt5Widgets REQUIRED)

if (NOT MSVC)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
endif()

add_subdirectory(src)
