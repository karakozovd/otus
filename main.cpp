#include "parser.h"

#include <iostream>
#include <sstream>
#include <fstream>

//-------------------------------------------------------------//

static std::stringstream g_logFileName;

void bulkToOstream(std::ostream &str, const std::vector<Command> &cmds)
{
    str << "bulk:\t";
    for (auto it = cmds.begin(); it != cmds.end(); ++it) {
        if (it != cmds.begin()) {
            str << ", ";
        }

        str << it->cmd();
    }
    str << std::endl;
}

void bulkToFileCallback(const std::vector<Command> &cmds)
{
    if (g_logFileName.str().empty()) {
        g_logFileName << "bulk" << cmds.front().timestamp() << ".log";
    }

    std::fstream file(g_logFileName.str(), std::fstream::out | std::fstream::app);
    bulkToOstream(file, cmds);
}

void bulkToStdoutCallback(const std::vector<Command> &cmds)
{
    bulkToOstream(std::cout, cmds);
}

//-------------------------------------------------------------//

int main(int argc, char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <size>\n", argv[0]);
        return 1;
    }

    size_t blockSize = atoi(argv[1]);
    if (blockSize <= 0) {
        fprintf(stderr, "incorrect block size; exit\n");
        return 1;
    }

    Parser p(blockSize);
    p.addCallback(&bulkToFileCallback);
    p.addCallback(&bulkToStdoutCallback);
    p.start();

    if (p.hasError())
        return 1;

    return 0;
}
