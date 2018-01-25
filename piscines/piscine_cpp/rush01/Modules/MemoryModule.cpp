#include "MemoryModule.hpp"

std::string MemoryModule::getValue(void) const
{
	double percentageMemUsed = (MemoryModule::memUsed() - 0.0) / (MemoryModule::memSizeTotal() - 0.0);

	std::stringstream stream;
	stream << std::setprecision(4) << percentageMemUsed * 100;
	return stream.str();
}

unsigned long long MemoryModule::memSizeTotal(void) const
{
	uint64_t memsize;

	size_t size = sizeof(memsize);
	if (sysctlbyname("hw.memsize", &memsize, &size, 0, 0) < 0)
			throw std::exception();
	return memsize;
}

unsigned long long MemoryModule::memFree(void) const
{
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics64_data_t vm_stats;

	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
		KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
		(host_info64_t)&vm_stats, &count))
	{
		unsigned long long free_memory = static_cast<uint64_t>(vm_stats.free_count) * static_cast<uint64_t>(page_size);
		return free_memory;
	}
	else
	{
		throw std::exception();
		return 0;
	}
}

unsigned long long MemoryModule::memUsed() const
{
	return MemoryModule::memSizeTotal() - MemoryModule::memFree();
}

MemoryModule::MemoryModule(){}
MemoryModule::~MemoryModule(){}

MemoryModule::MemoryModule(MemoryModule const & src)
{
	*this = src;
	return;
}

MemoryModule & MemoryModule::operator=(MemoryModule const & rhs)
{
	static_cast<void>(rhs);
	return *this;
}