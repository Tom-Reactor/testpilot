add_executable(testpilot_demo
    main.cpp
)

target_link_libraries( testpilot_demo
    PRIVATE 
        testpilot::library
        simulator::library
)
