#include "pch.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::System::Diagnostics;

int main()
{
	init_apartment();

	while (true)
	{
		SystemDiagnosticInfo diagnosticInfo = SystemDiagnosticInfo::GetForCurrentSystem();

		TimeSpan cpuIdleTime{ diagnosticInfo.CpuUsage().GetReport().IdleTime() };
		std::wcout << "The idle CPU time was:   " << cpuIdleTime.count() << "\n";

		TimeSpan cpuKernelTime{ diagnosticInfo.CpuUsage().GetReport().KernelTime() };
		std::wcout << "The CPU kernel time was: " << cpuKernelTime.count() << "\n";

		TimeSpan cpuUserTime{ diagnosticInfo.CpuUsage().GetReport().UserTime() };
		std::wcout << "The CPU user time was:   " << cpuUserTime.count() << "\n";

		std::wcout << "The available memory in bytes was: " << diagnosticInfo.MemoryUsage().GetReport().AvailableSizeInBytes() << "\n";
		std::wcout << "The used memory in bytes was:      " << diagnosticInfo.MemoryUsage().GetReport().TotalPhysicalSizeInBytes() - diagnosticInfo.MemoryUsage().GetReport().TotalPhysicalSizeInBytes() << "\n";
		std::wcout << "The total committed memory was:    " << diagnosticInfo.MemoryUsage().GetReport().CommittedSizeInBytes() << "\n";
		std::wcout << "The total memory in the system is: " << diagnosticInfo.MemoryUsage().GetReport().TotalPhysicalSizeInBytes() << "\n";

		std::wcout << "\n";
		std::wcout << "---\n";
		std::wcout << "\n";

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
