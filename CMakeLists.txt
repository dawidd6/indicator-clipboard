cmake_minimum_required(VERSION 3.5)

project(indicator-clipboard)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBNOTIFY REQUIRED libnotify)
pkg_check_modules(QT5WIDGETS REQUIRED Qt5Widgets)


include_directories(${LIBNOTIFY_INCLUDE_DIRS}
                    ${QT5WIDGETS_INCLUDE_DIRS})

link_directories(${LIBNOTIFY_LIBRARY_DIRS}
                 ${QT5WIDGETS_LIBRARY_DIRS})

add_definitions(${LIBNOTIFY_CFLAGS_OTHER}
                ${QT5WIDGETS_CFLAGS_OTHER})

add_executable(${PROJECT_NAME}
               ${PROJECT_NAME}.cpp)

target_link_libraries(${PROJECT_NAME}
                      ${LIBNOTIFY_LIBRARIES}
                      ${QT5WIDGETS_LIBRARIES})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES data/${PROJECT_NAME}.desktop DESTINATION share/applications RENAME com.github.dawidd6.indicator-clipboard.desktop)
install(FILES data/icon.svg DESTINATION share/icons/hicolor/scalable/apps RENAME com.github.dawidd6.indicator-clipboard.svg)
install(FILES data/icon_16.png DESTINATION share/icons/hicolor/16x16/apps RENAME com.github.dawidd6.indicator-clipboard.png)
install(FILES data/icon_20.png DESTINATION share/icons/hicolor/20x20/apps RENAME com.github.dawidd6.indicator-clipboard.png)
install(FILES data/icon_22.png DESTINATION share/icons/hicolor/22x22/apps RENAME com.github.dawidd6.indicator-clipboard.png)
install(FILES data/icon_24.png DESTINATION share/icons/hicolor/24x24/apps RENAME com.github.dawidd6.indicator-clipboard.png)
install(FILES data/icon_42.png DESTINATION share/icons/hicolor/42x42/apps RENAME com.github.dawidd6.indicator-clipboard.png)
install(FILES data/icon_48.png DESTINATION share/icons/hicolor/48x48/apps RENAME com.github.dawidd6.indicator-clipboard.png)
install(FILES data/icon_64.png DESTINATION share/icons/hicolor/64x64/apps RENAME com.github.dawidd6.indicator-clipboard.png)
