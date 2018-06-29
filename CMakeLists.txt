cmake_minimum_required(VERSION 3.5)

project(clip)

set(PNAME com.github.dawidd6.${PROJECT_NAME})

find_package(PkgConfig REQUIRED)

pkg_check_modules(LIBNOTIFY REQUIRED libnotify)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(INDI REQUIRED appindicator3-0.1)


include_directories(${LIBNOTIFY_INCLUDE_DIRS}
                    ${GTK_INCLUDE_DIRS}
                    ${INDI_INCLUDE_DIRS})

link_directories(${LIBNOTIFY_LIBRARY_DIRS}
                 ${GTK_LIBRARY_DIRS}
                 ${INDI_LIBRARY_DIRS})

add_definitions(${LIBNOTIFY_CFLAGS_OTHER}
                ${GTK_CFLAGS_OTHER}
                ${INDI_CFLAGS_OTHER})

add_executable(${PROJECT_NAME}
               main.c)

target_link_libraries(${PROJECT_NAME}
                      ${LIBNOTIFY_LIBRARIES}
                      ${GTK_LIBRARIES}
                      ${INDI_LIBRARIES})
