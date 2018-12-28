//
// Created by fatih on 12/15/18.
//

#include <tut/loaders.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include <fstream>
#include <boost/filesystem.hpp>
#include <tut/errors.hpp>
#include <iostream>

namespace fs = boost::filesystem;

namespace {
	template <class T> struct identity_t { using type = T; };

    tut::arch_t parse_arch(const nlohmann::json& j)
    {
        return { j["alias"] };
    }

    tut::target_t parse_target(const nlohmann::json& j)
    {
        return { tut::load_arch(j["arch"]), j["alias"] };
    }

    tut::processor_t parse_processor(const nlohmann::json& j)
    {
        return {
                tut::load_target(j["target"]),
                j["alias"],
                j["vendor"],
                j["family"]
        };
    }

	tut::programmer_t parse_programmer(const nlohmann::json& j)
	{
		tut::programmer_t res;

		for (auto& a : j["arches"])
		{
			res.arches.push_back(tut::load_arch(a));
		}

		res.alias = j["alias"];

		return res;
	}

	tut::programmer_args_t parse_args(const nlohmann::json& j)
    {
        tut::programmer_args_t res;
        res.programmer = tut::load_programmer(j["name"]);
        res.args = j;
        res.args.erase("name");
        return res;
    }

	tut::board_t parse_board(const nlohmann::json& j)
	{
		tut::board_t res;
		res.proc = tut::load_proc(j["processor"]);
		for (const nlohmann::json& programmer : j["programmers"])
		{
		    if (programmer.is_string())
            {
                res.programmers.push_back({tut::load_programmer(programmer), {}});
            } else {
                res.programmers.push_back(parse_args(programmer));
		    }
		}
		res.alias = j["alias"];
		return res;
	}

	template <class... ArgTs>
	auto parse(identity_t<tut::arch_t>, ArgTs&&... args) { return parse_arch(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(identity_t<tut::target_t>, ArgTs&&... args) { return parse_target(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(identity_t<tut::processor_t>, ArgTs&&... args) { return parse_processor(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(identity_t<tut::programmer_t>, ArgTs&&... args) { return parse_programmer(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(identity_t<tut::board_t>, ArgTs&&... args) { return parse_board(std::forward<ArgTs>(args)...); }
}

namespace tut
{
	template <class ObjT>
	struct shared_loader
	{
		shared_loader(const std::string& base) : m_base(base) {}

		std::shared_ptr<const ObjT> operator()(const std::string& name)
		{
			auto ptr = m_cache.find(name);
			if (m_cache.find(name) != m_cache.end())
			{
				if (auto res = ptr->second.lock(); res)
				{
					return res;
				}
				m_cache.erase(ptr);
			}

			nlohmann::json j;

			auto p = m_base + "/" + name + ".json";

			if (!fs::exists(p))
            {
			    throw tut::file_not_found(p);
            }

			std::ifstream file(p);
			file >> j;
			auto res = std::make_shared<ObjT>(parse(identity_t<ObjT>{}, j));
			m_cache.emplace(name, res);
			return res;
		}

	private:
		std::string m_base;
		std::map < std::string, std::weak_ptr<const ObjT>> m_cache;
	};


	fs::path full_path( "../../data" );


	const std::string data_base = full_path.string();

	std::shared_ptr<const tut::arch_t>
    load_arch(const std::string& name)
    {
		static shared_loader<tut::arch_t> cache{data_base + "/archs"};
		return cache(name);
    }

    std::shared_ptr<const tut::target_t>
    load_target(const std::string& name)
    {
		static shared_loader<tut::target_t> cache{data_base + "/targets"};
		return cache(name);
    }

    std::shared_ptr<const tut::processor_t>
    load_proc(const std::string& name)
    {
		static shared_loader<tut::processor_t> cache{data_base + "/processors"};
		return cache(name);
    }

	std::shared_ptr<const tut::programmer_t>
	load_programmer(const std::string& name)
	{
		static shared_loader<tut::programmer_t> cache{data_base + "/programmers"};
		return cache(name);
	}

	std::shared_ptr<const tut::board_t>
	load_board(const std::string& name)
	{
		static shared_loader<tut::board_t> cache{data_base + "/boards"};
		return cache(name);
	}
}
