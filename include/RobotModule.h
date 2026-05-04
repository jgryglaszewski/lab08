#ifndef ROBOT_MODULE_H
#define ROBOT_MODULE_H

#include <string>

class RobotModule {
public:
    RobotModule(std::string id, std::string name);

    std::string getName() const;
    void start();
    void stop();
    virtual double current() const = 0;
    virtual std::string type() const = 0;
    virtual void tick() = 0;
    virtual std::string diagnostic() const = 0;
    virtual void reset() = 0;
    std::string summary() const;
    int operator() const;

protected:
    bool isActive;

private:
    const std::string id;
    const std::string name;
};

#endif