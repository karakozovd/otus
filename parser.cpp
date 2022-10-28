#include "parser.h"
#include <string>
#include <iostream>
#include <iterator>

void Parser::addCallback(Parser::callback_t func)
{
    if (func) {
        m_callbacks.push_back(func);
    }
}

void Parser::start()
{
    if (m_callbacks.empty()) {
        std::cout << "error - no callback functions registered" << std::endl;
        return;
    }

    parseFromStdin();
}

void Parser::flushPendingCommands(bool force = false)
{
    if (!force) {
        if (m_level != 0) {
            return;
        }
    }

    if (!m_commands.empty()) {
        for (auto &callback : m_callbacks) {
            callback(m_commands);
        }

        m_commands.clear();
    }

    if (m_blocks > 0)
        --m_blocks;
}

void Parser::parseFromStdin()
{
    std::string tmp;
    while (std::getline(std::cin, tmp) && !m_hasError) {
        if (m_hasError) {            
            m_commands.clear();
            std::cout << "exit with error" << std::endl;
            break;
        }

        parseLine(tmp);

        if (m_blocks == 0) {
            break;
        }
    }

    if (m_hasError) {
        std::cout << "error - not all logical blocks was closed" << std::endl;
    }
}

void Parser::parseLine(const std::string &line)
{
    if (line.empty()) {
        if (m_level > 0) {
            --m_level;
        }
        flushPendingCommands();
        return;
    }

    auto isOpBrace = [](char symbol) -> bool { return symbol == '{'; };
    auto isClBrace = [](char symbol) -> bool { return symbol == '}'; };

    if (isOpBrace(line.at(0))) {
        ++m_level;

        if (m_level == 1) {
            // exclude our rule only (begin new locial block after recieving { brace) in two cases :
            // 1) if the current block wanna become dynamic and no commands to flush
            // 2) if the last block becomes dynamic
            if (m_commands.empty()) {
                return;
            } else if (m_blocks == 1) {
                return;
            }

            flushPendingCommands(true);
            return;
        }
    } else if (isClBrace(line.at(0))) {
        if (m_level > 0) {
            --m_level;
        }

        if (m_level == 0){
            flushPendingCommands();
            return;
        }
    } else {
        m_commands.push_back(Command(line));
    }
}
