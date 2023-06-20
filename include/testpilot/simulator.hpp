#pragma once

#include "testpilot/vehicle_model.hpp"

#include <cassert>
#include <vector>

namespace zm::testpilot {

using EntityId = uint64_t;

class Simulator {
public:
    Duration time;
    std::vector<Vehicle> vehicles;

    void tick(Duration dt) {
        for (auto &vehicle : vehicles) {
            vehicle.tick(dt);
        }
        time += dt;
    }

    EntityId add_vehicle(const Vehicle& vehicle) {
        const auto new_entity_id = vehicles.size();
        vehicles.push_back(vehicle);
        return new_entity_id;
    }

    void update_vehicle_input(EntityId id, const BicycleModelInput& input) {
        const auto idx = id;
        if (idx <= vehicles.size()) {
            vehicles[idx].input = input;
        } else {
            assert(false && "Invalid entity");
        }
    }

    BicycleModelState get_vehicle_state(EntityId id) {
        const auto idx = id;
        if (idx <= vehicles.size()) {
            return vehicles[idx].state;
        } else {
            assert(false && "Invalid entity");
        }
    }
};

} // namespace zm::testpilot