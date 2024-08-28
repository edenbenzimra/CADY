cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ComponentAnalyzer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2 # Or the latest version
)
FetchContent_MakeAvailable(nlohmann_json)

# Add the source files from the sources folder
file(GLOB SOURCES "sources/*.cpp")
file(GLOB HEADERS "include/*.h")

# Create the executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link nlohmann_json to your executable
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Organize files in Visual Studio Solution Explorer
source_group(TREE ${CMAKE_SOURCE_DIR}/include PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE ${CMAKE_SOURCE_DIR}/sources PREFIX "Source Files" FILES ${SOURCES})

# Set the project as the startup project in Visual Studio
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ComponentAnalyzer)

# Optionally, set the output directories (you can adjust as needed)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Optionally, include debugging symbols in debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
