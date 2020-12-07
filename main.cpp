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

		SystemCpuUsageReport cpuUsageReport = diagnosticInfo.CpuUsage().GetReport();

		long long totalUsageTime = cpuUsageReport.IdleTime().count() + cpuUsageReport.KernelTime().count() + cpuUsageReport.UserTime().count();
		double percentIdleTime = static_cast<double>(cpuUsageReport.IdleTime().count()) / totalUsageTime;
		double percentKernelTime = static_cast<double>(cpuUsageReport.KernelTime().count()) / totalUsageTime;
		double percentUserTime = static_cast<double>(cpuUsageReport.UserTime().count()) / totalUsageTime;

		std::wcout << "Percent of CPU time that was idle:   " << percentIdleTime << "% \n";
		std::wcout << "Percent of CPU time in kernel mode: " << percentKernelTime << "% \n";
		std::wcout << "Percent of CPU time in user mode:   " << percentUserTime << "% \n";

		SystemMemoryUsageReport memoryUsageReport = diagnosticInfo.MemoryUsage().GetReport();

		// Divide count in bytes by definition of MiB
		const int MiB_Definition = 1048576;
		long long freeMemoryInMiB = memoryUsageReport.AvailableSizeInBytes() / MiB_Definition; 
		long long usedMemoryInMiB = ( memoryUsageReport.TotalPhysicalSizeInBytes() - memoryUsageReport.AvailableSizeInBytes() ) / MiB_Definition;
		long long committedMemoryInMiB = memoryUsageReport.CommittedSizeInBytes() / MiB_Definition;
		long long totalMemoryInMiB = memoryUsageReport.TotalPhysicalSizeInBytes() / MiB_Definition;

		std::wcout << "The available memory was: " << freeMemoryInMiB << " MiB \n";
		std::wcout << "The used memory was:      " << usedMemoryInMiB << " MiB \n";
		std::wcout << "The total committed memory was:    " << committedMemoryInMiB << " MiB \n";
		std::wcout << "The total memory in the system is: " << totalMemoryInMiB << " MiB\n";

		std::wcout << "\n";
		std::wcout << "---\n";
		std::wcout << "\n";

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
