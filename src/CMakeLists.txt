add_definitions(-DTRANSLATION_DOMAIN=\"plasma_runner_org.kde.krunner_currency\")

add_library(krunner_currency MODULE)

target_sources(krunner_currency PRIVATE
    krunnercurrency.h
    krunnercurrency.cpp
)

find_package(Qt5Network REQUIRED)
target_link_libraries(krunner_currency KF5::Runner KF5::I18n Qt5::Network Qt5::Widgets)

install(TARGETS krunner_currency DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/krunner)
