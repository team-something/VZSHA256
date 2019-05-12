#include "sha256.h"

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    std::string s;
    std::getline(std::cin, s);
    std::vector<uint32_t> hash_digest;
    vzsha256::sha256(s, hash_digest);
    for(auto x : hash_digest)
    {
        std::cout << std::hex << x;
    }
    std::cout << "\n";
    return 0;
}
