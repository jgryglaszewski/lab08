#include "RadioModule.h"
using std::to_string;

RadioModule::RadioModule(string id, string name, double ch) : RobotModule(id, name), channel(ch), packets(0) {}

double RadioModule::operator()() const{
    return this->current();
}

double RadioModule::current() const{
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
string RadioModule::diagnostic() const{
        string out("");
    if(isActive){
        out.append("ACTIVE ");
    } else {
        out.append("OFF ");
    }

    out.append("channel=");
    out.append(to_string(channel));
    out.append(" packets=");
    out.append(to_string(packets));
    return out;
}
string RadioModule::type() const{
    return "RadioModule";
}