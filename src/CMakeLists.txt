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

set(SRC_FILES
  acrostic.cpp
  ClueView.cpp
  main.cpp
  mainwindow.cpp
  MessageWidget.cpp
  MissingLettersModel.cpp
  MissingLettersUI.cpp
  ui/DownMsg.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
  WIN32
  MACOSX_BUNDLE
  ${SRC_FILES}
)

set(QTLIBS Qt5::Widgets)
if(WIN32)
  set(QTLIBS ${QTLIBS} Qt5::WinMain)
endif()
target_link_libraries(${CMAKE_PROJECT_NAME}
  ${QTLIBS}
)

if(APPLE)
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND macdeployqt
    ARGS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.app -dmg)
elseif(WIN32)
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND windeployqt
    ARGS --dir $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>-deploy $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
  install(DIRECTORY $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>-deploy/
    DESTINATION bin
    USE_SOURCE_PERMISSIONS)
endif()

install(TARGETS ${CMAKE_PROJECT_NAME}
  RUNTIME DESTINATION bin
  BUNDLE DESTINATION bin)
