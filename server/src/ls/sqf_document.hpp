#pragma once

#include "document.hpp"

namespace ls
{
    class sqf_document : public document
    {
    public:
        sqf_document(server& srv, x39::uri uri) : document(srv, uri)
        {

        }
        virtual std::vector<lsp::data::diagnostics> analyze() override;
    };
}