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
#include <cpprest/http_client.h>

#include <tut/install/install.hpp>
#include <tut/sys_id.hpp>


namespace bp = boost::process;
namespace fs = boost::filesystem;

using namespace web::http;
using namespace web::http::client;

std::string get_distro() {
    std::string ret;
    bp::ipstream pipe_stream;

    std::vector<std::string> args;

    auto cat_executable = bp::search_path("cat", {"/bin"});

    args.emplace_back("/etc/os-release");
    bp::child c(cat_executable, args, bp::std_out > pipe_stream);
    std::getline(pipe_stream, ret);

    c.wait();

    return ret.substr(6, ret.size() - 7);

}


void get_file(const std::string &link, const std::string &dest, const std::string &name) {

    fs::path wget_root = "/usr";
    std::vector<std::string> args;

    auto wget_executable = bp::search_path("wget", {wget_root / "bin"});

    if (wget_executable.empty()) {
        throw std::runtime_error("Could not find wget executable");
    }

    args.emplace_back("-nc"); // If file exists do not download

    args.emplace_back(link);
    args.emplace_back("-O");
    args.emplace_back(dest + name);


    bp::ipstream pipe_stream;
    bp::child c(wget_executable, args, bp::std_out > pipe_stream);

    std::string line;
    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cout << line << std::endl;

    c.wait();


}


/*
 * c:/xutils
 * /opt/xutils
 *
 *
 */

void extract(const std::string &filename, const std::string &dest) { // nereye acilacagini al
    std::string exe;
    std::vector<std::string> args;

    fs::path l7z_root = "/usr";
    auto l7z_executable = bp::search_path("7z", {l7z_root / "bin"});

    if (l7z_executable.empty()) {
        throw std::runtime_error("Could not find l7z executable");
    }
    args.emplace_back("x"); // For extract
    args.emplace_back("-y"); // assume Yes on all queries. eg: override files
    args.emplace_back(filename);
    args.emplace_back("-o " + dest);
    bp::ipstream pipe_stream;
    bp::child c(l7z_executable, args, bp::std_out > pipe_stream);

    std::string line;
    while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
        std::cout << line << std::endl;

    c.wait();


}


int main(int argc, char **argv) try {
    if (argc < 2) {
        std::cerr << "usage: prepare board/proc board\n";
        return 1;
    }

    if (getuid() != 0) {
        std::cout << "Please run this program with sudo" << std::endl;
        //exit(EXIT_FAILURE);
    }


    std::string arg1(argv[1]);
    std::string arg2(argv[2]);
    if (arg1 == "board") {
        if (get_distro() == "Ubuntu") {
            if (arg2 == "nucleo/f103rb") {
                fs::path openocd_root = "/usr";
                auto openocd_executable = bp::search_path("openocd", {openocd_root / "bin"});

                if (!openocd_executable.empty()) {
                    //TODO: request new version if avaiable
                    throw std::runtime_error("openocd already installed!");
                }

                // Install openocd on ubuntu
//                    fs::path root = "/usr";
//                    std::vector<std::string> args;
//
//                    auto apt_executable = bp::search_path("apt-get", {root / "bin"});
//
//                    args.emplace_back("install");
//                    args.emplace_back("-y");
//                    args.emplace_back("openocd");
//
//                bp::ipstream pipe_stream;
//                bp::child c(apt_executable, args, bp::std_out > pipe_stream);
//
//                std::string line;
//                while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
//                    std::cout << line << std::endl;
//
//                c.wait();

                // End of Install openocd on ubuntu



                // Install avr-gcc on ubuntu
                http_client client(U("https://api.bakir.io/"));
                uri_builder builder(U("get-url/x86-linux/avr-gcc"));

                http_response response = client.request(methods::GET, builder.to_string()).get();

                if (response.status_code() == status_codes::OK) {
                    auto body = response.extract_string();
                    std::cout << body.get().c_str() << std::endl;
                }



                //std::string openocdLink = "https://github.com/ntfreak/openocd/archive/v0.10.0.tar.gz";
                //getFile(openocdLink, "./openocd/", "openocd-v0.10.0.tar.gz");

            }
        } else if (get_distro() == "Fedora") {
            // Install openocd on fedora
            // End of Install openocd on fedora
        } else {
            std::cout << "Unsupported distro" << std::endl;
        }


    } else if (arg1 == "proc") {
        if (arg2 == "esp8266") {
            std::cout << arg2 << std::endl;
        } else if (arg2 == "STM32/F103RB") {
            std::cout << arg2 << std::endl;
        } else if (arg2 == "cortex-m3") {
            std::cout << arg2 << std::endl;
        }
    } else {
        std::cerr << "Please use board or proc" << std::endl;
    }

    //extract("OpenOCD-20180728.zip");



    //getFile(openocdLink);

    std::cout << "hede" << std::endl;

}

catch (std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
}