#include <string>
#include <vector>

namespace bayan {
enum class Type {
    SHA1,
    CRC32
};

Type hashFromString(const std::string &str);
std::string hashToString(const Type &type, const char *data, size_t len);

struct InputData {
    std::vector<std::string> files;
    size_t blockSize;
    Type hash;
};

bool isSame(const InputData &data);
}
