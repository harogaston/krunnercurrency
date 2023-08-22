add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_org.kde.krunnercurrency\")

add_library(krunnercurrency MODULE)

target_sources(krunnercurrency PRIVATE
    krunnercurrency.cpp
)

kcoreaddons_desktop_to_json(krunnercurrency plasma-runner-krunnercurrency.desktop)
find_package(Qt5Network REQUIRED)
target_link_libraries(krunnercurrency KF5::Runner KF5::I18n Qt5::Network Qt5::Widgets)

install(TARGETS krunnercurrency DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/krunner)

install(FILES plasma-runner-krunnercurrency.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})