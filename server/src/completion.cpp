#include "completion.h"
#include <fstream>
#include <string>


Completion::Completion() {
    this->load_json("commands.min.json");
}

/**
 * Loads our json file(s) based on which engine we're running.
 * Will parse to completion_item[]
 *
 */
void Completion::load_json(const char * file) {
	std::ifstream commands(file);
	nlohmann::json json;
	commands >> json;

	for (auto& [key, value] : json.items()) {
		m_completions.items.push_back(this->create_suggestion(value));
	};
}

/**
 * Creates the actual MarkupText shown in the documentation part of the autocompletion.
 *
 * \param value
 * \return
 */
lsp::data::markup_content Completion::create_hint(nlohmann::json& command) {
	std::vector<std::string> hint;

    hint.push_back("```sqf", command["syntax"], "```");

    // add the arguments per  line
	hint.push_back("**Arguments**");
    if (command["parameters"].size == 0) {
        hint.push_back("* None");
    } else {
        for (auto& arg : command["parameters"]) {
            hint.push_back("* " + arg);
        };
    };

    hint.push_back("\n**Return**");
    if (command["return_value"].size == 0) {
        hint.push_back("* None");
    };

	// join
	std::string hint_joined = std::accumulate(std::next(hint.begin()), hint.end(), hint[0],
		[](std::string a, std::string b) {
			return a + "\n" + b;
		}
	);



	return lsp::data::markup_content{ lsp::data::markup_kind::Markdown, hint_joined };
};

/**
 * Formats our text from a json entry. These are the hints we parse once on startup.
 *
 * \param
 * \return
 */
lsp::data::completion_item Completion::create_suggestion(nlohmann::json& command) {

};

/**
 * Provides autocomplete list.
 *
 * \return
 */
lsp::data::completion_list Completion::as_completion_list() {
    return m_completions;
};