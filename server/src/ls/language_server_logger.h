#pragma once
#include <runtime/logging.h>

namespace ls
{
    class server;

    class language_server_logger : public Logger {
        server& language_server;
    public:
        language_server_logger(server& ref) : Logger(), language_server(ref) {}

        virtual void log(const LogMessageBase& base) override;
    };
}