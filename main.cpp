#include "bayan.h"

#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>

int main(int argc, char* argv[])
{
    boost::program_options::options_description desc("Usage: bayan [OPTIONS]... [FILES]...\nAll options:");
    desc.add_options()
        ("help", "Help")
        ("blocksize,b", boost::program_options::value<int>()->default_value(64), "Block size")
        ("hash,h",      boost::program_options::value<std::string>(), "Hash type (sha1, crc32)")
        ("files,f",     boost::program_options::value<std::vector<std::string>>()->multitoken()->zero_tokens()->composing(), "Files to check");

    boost::program_options::positional_options_description posDescription;
    posDescription.add("files", -1);

    boost::program_options::command_line_parser parser{ argc, argv };
    parser.options(desc).positional(posDescription).allow_unregistered();
    boost::program_options::parsed_options parsed_options = parser.run();

    boost::program_options::variables_map vm;
    boost::program_options::store(parsed_options, vm);
    boost::program_options::notify(vm);

    bayan::InputData data;
    data.blockSize = 64;
    data.hash = bayan::Type::CRC32;

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return -1;
    }

    if (vm.count("blocksize"))
        data.blockSize = vm["blocksize"].as<int>();

    if (vm.count("hash"))
        data.hash = bayan::hashFromString(vm["hash"].as<std::string>());

    if (vm.count("files"))
        data.files = vm["files"].as<std::vector<std::string>>();

    if (bayan::isSame(data)) {
        std::cout << "file identic" << std::endl;
    } else {
        std::cout << "file not identic" << std::endl;
    }

    return 0;
}
