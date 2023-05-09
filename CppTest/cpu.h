#pragma once

typedef struct APP_INFOS {
    CString DisplayName;
    CString FullPath;
    __int64 last_time_;
    __int64 last_system_time_;
    int CPU_Usage;
}App_Infos;

namespace CCPU {
    __int64 file_time_2_utc(const FILETIME* ftime);
    int get_processor_number();
    int get_cpu_usage(int pid);
    int get_cpu_usage(int pid, __int64& last_time_, __int64& last_system_time_);
    int testCPUUsage();

    void getCpuUsage();
}