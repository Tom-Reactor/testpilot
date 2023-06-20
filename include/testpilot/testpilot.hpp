#pragma once

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

struct Vector2 {
    double x = 0.;
    double y = 0.;
};

struct TestpilotState {
    bool controller_active = false;
    Vector2 destination;
    double set_speed = 0.;
    double wheel_angle = 0.;
    Vector2 position;
    double actual_speed = 0.;
};

struct TestpilotOutput {
    double set_speed = 0.;
    double wheel_angle = 0.;
    bool active = false;
};

/**
 * This class contains the Testpilot "AV" stack.
 *
 * Header-only for now to keep things fast and simple. Some refactoring may be in order
 * if / when we grow this code base.
 */
class Testpilot {
public:
    TestpilotState state;

    void load_map(const fs::path& path) {
        std::cout << "Placeholder. Would load map from " << path << "." << std::endl;
    }

    void update_destination(double x, double y) {
        state.destination = {x, y};
    }

    void activate() {
        state.controller_active = true;
    }

    void deactivate() {
        state.controller_active = false;
    }

    void update_position(double x, double y) {
        state.position = {x, y};
    }

    void tick() {
        if (state.controller_active) {
            state.set_speed = 2.;
            state.wheel_angle = .4;
        } else {
            state.set_speed = 0.;
            state.wheel_angle = 0.;
        }
    }

    TestpilotOutput get_output() const {
        return {
            .set_speed = state.set_speed,
            .wheel_angle = state.wheel_angle,
            .active = state.controller_active,
        };
    }
};