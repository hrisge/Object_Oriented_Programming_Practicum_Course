#pragma once
#include <string>

class Computer{
    double cpuFrequency;
    std::string gpu;
    unsigned power;
    unsigned ram;
public:
    Computer() = default;
    Computer(double cpuFrequency, const std::string& gpu, unsigned power, unsigned ram);
    double getCpuFrequency() const;
    const std::string &getGpu() const;
    unsigned getPower() const;
    unsigned getRam() const;
    void setCpuFrequency(double cpuFrequency);
    void setGpu(const std::string &gpu);
    void setPower(unsigned power);
    void setRam(unsigned ram);
    virtual void printType() const = 0;
    virtual std::string peripherals() const = 0;
    virtual ~Computer() = default;
};