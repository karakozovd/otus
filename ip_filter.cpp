#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#define SKIP_SECOND_OCTET   256

//-----------------------------------------------------------------------------//

using IpAddress = std::vector<uint16_t>;
using IpPool = std::vector<IpAddress>;

std::vector<std::string> split(const std::string &str, char d);
void printPool(const IpPool &pool);

IpPool filter(uint16_t first, uint16_t second = SKIP_SECOND_OCTET);
IpPool filterAny(uint16_t octet);

static IpPool mainPool;

//-----------------------------------------------------------------------------//

int main()
{
    for (std::string line; std::getline(std::cin, line);) {
        std::vector<std::string> entry = split(line, '\t');
        std::vector<std::string> octets = split(entry.at(0), '.');

        IpAddress addr;

        for (const auto &octet : octets) {
            std::istringstream stream(octet);

            uint16_t byte = 0;
            stream >> byte; // cast std::string -> uint16_t (not hex)

            addr.push_back(byte);
        }

        mainPool.push_back(addr);
    }

    std::sort(mainPool.begin(), mainPool.end(), std::greater<>());

    printPool(mainPool);

    IpPool filterFirstByte = filter(1);
    printPool(filterFirstByte);

    IpPool filterTwiceBytes = filter(46, 70);
    printPool(filterTwiceBytes);

    IpPool filterAnyBytes = filterAny(46);
    printPool(filterAnyBytes);

    return 0;
}

//-----------------------------------------------------------------------------//

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

//-----------------------------------------------------------------------------//

void printPool(const IpPool &pool)
{
    for (IpPool::const_iterator ip = pool.cbegin(); ip != pool.cend(); ++ip) {
        for (IpAddress::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
            if (ip_part != ip->cbegin()) {
                std::cout << ".";
            }

            std::cout << *ip_part;
        }

        std::cout << std::endl;
    }
}

//-----------------------------------------------------------------------------//

IpPool filter(uint16_t first, uint16_t second)
{
    IpPool outPool;

    for (const auto &ip : mainPool) {
        if (second == SKIP_SECOND_OCTET) {
            if (ip.at(0) == first) {
                outPool.push_back(ip);
            }
        } else {
            if (ip.at(0) == first && ip.at(1) == second) {
                outPool.push_back(ip);
            }
        }
    }

    std::sort(outPool.begin(), outPool.end(), std::greater<>());

    return outPool;
}

//-----------------------------------------------------------------------------//

IpPool filterAny(uint16_t octet)
{
    IpPool outPool;

    for (const auto &ip : mainPool) {
        for (const auto &part : ip) {
            if (part == octet) {
                outPool.push_back(ip);
                break;
            }
        }
    }

    std::sort(outPool.begin(), outPool.end(), std::greater<>());

    return outPool;
}
