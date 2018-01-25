#include "NetworkModule.hpp"


std::string NetworkModule::getValue() const
{
	std::string cmd = "netstat -wl -I en0 | grep \"<Link#4>\"  | awk '{print $5}'";
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

NetworkModule::NetworkModule(){}
NetworkModule::~NetworkModule(){}

NetworkModule::NetworkModule(NetworkModule const & src)
{
	*this = src;
	return;
}

NetworkModule & NetworkModule::operator=(NetworkModule const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}
