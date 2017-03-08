#
# Copyright (c) 2017 Vladislav Mileshkin
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

add_subdirectory(icons)
add_subdirectory(data)

add_definitions(-DTRANSLATION_DOMAIN=\"kipiplugin_reverseimagesearch\")

set(kipiplugin_reverseimagesearch_PART_SRCS
    plugin_reverseimagesearch.cpp
    reverseimagesearchengine.cpp
)

add_library(kipiplugin_reverseimagesearch MODULE ${kipiplugin_reverseimagesearch_PART_SRCS})

target_link_libraries(kipiplugin_reverseimagesearch
                      Qt5::Network

                      KF5::Kipi
                      KF5::WindowSystem
                      KF5::I18n

                      KF5kipiplugins
)

configure_file(kipiplugin_reverseimagesearch.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/kipiplugin_reverseimagesearch.desktop)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kipiplugin_reverseimagesearch.desktop DESTINATION ${SERVICES_INSTALL_DIR})
install(TARGETS kipiplugin_reverseimagesearch DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES kipiplugin_reverseimagesearchui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/kipi)
