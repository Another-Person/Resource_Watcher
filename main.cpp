#include "pch.h"

#include <iostream>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::System::Diagnostics;

int main()
{
    init_apartment();
    SystemDiagnosticInfo diagnosticInfo = SystemDiagnosticInfo::GetForCurrentSystem();

    TimeSpan cpuIdleTime{diagnosticInfo.CpuUsage().GetReport().IdleTime()};
    std::wcout << "The idle CPU time was:   " << cpuIdleTime.count() << "\n";

    TimeSpan cpuKernelTime{diagnosticInfo.CpuUsage().GetReport().KernelTime()};
    std::wcout << "The CPU kernel time was: " << cpuKernelTime.count() << "\n";

    TimeSpan cpuUserTime{diagnosticInfo.CpuUsage().GetReport().UserTime()};
    std::wcout << "The CPU user time was:   " << cpuUserTime.count() << "\n";
}
