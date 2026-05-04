#include "RadioModule.h"

RadioModule::RadioModule(string id, string name, double ch) : RobotModule(id, name), channel(ch), packets(0) {}

double RobotModule::operator()() {
    return this->current()
}

double RadioModule::current() {
    if(isActive){
        return 30 + packets;
    } else {
        return 1;
    }
}

void RadioModule::tick() {
    if(isActive) {
        packets += channel;
    }
}

void RadioModule::reset() {
    packets = 0;
    isActive = false;
}
string diagnostic(){
        string out("");
    if(isActive){
        out.append("ACTIVE ");
    } else {
        out.append("OFF ");
    }

    out.append("channel=");
    out.append(to_string(load));
    out.append(" packets=");
    out.append(to_string(heat));
    return out;
}
string RadioModule::type() {
    return "RadioModule";
}