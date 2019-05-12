#include "sha256.h"

namespace vzsha256
{
    uint32_t right_rotate(const uint32_t& in, const int bits)
    {
        /* ********************************************
         * Function to right rotate 32 - bit unsigned integer
         * right_rotate(b'10101, 1) -> b'11010
         * *******************************************/
        return (in >> bits) | (in << (32 - bits));
    }

    uint32_t swap_uint32(uint32_t num)
    {
        /* ***********************************************
         * Function to convert from little endian to big endian
         * For example:
         * 0x12 | 34 | 56 | 78 -> 0x34 | 12 | 78 | 56 -> 0x78 | 56 | 34 | 12
         * ***********************************************/

        num = ((num << 8) & 0xFF00FF00) | ((num >> 8) & 0xFF00FF); // Swap adjacent bytes
        num = (num << 16) | (num >> 16); // Swap adjacent words
        return num;
    }

    void sha256(const std::string& data, std::vector<uint32_t>& hash_digest)
    {
        // Initialise values of the digest
        hash_digest.resize(initial_values_size);
        std::copy(initial_values, initial_values + initial_values_size, hash_digest.begin()); // Copy original data onto padded vector
        // Length of data in bits
        // -------------------- number of bytes -------- number of bits in byte
        uint64_t data_length = ((uint64_t)data.size() * ((uint64_t)CHAR_BIT));

        // Number of blocks of 512 bits required to hash data completely
        uint32_t number_blocks = 1 + ((data_length + 16 + 64) / 512); // Why are we adding 16 and 64??

        std::vector<uint32_t> padded_data((number_blocks * (512 / 32)), 0); // Resize string to fit number_blocks blocks

        std::string temp_ = data + (char)0x80;
        memcpy(&padded_data[0], temp_.c_str(), temp_.size());

        // std::copy(data.begin(), data.end(), padded_data.begin()); // Copy original data onto padded vector
        padded_data[data.size()] = (uint32_t)0x80; // Add bit 1 as last character; 0x80 is 1 in big endian
        // Make all other characters big - endian
        for(int i=0; i<(int)padded_data.size(); ++i)
        {
            padded_data[i] = swap_uint32(padded_data[i]);
        }

        padded_data[((number_blocks * 512 - 64) / 32) + 1] = data_length;

        for(int i=0; i<(int)number_blocks; i++)
        {
            std::vector<uint32_t> w(64, 0); // 64 entry message schedule entry
            //Copy the 16 numbers from the ith block to the w vector
            std::copy(padded_data.begin() + (i * 16), padded_data.begin() + ((i + 1) * 16), w.begin());

            // Create the remaining 48 words from the first 16
            for(uint32_t j=16; j<64; ++j)
            {
                // As per SHA algorithm
                uint32_t s0 = right_rotate(w[j - 15], 7) ^ right_rotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
                uint32_t s1 = right_rotate(w[j - 2], 17) ^ right_rotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
                w[j] = w[j-16] + s0 + w[j-7] + s1;
            }

            // Copy hash digest onto a temp variable
            std::vector <uint32_t> temp_digest(hash_digest);

            // Compression
            for(uint32_t j=0; j<64; j++)
            {
                uint32_t s1 = right_rotate(temp_digest[4], 6) ^ right_rotate(temp_digest[4], 11) ^ right_rotate(temp_digest[4], 25);
                uint32_t ch = (temp_digest[4] & temp_digest[5]) ^ ((~temp_digest[4]) & temp_digest[6]);

                uint32_t temp1 = ch + s1 + temp_digest[7] + round_constants[j] + w[j];

                uint32_t s0 = right_rotate(temp_digest[0], 2) ^ right_rotate(temp_digest[0], 13) ^ right_rotate(temp_digest[0], 22);
                uint32_t maj = (temp_digest[0] & temp_digest[1]) ^ (temp_digest[0] & temp_digest[2]) ^ (temp_digest[1] & temp_digest[2]);

                uint32_t temp2 = s0 + maj;

                temp_digest[7] = temp_digest[6];
                temp_digest[6] = temp_digest[5];
                temp_digest[5] = temp_digest[4];
                temp_digest[4] = temp_digest[3] + temp1;
                temp_digest[3] = temp_digest[2];
                temp_digest[2] = temp_digest[1];
                temp_digest[1] = temp_digest[0];
                temp_digest[0] = temp1 + temp2;
                if(j == 0)
                {
                }
            }

            for(int j=0; j<8; j++)
            {
                hash_digest[j] += temp_digest[j];
            }
        }
    }
}
