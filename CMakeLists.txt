#----------------------------------------------------------
#
#
#
cmake_minimum_required(VERSION 3.0)

project(KdeContactSearch)

#----------------------------------------------------------
# Source files
#
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

#----------------------------------------------------------
# Depends
#
find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(
    CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH}
)

#----------------------------------------------------------
# require c++14
#
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#----------------------------------------------------------
# Setup KF5
#
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMSetupVersion)
include(FeatureSummary)
include(ECMQueryQmake)

find_package(
	Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
		Core
		Widgets
		DBus
)

find_package(
	KF5 ${KF5_MIN_VERSION} REQUIRED
		CoreAddons
		WidgetsAddons
		DBusAddons
		Notifications
		Config
		WindowSystem
		NewStuff
		Akonadi
		AkonadiSearch
		PimCommonAkonadi
		Contacts
)

#----------------------------------------------------------
# Subdirectories to build
#
add_subdirectory(src)

#----------------------------------------------------------
# Install
#
install(TARGETS KdeContactSearch RUNTIME DESTINATION bin)
