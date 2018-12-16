//
// Created by fatih on 12/15/18.
//

#include <tut/loaders.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include <fstream>

namespace {
	template <class T> struct id_t { using type = T; };

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

	tut::board_t parse_board(const nlohmann::json& j)
	{
		tut::board_t res;
		res.proc = tut::load_proc(j["processor"]);
		for (auto& programmer : j["programmers"])
		{
			res.programmers.push_back(tut::load_programmer(programmer));
		}
		res.alias = j["alias"];
		return res;
	}

	template <class... ArgTs>
	auto parse(id_t<tut::arch_t>, ArgTs&&... args) { return parse_arch(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(id_t<tut::target_t>, ArgTs&&... args) { return parse_target(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(id_t<tut::processor_t>, ArgTs&&... args) { return parse_processor(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(id_t<tut::programmer_t>, ArgTs&&... args) { return parse_programmer(std::forward<ArgTs>(args)...); }

	template <class... ArgTs>
	auto parse(id_t<tut::board_t>, ArgTs&&... args) { return parse_board(std::forward<ArgTs>(args)...); }
}

namespace tut
{
    std::map<std::string, std::weak_ptr<const tut::target_t>> targets;
    std::map<std::string, std::weak_ptr<const tut::arch_t>> archs;
    std::map<std::string, std::weak_ptr<const tut::processor_t>> procs;

    std::shared_ptr<const tut::arch_t>
    load_arch(const std::string& name)
    {
        auto ptr = archs.find(name);
        if (archs.find(name) != archs.end())
        {
            if (auto res = ptr->second.lock(); res)
            {
                return res;
            }
            archs.erase(ptr);
        }

        nlohmann::json j;
        std::ifstream file("C:/Users/mfati/Documents/tosutil/data/archs/" + name + ".json");
        file >> j;
        auto res = std::make_shared<tut::arch_t>(parse_arch(j));
        archs.emplace(name, res);
        return res;
    }

    std::shared_ptr<const tut::target_t>
    load_target(const std::string& name)
    {
        auto ptr = targets.find(name);
        if (targets.find(name) != targets.end())
        {
            if (auto res = ptr->second.lock(); res)
            {
                return res;
            }
            targets.erase(ptr);
        }

        nlohmann::json j;
        std::ifstream file("C:/Users/mfati/Documents/tosutil/data/targets/" + name + ".json");
        file >> j;
        auto res = std::make_shared<tut::target_t>(parse_target(j));
        targets.emplace(name, res);
        return res;
    }

    std::shared_ptr<const tut::processor_t>
    load_proc(const std::string& name)
    {
        auto ptr = procs.find(name);
        if (procs.find(name) != procs.end())
        {
            if (auto res = ptr->second.lock(); res)
            {
                return res;
            }
            procs.erase(ptr);
        }

        nlohmann::json j;
        std::ifstream file("C:/Users/mfati/Documents/tosutil/data/processors/" + name + ".json");
        file >> j;
        auto res = std::make_shared<tut::processor_t>(parse_processor(j));
        procs.emplace(name, res);
        return res;
    }

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
			std::ifstream file(m_base + "/" + name + ".json");
			file >> j;
			auto res = std::make_shared<ObjT>(parse(id_t<ObjT>{}, j));
			m_cache.emplace(name, res);
			return res;
		}

	private:
		std::string m_base;
		std::map < std::string, std::weak_ptr<const ObjT>> m_cache;
	};

	shared_loader<tut::programmer_t> programmer_cache{"C:/Users/mfati/Documents/tosutil/data/programmers"};
	std::shared_ptr<const tut::programmer_t> load_programmer(const std::string& name)
	{
		return programmer_cache(name);
	}

	shared_loader<tut::board_t> board_cache{"C:/Users/mfati/Documents/tosutil/data/boards"};
	std::shared_ptr<const tut::board_t> load_board(const std::string& name)
	{
		return board_cache(name);
	}
}
