//
// Created by fatih on 12/14/18.
//

#pragma once

#include <string>
#include <memory>
#include <vector>

namespace tut
{
struct arch_t
{
    std::string alias;
};

struct target_t
{
    std::shared_ptr<const arch_t> arch;
    std::string alias;
    std::string triplet;
};

struct processor_t
{
    std::shared_ptr<const target_t> target;
    std::string alias;
    std::string vendor;
    std::string family;
};

struct toolchain_t
{
    std::vector<std::shared_ptr<const arch_t>> arches;
    std::string alias;
};

struct programmer_t
{
	std::vector<std::shared_ptr<const arch_t>> arches;
	std::string alias;
};

struct board_t
{
	std::shared_ptr<const processor_t> proc;
	std::vector<std::shared_ptr<const programmer_t>> programmers;
	std::string alias;
};
}