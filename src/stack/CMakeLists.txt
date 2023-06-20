# Create libtestpilot
add_library(libtestpilot SHARED 
    testpilot.cpp
)
add_library(testpilot::library ALIAS libtestpilot)

target_include_directories(libtestpilot
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
