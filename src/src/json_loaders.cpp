//
// Created by fatih on 12/15/18.
//

#include <tut/loaders.hpp>
#include <map>
#include <nlohmann/json.hpp>
#include <fstream>

namespace {
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
}
