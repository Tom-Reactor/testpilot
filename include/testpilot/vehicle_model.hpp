#pragma once

#include <chrono>
#include <cmath>

namespace zm::testpilot {

using Duration = std::chrono::nanoseconds;
double to_seconds(Duration duration) {
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

struct BicycleModelState {
    double x = 0.;
    double y = 0.;
    double yaw = 0.;
    // Fields below technically aren't "state" but it's useful to see what their last known values were
    double yaw_rate = 0.;
    double wheel_angle = 0.;
    double speed = 0.;
};

struct BicycleModelInput {
    double set_speed = 0.;
    double wheel_angle_rad = 0.;
};

struct BicycleModelParams {
    double l_r = 0.;
};

class Vehicle {
public:
    BicycleModelState state;
    BicycleModelInput input;
    BicycleModelParams params;

    void tick(Duration dt) {
        // Integrate.
        // We take
        // https://www.researchgate.net/publication/308851864_Kinematic_and_dynamic
        // _vehicle_models_for_autonomous_driving_control_design
        // as a starting point, but realizing that we can simplify the math when
        // we set l_r equal to the length of the vehicle. This causes the slip
        // angle beta to be equal to the wheel angle delta, and there's no
        // change in behavior.
        const auto dt_s = to_seconds(dt);
        const auto v = input.set_speed;
        const auto delta = input.wheel_angle_rad;
        const auto yaw = state.yaw;
        const auto l_r = params.l_r;

        state.x += v * std::cos(yaw + delta) * dt_s;
        state.y += v * std::sin(yaw + delta) * dt_s;
        
        const auto yaw_rate = v / l_r * std::sin(delta);
        state.yaw += yaw_rate * dt_s;

        state.yaw_rate = yaw_rate;
        state.wheel_angle = delta;
        state.speed = v;
    }
};

}  // namespace zm::testpilot