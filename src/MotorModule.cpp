#include "MotorModule.h"

MotorModule::MotorModule(string id, string name, double l) : RobotModule(id, name), heat(0), load(l) {}

double MotorModule::operator()(){
    return this->current();
}

double MotorModule::current(){
    if(isActive)
        return load*120 + heat*10;
    else
        return 0;
}

void MotorModule::tick(){
    if(isActive){
        heat += 2;
    }
}

void MotorModule::reset(){
    isActive = false;
    heat = 0;
}

string MotorModule::diagnostic() {
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

string MotorModule::type(){
    return "MotorModule";
}