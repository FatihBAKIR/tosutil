//
// Created by fatih on 12/14/18.
//

#pragma once

#include <string>
#include <memory>

namespace tut
{
struct arch_t
{
    std::string name;
};

struct target_t
{
    std::shared_ptr<const arch_t> arch;
    std::string name;
};

struct processor_t
{
    std::shared_ptr<const target_t> target;
    std::string name;
    std::string vendor;
    std::string family;
};

struct toolchain_t
{
    std::shared_ptr<const arch_t> arch;
    std::string name;
};
}