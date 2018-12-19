//
// Created by fatih on 12/19/18.
//

#pragma once

#include <stdexcept>
#include <boost/filesystem.hpp>

namespace tut
{
    class file_not_found : public std::runtime_error
    {
    public:
        explicit file_not_found(const boost::filesystem::path& p) :
            runtime_error("File not found: " + p.string()) {}
    };
}