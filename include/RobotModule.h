#ifndef ROBOT_MODULE_H
#define ROBOT_MODULE_H

#include <iostream>
#include <string>
#include <iomanip>
// std::cout << std::setprecision(0) << std::fixed;

class RobotModule {
public:
    RobotModule(std::string id, std::string name);
    virtual ~RobotModule() = default;

    std::string getName() const;
    void start();
    void stop();
    virtual double current() const = 0;
    virtual std::string type() const = 0;
    virtual void tick() = 0;
    virtual std::string diagnostic() const = 0;
    virtual void reset() = 0;
    std::string summary() const;
    int operator()() const;



private:
    const std::string id;
    const std::string name;

protected:
    bool isActive;
};

#endif