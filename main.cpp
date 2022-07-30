#include "allocator.h"
#include "container.h"

#include <map>
#include <vector>

int factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main()
{
    std::map<int, int> map;
    std::map<int, int, std::less<>, BasicAllocator<std::pair<const int, int>, 10>> amap;

    for (int i = 0; i < 10; ++i) {
        map.insert({i, factorial(i)});
        amap.insert({i, factorial(i)});
    }

    for (auto it = amap.begin(); it != amap.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }

    BasicVector<int, BasicAllocator<int, 10>> vector;

    for (int i = 0; i < 10; ++i) {
        vector.push_back(i);
    }

    for (auto i : vector) {
        std::cout << i << " ";
    }

    return 0;
}
