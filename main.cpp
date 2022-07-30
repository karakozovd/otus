#include "allocator.h"
#include "container.h"

#include <map>
#include <vector>

int main()
{
    std::map<int, int, std::less<>, BasicAllocator<std::pair<const int, int>, 10>> map;

    for (int i = 0; i < 10; ++i) {
        map.insert({i, i * i});
    }

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << "[" << it->first << "] = " << it->second << std::endl;
    }

    map.erase(0);
    map.erase(3);
    map.erase(5);

    for (auto it = map.begin(); it != map.end(); ++it) {
        std::cout << "[" << it->first << "] = " << it->second << std::endl;
    }

    std::cout << "-----------------------" << std::endl;


    BasicVector<int, BasicAllocator<int, 5>> vector;

    for (int i = 0; i < 5; ++i) {
        vector.push_back(i * i + 1);
    }

    vector.pop_back();
    vector.pop_back();
    vector.pop_back();

    for (auto i : vector) {
        std::cout << i << std::endl;
    }

    return 0;
}
