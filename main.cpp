#include <iostream>
#include <tut/util.hpp>
#include <tut/loaders.hpp>
#include <map>
#include <boost/process.hpp>

auto programs = []{
   std::map<std::string, std::string> res;
    res.emplace("info", "./info.exe");
    res.emplace("analyze", "./analyze.exe");
    res.emplace("program", "./program.exe");
   return res;
}();

int main(int argc, char** argv) {
    namespace bp = boost::process;
    namespace fs = boost::filesystem;

    auto p = fs::canonical(fs::system_complete(argv[0]).parent_path());

    std::vector<std::string> args{ argv + 1, argv + argc };

    auto prog = p / programs[args[0]];

    args.erase(args.begin());

    bp::child c(prog, bp::args(args));
    c.wait();
}