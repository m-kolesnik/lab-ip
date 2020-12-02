#pragma once

#include <array>
#include <string>
#include <string_view>
#include <stdint.h>

namespace ip
{
    class invalid_format_exception : public std::exception
    {
        std::string invalid_format_;
    public:
        invalid_format_exception(const std::string &invalid_format) noexcept;
		virtual ~invalid_format_exception() noexcept {};
        char const* what() const noexcept override;
    };

    class address
    {
    public:

#pragma region Type definitions
        using value_type = uint8_t;
		using storage_type = std::array<value_type, 4>;
        using reference = value_type & ;
        using pointer = value_type * ;
        using size_type = std::array<value_type, 4>::size_type;
#pragma endregion
        address(value_type first, value_type second,
            value_type third, value_type fourth);
        address(const std::array<unsigned char, 4> &data);
        explicit address(uint32_t value);
        reference operator[](const int &index) noexcept(false);
        value_type operator[](const int &index) const noexcept(false);
        address& operator++();
        address operator++(int);
        address& operator--();
        address operator--(int);
    private:
        storage_type data_{};
    };

    bool operator<(const ip::address &first, const ip::address &second);
    bool operator==(const ip::address &first, const ip::address &second);
    std::ostream& operator<<(std::ostream& output, const ip::address &address);
    address from_string(const std::string &view);
    std::string to_string(const address& address);
	uint32_t to_uint32(const address& address);
}