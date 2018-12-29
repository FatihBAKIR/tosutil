#include <iostream>
#include <tut/util.hpp>
#include <tut/loaders.hpp>
#include <map>
#include <boost/process.hpp>

namespace bp = boost::process;
namespace fs = boost::filesystem;

int main(int argc, char** argv) {

    if(argc == 1){
        std::cout << "Not enough arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    auto p = fs::canonical(fs::system_complete(argv[0]).parent_path());

    auto programs = [&]{
        std::map<std::string, fs::path> res;
        res.emplace("info", bp::search_path("info", { p, p/"src/src/" }));
        res.emplace("analyze", bp::search_path("analyze", { p, p/"src/src/" }));
        res.emplace("program", bp::search_path("program", { p, p/"src/src/" }));
        res.emplace("prepare", bp::search_path("prepare", { p, p/"src/src/" }));
        return res;
    }();

    std::vector<std::string> args{ argv + 1, argv + argc };

    auto prog =  programs[args[0]];

    args.erase(args.begin());

    bp::child c(prog, bp::args(args));
    c.wait();
}