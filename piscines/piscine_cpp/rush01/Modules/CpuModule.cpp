#include "CpuModule.hpp"

CpuModule::CpuModule(){}
CpuModule::~CpuModule(){}

CpuModule::CpuModule(CpuModule const & src)
{
	*this = src;
	return;
}

CpuModule & CpuModule::operator=(CpuModule const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}


std::string CpuModule::getValue() const
{
	std::string cmd = "top -l 1 -i 1 | grep \"CPU usage\" | awk '{print $7}' |  rev | cut -c 2- | rev";
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

std::string CpuModule::getModel() const
{
	std::string cmd = "sysctl -a | grep machdep.cpu.brand_string | awk '{out=$2; for(i=3;i<=NF;i++){out=out" "$i}; print out}'";
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

std::string CpuModule::getNbrCore() const
{
	std::string cmd = "sysctl -n hw.ncpu";
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}