#include "SensorModule.h"

SensorModule::SensorModule(std::string id, std::string name, int sensitivity) : RobotModule(id, name), sensitivity(sensitivity);

double SensorModule::current() const {
    if (isActive) {
        return 5 + sensitivity;
    }

    return 1;
}

std::string SensorModule::type() const {
    return "SensorModule";
}
void SensorModule::tick() {
    if (isActive) {
        samples += sensitivity;
    }
}

std::string SensorModule::diagnostic() const {
    return (isActive ? "ACTIVE" : "SLEEP") + "sensitivity=" + std::to_string(sensitivity) + " samples=" + std::to_string(samples);
}

void SensorModule::reset() {
    stop();
    samples = 0;
}