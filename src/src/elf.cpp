#include <tut/elf.hpp>
#include <ELFIO/elfio.hpp>

namespace tut
{
	struct elf
	{
		ELFIO::elfio e;
	};

	elf_ptr load_elf(const std::string & path)
	{
		auto res = elf_ptr(new elf);
		if (!res->e.load(path))
		{
			throw std::runtime_error("file not found: " + path);
		}
		return res;
	}

	elf_machine get_machine(const elf& e)
	{
		return elf_machine(e.e.get_machine());
	}

	void elf_deleter::operator()(elf *e)
	{
		delete e;
	}
}