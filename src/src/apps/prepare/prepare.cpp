//
// Created by oguz on 28.12.2018.
//

#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <boost/asio.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/process.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/system/error_code.hpp>

#include "prepare.hpp"

#if defined(BOOST_POSIX_API)
#define SHELL_COMMAND_PREFIX "-c"
#elif defined(BOOST_WINDOWS_API)
#define SHELL_COMMAND_PREFIX "/c"
#endif

namespace bp = boost::process;
namespace fs = boost::filesystem;


void getFile(const std::string& link) {


#if defined(BOOST_POSIX_API) //TODO: Test unix env
    fs::path wget_root = "/usr";
    std::vector<std::string> args;

    auto wget_executable = bp::search_path("wget", { wget_root / "bin" });

    if (wget_executable.empty())
    {
        throw std::runtime_error("Could not find wget executable");
    }

    args.emplace_back(link);

    bp::ipstream pipe_stream;
    bp::child c(wget_executable, args, bp::std_out > pipe_stream);

    std::string line;
    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cout << line << std::endl;

    c.wait();



#elif defined(BOOST_WINDOWS_API) //TODO: This code won't work :D

#endif

}



void extract(const std::string& filename){
    std::string exe;
    std::vector<std::string> args;

#if defined(BOOST_POSIX_API) //TODO: Test unix env
    fs::path l7z_root = "/usr";
    auto l7z_executable = bp::search_path("7z", { l7z_root / "bin" });

    if (l7z_executable.empty())
    {
        throw std::runtime_error("Could not find l7z executable");
    }
    args.emplace_back("x"); // For extract
    args.emplace_back("-y"); // assume Yes on all queries. eg: override files
    args.emplace_back(filename);
#elif defined(BOOST_WINDOWS_API) //TODO: This code won't work :D
    char sysdir[MAX_PATH];
    UINT size = ::GetSystemDirectoryA(sysdir, sizeof(sysdir));
    if (!size)
        boost::throw_exception(boost::system::system_error(boost::system::error_code(::GetLastError(), boost::system::get_system_category()), "boost::process::launch_shell: GetWindowsDirectory failed"));
    BOOST_ASSERT(size < MAX_PATH);

    exe = std::string(sysdir) + (sysdir[size - 1] != '\\' ? "\\cmd.exe" : "cmd.exe");
    args.push_back("cmd");
    args.push_back("/c");
    args.push_back(command);
#endif

    bp::ipstream pipe_stream;
    bp::child c(l7z_executable, args, bp::std_out > pipe_stream);

    std::string line;
    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cout << line << std::endl;

    c.wait();
}


int main(int argc, char** argv) try
{
    if (argc < 2)
    {
        std::cerr << "usage: prepare board\n";
        return 1;
    }

    //extract("OpenOCD-20180728.zip");

    //std::string openocdLink = "https://github.com/ntfreak/openocd/archive/v0.10.0.tar.gz";

    //getFile(openocdLink);

    std::cout << "hede" << std::endl;

}

catch (std::exception& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}