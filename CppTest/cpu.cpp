#include <Windows.h>
#include <map>
#include <atlstr.h>
#include "cpu.h"
#include <tlhelp32.h>
namespace CCPU
{
    // 时间转换
    __int64 file_time_2_utc(const FILETIME* ftime)
    {
        LARGE_INTEGER li;

        li.LowPart = ftime->dwLowDateTime;
        li.HighPart = ftime->dwHighDateTime;
        return li.QuadPart;
    }

    // 获得CPU的核数
    int get_processor_number()
    {
        SYSTEM_INFO info;
        GetSystemInfo(&info);
        return (int)info.dwNumberOfProcessors;
    }

    // 获取进程CPU占用
    int get_cpu_usage(int pid)
    {
        //cpu数量
        static int processor_count_ = -1;
        //上一次的时间
        static __int64 last_time_ = 0;
        static __int64 last_system_time_ = 0;

        FILETIME now;
        FILETIME creation_time;
        FILETIME exit_time;
        FILETIME kernel_time;
        FILETIME user_time;
        __int64 system_time;
        __int64 time;
        __int64 system_time_delta;
        __int64 time_delta;

        int cpu = -1;

        if (processor_count_ == -1)
        {
            processor_count_ = get_processor_number();
        }

        GetSystemTimeAsFileTime(&now);

        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
        if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
        {
            return -1;
        }
        system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_;
        time = file_time_2_utc(&now);

        if ((last_system_time_ == 0) || (last_time_ == 0))
        {
            last_system_time_ = system_time;
            last_time_ = time;
            return -1;
        }

        system_time_delta = system_time - last_system_time_;
        time_delta = time - last_time_;

        if (time_delta == 0)
            return -1;

        cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
        last_system_time_ = system_time;
        last_time_ = time;
        return cpu;
    }

    int get_cpu_usage(int pid, __int64& last_time_, __int64& last_system_time_)
    {
        //cpu数量
        static int processor_count_ = -1;
        //上一次的时间
        //static __int64 last_time_ = 0;
        //static __int64 last_system_time_ = 0;

        FILETIME now;
        FILETIME creation_time;
        FILETIME exit_time;
        FILETIME kernel_time;
        FILETIME user_time;
        __int64 system_time;
        __int64 time;
        __int64 system_time_delta;
        __int64 time_delta;

        int cpu = -1;

        if (processor_count_ == -1)
        {
            processor_count_ = get_processor_number();
        }

        GetSystemTimeAsFileTime(&now);

        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
        int err = GetLastError();
        if (!GetProcessTimes(hProcess, &creation_time, &exit_time, &kernel_time, &user_time))
        {
            return -1;
        }
        system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) / processor_count_;
        time = file_time_2_utc(&now);

        if ((last_system_time_ == 0) || (last_time_ == 0))
        {
            last_system_time_ = system_time;
            last_time_ = time;
            return -1;
        }

        system_time_delta = system_time - last_system_time_;
        time_delta = time - last_time_;

        if (time_delta == 0)
            return -1;

        cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
        last_system_time_ = system_time;
        last_time_ = time;
        return cpu;
    }

    std::map<int, App_Infos> ProcessList;
    int testCPUUsage()
    {
        int cpuUsage = 0;
        HANDLE hSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (INVALID_HANDLE_VALUE == hSnap)
            return 0;

        PROCESSENTRY32 processEntry = { sizeof(PROCESSENTRY32) };
        BOOL toContinue = ::Process32First(hSnap, &processEntry);
        HANDLE hProcess = INVALID_HANDLE_VALUE;


        while (toContinue)
        {
            DWORD pid = processEntry.th32ProcessID;
            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid);
            if (hProcess == INVALID_HANDLE_VALUE)
            {
                continue;
            }

            __int64 last_time_ = 0;
            __int64 last_system_time_ = 0;
            TCHAR fullPath[MAX_PATH];
            DWORD len = MAX_PATH;
            get_cpu_usage(pid, last_time_, last_system_time_);
            App_Infos TempInfos;
            TempInfos.last_time_ = last_time_;
            TempInfos.last_system_time_ = last_system_time_;
            if (QueryFullProcessImageName(hProcess, 0, fullPath, &len))
            {
                TempInfos.FullPath = fullPath;
            }
            TempInfos.DisplayName = processEntry.szExeFile;
            ProcessList.insert(std::make_pair(pid, TempInfos));

            CloseHandle(hProcess);
            toContinue = ::Process32Next(hSnap, &processEntry);
        }
        CloseHandle(hSnap);

        Sleep(1000);

        std::map<int, App_Infos>::iterator it;
        for (it = ProcessList.begin(); it != ProcessList.end(); ++it)
        {
            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, it->first);
            if (hProcess == INVALID_HANDLE_VALUE)
            {
                continue;
            }

            int percent = get_cpu_usage(it->first, it->second.last_time_, it->second.last_system_time_);
            it->second.CPU_Usage = percent;
            if ((percent != -1) && (percent != 0))
            {
                cpuUsage += percent;
                wprintf(L"pid=%d,percent=%d,name=%s\n\n", it->first, percent, it->second.DisplayName.GetBuffer(0));
                //fwprintf(fp, L"pid=%d,percent=%d,name=%s\n\n", it->first, percent, it->second.DisplayName.GetBuffer(0));
                it->second.DisplayName.ReleaseBuffer();
            }
        }

        printf("%d%%\n", cpuUsage);
        return 0;
    }

#include <Pdh.h>
#pragma comment(lib, "pdh.lib")
    
    PDH_HQUERY h_query;
    HCOUNTER h_counter = nullptr;
    void CloseCPUQuery()
    {
        PdhRemoveCounter(h_counter);
        PdhCloseQuery(h_query);
    }

    void getCpuUsage() {
        const auto v_count = new PDH_FMT_COUNTERVALUE();
        PDH_STATUS status = PdhOpenQuery(nullptr, 0, &h_query);
        if (ERROR_SUCCESS == status)
        {
            status = PdhAddCounter(h_query, L"\\Processor Information(_Total)\\% Processor Utility", 0, &h_counter);

            if (ERROR_SUCCESS == status)
            {
                int i = 0;
                while (i++ < 3)
                {
                    DWORD dw_counter_type = 0;
                    PdhCollectQueryData(h_query);
                    PdhGetFormattedCounterValue(h_counter, PDH_FMT_DOUBLE, &dw_counter_type, v_count);
                    const double cpu = v_count->doubleValue;
                    printf("CPU:%f\n", cpu);
                    Sleep(500);
                }
            }
        }
        printf("-----------\n");
        CloseCPUQuery();
    }
}