#pragma once
#include <nlohmann/json.hpp>
#include "languageserver.h"

class Completion {
public:
	Completion(); // Constructor
	lsp::data::completion_list as_completion_list();
	

private:
	void load_json(const char *);
	lsp::data::completion_list m_completions;
	lsp::data::markup_content create_hint(nlohmann::json& command);
	lsp::data::completion_item create_suggestion(nlohmann::json& command);
};