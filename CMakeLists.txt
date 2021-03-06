cmake_minimum_required(VERSION 2.8)

project(indicator-clipboard)

set(PNAME com.github.dawidd6.${PROJECT_NAME})

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBNOTIFY REQUIRED libnotify)
pkg_check_modules(QT5WIDGETS REQUIRED Qt5Widgets>=5.2.1)

add_definitions(${LIBNOTIFY_CFLAGS_OTHER} ${QT5WIDGETS_CFLAGS_OTHER} "-std=c++11 -fPIC")
include_directories(${LIBNOTIFY_INCLUDE_DIRS} ${QT5WIDGETS_INCLUDE_DIRS})
link_directories(${LIBNOTIFY_LIBRARY_DIRS} ${QT5WIDGETS_LIBRARY_DIRS})

add_library(lib src/${PROJECT_NAME}.cpp src/${PROJECT_NAME}.h)

# main
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} lib ${LIBNOTIFY_LIBRARIES} ${QT5WIDGETS_LIBRARIES})

# tests
enable_testing()

add_executable(trim_test tests/trim.cpp)
target_link_libraries(trim_test lib ${LIBNOTIFY_LIBRARIES} ${QT5WIDGETS_LIBRARIES})

add_test(trim_test trim_test)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES data/${PROJECT_NAME}.desktop DESTINATION share/applications RENAME ${PNAME}.desktop)
install(FILES data/${PROJECT_NAME}.desktop DESTINATION /etc/xdg/autostart RENAME ${PNAME}.desktop)
install(FILES data/icon.svg DESTINATION share/icons/hicolor/scalable/apps RENAME ${PNAME}.svg)
install(FILES data/icon_16.png DESTINATION share/icons/hicolor/16x16/apps RENAME ${PNAME}.png)
install(FILES data/icon_20.png DESTINATION share/icons/hicolor/20x20/apps RENAME ${PNAME}.png)
install(FILES data/icon_22.png DESTINATION share/icons/hicolor/22x22/apps RENAME ${PNAME}.png)
install(FILES data/icon_24.png DESTINATION share/icons/hicolor/24x24/apps RENAME ${PNAME}.png)
install(FILES data/icon_42.png DESTINATION share/icons/hicolor/42x42/apps RENAME ${PNAME}.png)
install(FILES data/icon_48.png DESTINATION share/icons/hicolor/48x48/apps RENAME ${PNAME}.png)
install(FILES data/icon_64.png DESTINATION share/icons/hicolor/64x64/apps RENAME ${PNAME}.png)
