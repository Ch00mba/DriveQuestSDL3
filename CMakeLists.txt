cmake_minimum_required(VERSION 3.21)
project(DriveQuest)

# 1. Include the FetchContent module
include(FetchContent)

# 2. Tell CMake where to download SDL3 from (official GitHub)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        preview-3.1.3 # Grabs a specific stable preview version
)



set(SDLTTF_GL_TEXTENGINE OFF CACHE BOOL "" FORCE)
set(SDLTTF_VULKAN_TEXTENGINE OFF CACHE BOOL "" FORCE)


# 3. Download and make SDL3 available to the project
FetchContent_MakeAvailable(SDL3)

# 4. Include your source subdirectory
add_subdirectory(DriveQuest)