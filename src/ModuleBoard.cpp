#include <vector>
#include "ModuleBoard.h"
#include "RobotModule.h"

ModuleBoard::~ModuleBoard(){
    for (RobotModule *p : modules){
        delete p;
    }
}

void ModuleBoard::add(RobotModule* r){
    RobotModule *p;
    switch(r->type()){
        case "SensorModule":
            p = new SensorModule(r->getID(), r->getName(), r->getSpecial());
            break;
        case "MotorModule":
            p = new MotorModule(r->getID(), r->getName(), r->getSpecial());
            break;
        case "RadioModule":
            p = new RadioModule(r->getID(), r->getName(), r->getSpecial());
            break;
    }
    delete r;
    modules.emplace_back(p);
}

std::size_t ModuleBoard::size(){ return modules.size(); }

const ModuleBoard* ModuleBoard::operator[](size_t i) const{
    return i<modules.size() ? modules[i] : nullptr;
}
ModuleBoard* ModuleBoard::operator[](size_t i){
    return i<modules.size() ? modules[i] : nullptr;
}

double ModuleBoard::operator()() const{
    double sum=0.0;
    for(RobotModule* p : modules){
        sum += p->current();
    }
    return sum;
}

void ModuleBoard::tickAll(){
    for(RobotModule* p : modules){
        p->tick();
    }
}