#include <vector>
#include "StartupSequence.h"
#include "RobotModule.h"

StartupSequence::StartupSequence(std::vector<RobotModule*> v) : sequence(v) {}

const RobotModule* StartupSequence::operator[](std::size_t i) const{
    return i<sequence.size() ? sequence[i] : nullptr;
}

void StartupSequence::startAll() const{
    for(RobotModule* p : sequence){
        p->start();
    }
}

void StartupSequence::resetAll() const{
    for(RobotModule* p : sequence){
        p->reset();
    }
}

void StartupSequence::stopAll() const{
    for(RobotModule* p : sequence){
        p->stop();
    }
}

std::size_t StartupSequence::size() const { return sequence.size(); }