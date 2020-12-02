#include <stdio.h>
#include <stdint.h>
#include <string.h>

namespace ip {

class IPv6Address {

public:
    IPv6Address();

    bool fromString(const char *addrstr);

    void print();

private:
    unsigned char _address[16];
}  __attribute__((__packed__));


IPv6Address::IPv6Address()
{
    memset(_address, 0, sizeof(_address));
}

#define MAX_IPV6_ADDRESS_STR_LEN  39

static int8_t asciiToHex(char c)
{
    c |= 0x20;

    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return (c - 'a') + 10;
    } else {
        return -1;
    }
}

bool IPv6Address::fromString(const char *addrstr)
{
    uint16_t accumulator = 0;
    uint8_t colon_count = 0;
    uint8_t pos = 0;

    memset(_address, 0, sizeof(_address));

    for(uint8_t i=1; i <= MAX_IPV6_ADDRESS_STR_LEN; i++) {
        if (addrstr[i] == ':') {
            if (addrstr[i-1] == ':') {
                colon_count = 14;
            } else if (colon_count) {
                colon_count -= 2;
            }
        } else if (addrstr[i] == '\0') {
            break;
        }
    }

    for(uint8_t i=0; i <= MAX_IPV6_ADDRESS_STR_LEN && pos < 16; i++) {
        if (addrstr[i] == ':' || addrstr[i] == '\0') {
            _address[pos] = accumulator >> 8;
            _address[pos+1] = accumulator;
            accumulator = 0;

            if (colon_count && i && addrstr[i-1] == ':') {
                pos = colon_count;
            } else {
                pos += 2;
            }
        } else {
            int8_t val = asciiToHex(addrstr[i]);
            if (val == -1) {
                return 0;
            } else {
                accumulator <<= 4;
                accumulator |= val;
            }
        }

        if (addrstr[i] == '\0')
            break;
    }

    return 1;
}

static void printPaddedHex(uint8_t byte)
{
    char str[2];
    str[0] = (byte >> 4) & 0x0f;
    str[1] = byte & 0x0f;

    for (int i=0; i<2; i++) {
        if (str[i] > 9) str[i] += 39;
        str[i] += 48;
        printf("%c", str[i]);
    }
}

}