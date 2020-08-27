#pragma once
#include <nlohmann/json.hpp>
#include "lspserver.h"

class Completion {
public:
	Completion(); // Constructor
	lsp::data::completion_list as_completion_list();


private:
	lsp::data::completion_list m_completions;
	uint16_t m_index;

	void load_json(const char*);
	lsp::data::markup_content hint_former(nlohmann::json& command);
	lsp::data::completion_item create_suggestion(nlohmann::json& command);
};