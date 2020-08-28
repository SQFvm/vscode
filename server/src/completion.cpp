#include "completion.h"
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

void Completion::compute(std::vector<variable_declaration::sptr> globals, std::string_view view)
{
	// lowercase input
	std::string data(view);
	std::transform(data.begin(), data.end(), data.begin(), [](char c) { return (char)std::tolower(c); });


	m_completion_live.items.clear();
	for (auto it : m_completion_items)
	{
		// Check if sortText starts with `data`
		if (it.sortText->rfind(data) == 0)
		{
			m_completion_live.items.push_back(it);
		}
	}

	for (auto it : globals)
	{
		// Check if variable name starts with `data`
		if (it->variable.rfind(view) == 0)
		{
			m_completion_live.items.push_back(create_suggestion(it));
		}
	}
	m_completion_live.isIncomplete = false;
}

/**
 * Loads our json file(s) based on which engine we're running.
 * Will parse to completion_item[]
 *
 */
void Completion::load_json(const char* file)
{
	std::filesystem::path path(file);
	path = std::filesystem::absolute(path);
	std::ifstream commands(path);
	if (commands.good())
	{
		nlohmann::json json;
		commands >> json;

		for (auto& [key, value] : json.items())
		{
			m_completion_items.push_back(this->create_suggestion(value));
		}
	}
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
	completion.sortText = command["title"];
	completion.label = command["title"];
	completion.data = m_index++;
	completion.detail = command["docSyntax"];
	completion.documentation = hint;
	lsp::data::from_json(command, "kind", completion.kind);
	return completion;
}
/**
 * Creates a completion_item from an existing variable_declaration.
 *
 * \param
 * \return
 */
lsp::data::completion_item Completion::create_suggestion(variable_declaration::sptr& var)
{
	lsp::data::completion_item completion;

	//completion.kind = lsp::data::completion_item_kind::Operator;
	completion.sortText = var->variable;
	//completion.label = command["title"];
	completion.data = var->variable;
	//completion.detail = command["docSyntax"];
	//completion.documentation = hint;
	completion.kind = lsp::data::completion_item_kind::Variable;
	return completion;
}

/**
 * Creates the actual MarkupText shown in the documentation part of the autocompletion.
 *
 * \param value
 * \return
 */
lsp::data::markup_content Completion::hint_former(nlohmann::json& command) {
	std::stringstream sstream;

	sstream <<
		"```sqf" << std::endl <<
		command["syntax"].get<std::string>() << std::endl <<
		"```" << std::endl;

	// add the arguments per line (Or None)
	sstream << "**Arguments**" << std::endl;
	if (command["parameters"].size() == 0) {
		sstream << "* None" << std::endl;
	} else {
		for (std::string arg : command["parameters"]) {
			sstream << "* " << arg << std::endl;
		};
	};

	// add return values per line (Or None)
	sstream << "**Return**" << std::endl;
	if (command["return_value"].size() == 0) {
		sstream << "* None" << std::endl;
	} else {
		for (std::string arg : command["return_value"]) {
			sstream << "* " << arg << std::endl;
		};
	};

	// add clickable link for the description
	// broken, needs casting? Who knows
	sstream << "[Description](" << command["url"].get<std::string>() << ')' << std::endl;

	// join with linebreaks
	return lsp::data::markup_content{ lsp::data::markup_kind::Markdown, sstream.str() };
};
