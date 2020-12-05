#pragma once

#include <vector>

#include "../util/uri.h"
#include "../util/lspserver.h"

namespace ls
{
    class server;
    class document
    {
        x39::uri m_uri;
    protected:
        server& m_server;
    public:
        document(server& srv, x39::uri uri) : m_uri(uri), m_server(srv)
        {

        }

        x39::uri uri() const
        {
            return m_uri;
        }

        virtual std::vector<lsp::data::diagnostics> analyze() = 0;
    };
}