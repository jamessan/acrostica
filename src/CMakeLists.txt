###
# Acrostica - Simple acrostic creator
# Copyright (C) 2014-2018 James McCoy <jamessan@jamessan.com>
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

set(SRC_FILES
  acrostic.cpp
  ClueWidget.cpp
  main.cpp
  mainwindow.cpp
  MissingLettersModel.cpp
  MissingLettersUI.cpp
  ui/DownMsg.cpp
)

add_executable(${CMAKE_PROJECT_NAME} WIN32
  ${SRC_FILES}
)
target_link_libraries(${CMAKE_PROJECT_NAME}
  Qt5::Widgets
)

install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME DESTINATION bin)
