cmake_minimum_required(VERSION 3.16)
project(Xero)

# Standard C++ version for modern game dev
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Fetch Raylib automatically from GitHub
include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 6.0  # Stable version
)

# This prevents Raylib from building its own examples/tests, saving time
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# 2. Add your source files
add_executable(${PROJECT_NAME} src/main.cpp)

# 3. Link libraries
# On Windows/Linux, raylib is sufficient. 
# On macOS, CMake handles the necessary Apple Frameworks (OpenGL, CoreVideo, etc.)
target_link_libraries(${PROJECT_NAME} raylib)

# 4. Optional: Set output directory to root so it can find assets easily
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)