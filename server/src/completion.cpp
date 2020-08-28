#include "completion.h"
#include <fstream>
#include <string>
#include <filesystem>

Completion::Completion() {
	m_index = 0;
	this->load_json("commands.min.json");
}

/**
 * Loads our json file(s) based on which engine we're running.
 * Will parse to completion_item[]
 *
 */
void Completion::load_json(const char* file) {
	std::filesystem::path path(file);
	path = std::filesystem::absolute(path);
	std::ifstream commands(path);
	nlohmann::json json;
	commands >> json;

	for (auto& [key, value] : json.items()) {
		m_completions.items.push_back(this->create_suggestion(value));
	};
}

/**
 * Formats our text from a json entry. These are the hints we parse once on startup.
 *
 * \param
 * \return
 */
lsp::data::completion_item Completion::create_suggestion(nlohmann::json& command) {
	lsp::data::markup_content hint = this->hint_former(command);
	lsp::data::completion_item completion;

	//completion.kind = lsp::data::completion_item_kind::Operator;
	completion.label = command["title"];
	completion.data = m_index++;
	completion.detail = command["docSyntax"];
	completion.documentation = hint;
	return completion;
};

/**
 * Creates the actual MarkupText shown in the documentation part of the autocompletion.
 *
 * \param value
 * \return
 */
lsp::data::markup_content Completion::hint_former(nlohmann::json& command) {
	std::vector<std::string> hint = {
		"```sqf",
		command["syntax"].get<std::string>(),
		"```"
	};

	// add the arguments per line (Or None)
	hint.push_back("**Arguments**");
	if (command["parameters"].size() == 0) {
		hint.push_back("* None");
	} else {
		for (std::string arg : command["parameters"]) {
			hint.push_back("* " + arg);
		};
	};

	// add return values per line (Or None)
	hint.push_back("\n**Return**");
	if (command["return_value"].size() == 0) {
		hint.push_back("* None");
	} else {
		for (std::string arg : command["return_value"]) {
			hint.push_back("* " + arg);
		};
	};

	// add clickable link for the description
	// broken, needs casting? Who knows
	hint.push_back("\n[Description](" + command["url"].get<std::string>() + ')');

	// join with linebreaks
	std::string hint_joined = std::accumulate(std::next(hint.begin()), hint.end(), hint[0],
		[](std::string a, std::string b) {
			return a + "\n" + b;
		}
	);
	return lsp::data::markup_content{ lsp::data::markup_kind::Markdown, hint_joined };
};

/**
 * Provides autocomplete list.
 *
 * \return
 */
lsp::data::completion_list Completion::as_completion_list() {
	return m_completions;
};
