#pragma once

#include <vector>
#include <string>
#include <chrono>

//-------------------------------------------------------------//

class Command
{
public:
    explicit Command(const std::string &cmd) : m_cmd{cmd}, m_timestamp{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())} { }
    ~Command() = default;

    std::string cmd() const { return m_cmd; }
    time_t timestamp() const { return m_timestamp; }

private:
    std::string m_cmd;
    time_t m_timestamp;
};

//-------------------------------------------------------------//

class Parser
{
public:
    // instead of std::function, just for practice
    typedef void (*callback_t)(const std::vector<Command> &);

    explicit Parser(size_t blocks) : m_blocks{blocks}, m_level{0}, m_hasError{false} { }
    Parser(size_t blocks, const std::vector<callback_t> &funcs) : m_blocks{blocks}, m_level{0}, m_hasError{false}, m_callbacks{funcs} { }
    ~Parser() = default;

    void addCallback(callback_t func);
    void start();

    bool hasError() const { return m_hasError; }

private:
    void flushPendingCommands(bool force);
    void parseFromStdin();
    void parseLine(const std::string &line);

private:
    size_t m_blocks;
    size_t m_level;

    bool m_hasError;

    std::vector<Command> m_commands;

    std::vector<callback_t> m_callbacks;
};
