#include "bayan.h"

#include <fstream>
#include <algorithm>

#include <boost/uuid/detail/sha1.hpp>
#include <boost/functional/hash.hpp>
#include <boost/crc.hpp>
#include <boost/filesystem.hpp>

namespace bayan {

Type hashFromString(const std::string &str)
{
    Type res = Type::CRC32;
    if (str == "crc32" || str == "CRC32") {
        res = Type::CRC32;
    } else if (str == "sha1" || str == "SHA1") {
        res = Type::SHA1;
    }

    return res;
}

std::string hashToString(const Type &type, const char *data, size_t len)
{
    switch (type) {
    case Type::SHA1: {
        unsigned resHash[5];

        boost::uuids::detail::sha1 Sha1;
        Sha1.process_bytes(data, len);

        std::string res;
        Sha1.get_digest(resHash);

        for (auto d : resHash) { res += std::to_string(d); }
        return res;
    } break;

    case Type::CRC32: {
        boost::crc_32_type crc_hash;
        crc_hash.process_bytes(data, len);
        return std::to_string(crc_hash.checksum());
    } break;

    default:
        break;
    }

    return {};
}

bool isSame(const InputData &data)
{
    size_t size = boost::filesystem::file_size(data.files.front());
    auto found = std::find_if(data.files.begin(), data.files.end(), [&size](const std::string &tmp) {
        return size != boost::filesystem::file_size(tmp);
    });

    if (found != data.files.end())
        return false;

    std::vector<std::ifstream> fileStreams(data.files.size());
    std::vector<char> buf(data.blockSize);

    size_t blockCount = size / data.blockSize + 1;
    size_t lastSize = size % data.blockSize;

    for (size_t i = 0; i < blockCount; i++) {
        std::string fisrtHash, curHash;
        for (size_t j = 0; j < data.files.size(); j++) {
            if (i == 0) {
                fileStreams[j].rdbuf()->pubsetbuf(nullptr, 0);
                fileStreams[j].open(data.files[j], std::ios::in | std::ios::binary);
                if (!fileStreams[j].is_open()) {
                    return false;
                }
            }

            if (i == blockCount - 1) {
                fileStreams[j].read(buf.data(), lastSize);
                memset(buf.data() + lastSize, 0, buf.size() - lastSize);
            } else {
                fileStreams[j].read(buf.data(), buf.size());
            }

            switch (data.hash) {
            case Type::CRC32: {
                auto type = Type::CRC32;
                curHash = hashToString(type, buf.data(), buf.size());
            } break;
            case Type::SHA1: {
                auto type = Type::SHA1;
                curHash = hashToString(type, buf.data(), buf.size());
            } break;
            }

            if (j == 0) {
                fisrtHash = curHash;
            } else {
                if (fisrtHash != curHash) {
                    return false;
                }
            }
        }
    }

    return true;
}

}
