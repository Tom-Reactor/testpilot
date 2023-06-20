# Create libtestpilot
add_library(libsimulator SHARED 
    simulator.cpp
)
add_library(simulator::library ALIAS libsimulator)

target_include_directories(libsimulator
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
