#include <vector>
#include "ModuleBoard.h"
#include "RobotModule.h"

ModuleBoard::~ModuleBoard(){
    for (RobotModule *p : modules){
        delete p;
    }
}

void ModuleBoard::add(RobotModule* r){
    modules.emplace_back(r);
}

std::size_t ModuleBoard::size(){ return modules.size(); }

const RobotModule* ModuleBoard::operator[](size_t i) const{
    return i<modules.size() ? modules[i] : nullptr;
}
RobotModule* ModuleBoard::operator[](size_t i){
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