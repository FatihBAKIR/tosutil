#include <tut/elf.hpp>
#include <elfio/elfio.hpp>

namespace tut
{
	struct elf
	{
		ELFIO::elfio e;
	};

	elf_ptr load_elf(const std::string & path)
	{
		auto res = elf_ptr(new elf);

		if (!boost::filesystem::exists(path))
		{
			throw std::runtime_error("file not found: " + path);
		}

		if (!res->e.load(path))
		{
			throw std::runtime_error("not an elf file: " + path);
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