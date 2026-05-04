#include "RobotModule"

RobotModule::RobotModule(std::string id, std::string name) : id(id), name(name) {}

std::string RobotModule::getName() const {
    return name;
}

void RobotModule::start() {
    isActive = true;
}

void RobotModule::stop() {
    isActive = false;
}

std::string RobotModule::summary() const {
    return type() + name + "[id=" + id + ", current=" + current() + " mA]" + " -> " + diagnostic();
}

int RobotModule::operator() const {
    return current();
}
