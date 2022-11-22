#include <filesystem>    //c++17
#include <source_location>   //c++20
#include <fstream>
#include <iostream>
#include <string>
#include <atlbase.h>
//using namespace std::filesystem;
namespace fs = std::filesystem;


#include <Windows.h>
void WriteFile_My(std::string message,
    std::string logfile = "test.log",
    const std::source_location location = std::source_location::current())
{
    std::ofstream ofile;
    SYSTEMTIME systime;
    GetLocalTime(&systime);
    char buffer[MAX_PATH] = { 0 };
    sprintf_s(buffer, "[%04d-%02d-%02d %02d:%02d:%02d] ",
        systime.wYear, systime.wMonth, systime.wDay,
        systime.wHour, systime.wMinute, systime.wSecond);
    std::string strbuffer = buffer;
    strbuffer += "[";
    strbuffer += location.file_name();
    strbuffer += "] [";
    strbuffer += std::to_string(location.line());
    strbuffer += ":";
    strbuffer += std::to_string(location.column());
    strbuffer += "] [";
    strbuffer += location.function_name();
    strbuffer += "] ";
    strbuffer += message;
    ofile.open(logfile.c_str(), std::ios::app);
    ofile << strbuffer.c_str() << std::endl;
    ofile.close();
}

int main()
{
    WriteFile_My("this is a log test!");

    USES_CONVERSION;
    auto asFile = fs::path("C:\\DTEN\\DTENOTA\\DTENOTA.exe");
    if (!std::filesystem::exists(asFile))
    {
        std::cout << "not exist file" << std::endl;
        return 0;
    }
    std::cout << "current path: " << std::filesystem::current_path() << std::endl;
    std::cout << "temporary path: " << std::filesystem::temp_directory_path() << std::endl;
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time(asFile);
    std::wstring wstr = asFile.filename();
    std::string str = W2A(wstr.c_str());
    std::cout
        << str.c_str() << '\n'
        << asFile.filename() << '\n'
        << asFile.root_path() << '\n'
        << asFile.extension() << '\n'
        << std::filesystem::hash_value(asFile) << '\n'
        << std::filesystem::file_size(asFile);

    system("pause");
    return 0;
}