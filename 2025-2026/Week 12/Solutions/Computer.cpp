#include "Computer.hpp"

Computer::Computer(double cpuFrequency, const std::string &gpu, unsigned power,
                   unsigned ram)
    : cpuFrequency(cpuFrequency), gpu(gpu), power(power), ram(ram) {}
double Computer::getCpuFrequency() const { return cpuFrequency; }
const std::string &Computer::getGpu() const { return gpu; }
unsigned Computer::getPower() const { return power; }
unsigned Computer::getRam() const { return ram; }
void Computer::setCpuFrequency(double cpuFrequency) {
  if (cpuFrequency >= 0) {
    this->cpuFrequency = cpuFrequency;
  }
}
void Computer::setGpu(const std::string &gpu) { this->gpu = gpu; }
void Computer::setPower(unsigned power) { this->power = power; }
void Computer::setRam(unsigned ram) { ram = ram; }
