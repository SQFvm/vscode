#pragma once
#include "lspserver.h"
#include "variable_declaration.h"

#include <nlohmann/json.hpp>
#include <string_view>

class Completion {
public:
	// Constructor
	Completion() : m_index(0) { this->load_json("commands.min.json"); }
	/**
	 * Provides autocomplete list.
	 *
	 * \return
	 */
	lsp::data::completion_list as_completion_list() const { return m_completion_live; }
	void compute(std::vector<variable_declaration::sptr> globals, std::string_view view);

private:
	// Contains the current "live" result, as computed by `void compute()`
	lsp::data::completion_list m_completion_live;

	// Contains the list of completion items.
	std::vector<lsp::data::completion_item> m_completion_items;
	uint16_t m_index;

	void load_json(const char*);
	lsp::data::markup_content hint_former(nlohmann::json& command);
	lsp::data::completion_item create_suggestion(nlohmann::json& command);
	lsp::data::completion_item create_suggestion(variable_declaration::sptr& var);
};