#pragma once

#include <string>
#include <string_view>
#include <unordered_set>
#include <unordered_map>
#include <functional>

#include "../util/uri.h"

namespace ls
{
    class variable
    {
        std::unordered_set<x39::uri> m_assigned;
        std::unordered_set<x39::uri> m_used;
        std::string m_variable_name;
    public:
        variable(std::string variable_name) :
            m_variable_name(variable_name)
        {

        }
        std::string_view variable_name() const {
            return m_variable_name;
        }
        void set_assigned(x39::uri uri)
        {
            m_assigned.insert(uri);
        }
        void clear_assigned(x39::uri uri)
        {
            m_assigned.erase(uri);
        }
        void set_used(x39::uri uri)
        {
            m_used.insert(uri);
        }
        void clear_used(x39::uri uri)
        {
            m_used.erase(uri);
        }
        bool is_assigned() const
        {
            return !m_assigned.empty();
        }
        bool is_used() const
        {
            return !m_used.empty();
        }
    };
}
template<>
struct std::hash<ls::variable>
{
    std::size_t operator()(ls::variable const& var) const noexcept
    {
        std::size_t h1 = std::hash<std::string_view>{}(var.variable_name());
        return h1;
    }
};