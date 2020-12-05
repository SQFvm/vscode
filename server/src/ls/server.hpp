#pragma once

#include <memory>

#include <runtime/runtime.h>
#include <parser/config/default.h>
#include <parser/preprocessor/default.h>
#include <parser/sqf/sqf_parser.hpp>
#include <fileio/default.h>
#include <operators/ops.h>

#include "../util/lspserver.h"
#include "../util/language_server_logger.h"
#include "../git_sha1.h"

namespace ls
{
    class server : public lsp::server
    {
    private:
        language_server_logger m_logger;
        sqf::runtime::runtime* m_runtime;
    public:
        server() : m_logger(*this), m_runtime(nullptr)
        {
            reset_runtime();
        }
        ~server()
        {
            delete m_runtime;
        }
        sqf::runtime::runtime& runtime()
        {
            return *m_runtime;
        }
        void reset_runtime()
        {
            m_runtime = new sqf::runtime::runtime{ m_logger, {} };
            m_runtime->fileio(std::make_unique<sqf::fileio::impl_default>(m_logger));
            m_runtime->parser_config(std::make_unique<sqf::parser::config::impl_default>(m_logger));
            m_runtime->parser_preprocessor(std::make_unique<sqf::parser::preprocessor::impl_default>(m_logger));
            m_runtime->parser_sqf(std::make_unique<sqf::parser::sqf::parser>(m_logger));
            sqf::operators::ops(*m_runtime);
        }
    protected:
        virtual lsp::data::initialize_result on_initialize(const lsp::data::initialize_params& params) override
        {
            lsp::data::initialize_result res;
            res.serverInfo = lsp::data::initialize_result::server_info{};
            res.serverInfo->name = "SQF-VM Language Server";
            res.serverInfo->version = std::string(g_GIT_SHA1);
            res.capabilities.textDocumentSync = lsp::data::initialize_result::server_capabilities::text_document_sync_options{};
            res.capabilities.textDocumentSync->change = lsp::data::text_document_sync_kind::Full;
            res.capabilities.textDocumentSync->openClose = true;
            res.capabilities.textDocumentSync->save = lsp::data::initialize_result::server_capabilities::text_document_sync_options::SaveOptions{};
            res.capabilities.textDocumentSync->save->includeText = true;
            res.capabilities.textDocumentSync->willSave = false;
            res.capabilities.foldingRangeProvider = lsp::data::initialize_result::server_capabilities::folding_range_registration_options{};
            res.capabilities.foldingRangeProvider->documentSelector = lsp::data::document_filter{ };
            res.capabilities.foldingRangeProvider->documentSelector->language = "sqf";
            // res.capabilities.completionProvider = lsp::data::initialize_result::server_capabilities::completion_options{};
            
            return res;
        }
        virtual void on_shutdown() override {}
    };
}