#include "MotorModule.h"

MotorModule::MotorModule(string id, string name, double l) : RobotModule(id, name), heat(0), load(l) {}

double operator()(){
    return this->current();
}

double current(){
    if(isActive)
        return load*120 + heat*10;
    else
        return 0;
}

void tick(){
    if(isActive){
        heat += 2;
    }
}

void reset(){
    stop();
    heat = 0;
}

string diagnostic() {
    string out("");
    if(isActive){
        out.append("ACTIVE ");
    } else {
        out.append("STOPPED ");
    }

    out.append("load=");
    out.append(to_string(load));
    out.append(" heat=");
    out.append(to_string(heat));
    return out;
}