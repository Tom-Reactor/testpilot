#include "testpilot/testpilot.hpp"
#include "testpilot/simulator.hpp"

#include <iostream>
#include <cstdio>

using namespace zm::testpilot;

static const char GT_MAP_PATH[] = "/tmp/dummy_path_to_gtmap.map";

int main() {
    using namespace std::literals::chrono_literals;

    // Create a simulator
    Vehicle v;
    v.params = BicycleModelParams{
        .l_r = 5.,
    };

    Simulator sim;
    const auto tp_entity = sim.add_vehicle(v);

    // Create a stack
    Testpilot stack;
    stack.load_map(GT_MAP_PATH);
    stack.update_destination(100., 50.);

    // Simulate
    TestpilotOutput tp_output;
    for (int i = 0; i < 100; ++i) {
        
        sim.update_vehicle_input(tp_entity, BicycleModelInput{.set_speed = tp_output.set_speed, .wheel_angle_rad = tp_output.wheel_angle });
        sim.tick(50ms);
        const auto vehicle_state = sim.get_vehicle_state(tp_entity);
        stack.update_position(vehicle_state.x, vehicle_state.y);

        if (i == 10) {
            stack.activate();
        }
        if (i == 90) {
            stack.deactivate();
        }
        stack.tick();
        tp_output = stack.get_output();
        printf("TP [%s] commanded wheel angle: %.2f, set speed: %.2f\n", (tp_output.active ? " active " : "inactive"),  tp_output.wheel_angle, tp_output.set_speed);
        printf("Pos: (%.2f, %.2f), Speed: %.2f, Yaw: %.2f\n", vehicle_state.x, vehicle_state.y, vehicle_state.speed, vehicle_state.yaw);
    }

    return 0;
}