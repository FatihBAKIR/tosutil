//
// Created by fatih on 12/15/18.
//

#pragma once

#include "util.hpp"

namespace tut
{
    std::shared_ptr<const tut::arch_t>
    load_arch(const std::string& name);

    std::shared_ptr<const tut::target_t>
    load_target(const std::string& name);

    std::shared_ptr<const tut::processor_t>
    load_proc(const std::string& name);

	std::shared_ptr<const tut::programmer_t>
	load_programmer(const std::string& name);	

	std::shared_ptr<const tut::board_t>
	load_board(const std::string& name);
}