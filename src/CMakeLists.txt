set(CMAKE_AUTORCC 1)

#----------------------------------------------------------
# Source files
#
set(
	SOURCE_FILES
		SearchTask.cpp
		main.cpp
)

#----------------------------------------------------------
# Executable target
#
add_executable(
	KdeContactSearch
		${SOURCE_FILES}
)

#----------------------------------------------------------
# Required link libraries
#
target_link_libraries(
	KdeContactSearch
	${Qt5Widgets_LIBRARIES}
	KF5::AkonadiSearchPIM
	KF5::AkonadiSearchCore
	KF5::AkonadiCore
	KF5::PimCommonAkonadi
	KF5::Contacts
)

