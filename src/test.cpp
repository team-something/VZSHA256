#include "sha256.h"

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

int main()
{
    std::string s_ = "aMVsPDdIQaMVsPDdIQaMVsPDdIQaMVsPDdIQaMVsPDdIQaMVsPDdIQaMVsPDdIQa";
    std::string s = "11223344555577889911223344555577889911223344555577889911223344555577889911223344555577889911223344\
                     555577812121212494949494121212";
    std::vector<uint32_t> hash_digest;
    vzsha256::sha256(s_, hash_digest);
    for(auto x : hash_digest)
    {
        std::cout << std::hex << x;
    }
    std::cout << "\n";
    return 0;
}
