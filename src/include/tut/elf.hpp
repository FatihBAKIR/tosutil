#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <memory>
#include <filesystem>

namespace tut
{
	struct elf;

	enum class elf_machine
	{
		ARM = 40,
		AVR = 83
	};

	inline std::string to_string(elf_machine em)
	{
		switch (em)
		{
		case tut::elf_machine::ARM: return "ARM";
		case tut::elf_machine::AVR: return "AVR";
		default: return "Unknown";
		}
	}

	struct elf_deleter {
		void operator()(elf*);
	};

	using elf_ptr = std::unique_ptr<elf, elf_deleter>;

	elf_ptr load_elf(const std::string& path);

	inline elf_ptr load_elf(const std::filesystem::path& p) {
		return load_elf(p.string());
	}

	inline elf_ptr load_elf(const boost::filesystem::path& p) {
		return load_elf(p.string());
	}

	elf_machine get_machine(const elf& e);
	inline auto get_machine(const elf_ptr& e) { return get_machine(*e);  }
}