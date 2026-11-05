# CMakeList.txt : CMake project for DriveQuest, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (DriveQuest "DriveQuest.cpp" "DriveQuest.h")

# Update target_link_libraries to include SDL3_ttf::SDL3_ttf
target_link_libraries(DriveQuest PRIVATE SDL3::SDL3)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DriveQuest PROPERTY CXX_STANDARD 20)
endif()

# Link SDL3 to the DriveQuest executable
target_link_libraries(DriveQuest PRIVATE SDL3::SDL3)

# TODO: Add tests and install targets if needed.

# Automatically copy required DLLs (like SDL3.dll) next to the executable
add_custom_command(TARGET DriveQuest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t
    "$<TARGET_FILE_DIR:DriveQuest>"
    $<TARGET_RUNTIME_DLLS:DriveQuest>
    COMMAND_EXPAND_LISTS
)

# Automatically copy the assets directory to the build output folder
add_custom_command(TARGET DriveQuest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:DriveQuest>/assets"
)