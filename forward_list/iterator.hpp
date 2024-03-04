#pragma once

#include "../forward_list.hpp"

#include "link.hpp"
#include "const_iterator.hpp"

namespace sss
{
    template<typename T>
    class forward_list<T>::iterator
    {
        private:
            std::optional<std::reference_wrapper<link>> link;
            
        public:
            constexpr iterator(void) noexcept;
            constexpr iterator(forward_list<T>::link& link) noexcept;
            constexpr iterator(forward_list& list) noexcept;
            friend constexpr const_iterator::const_iterator(const iterator& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<forward_list<T>::link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<T>> next(void) noexcept;

            constexpr iterator begin(void) const noexcept;
            constexpr iterator end(void) const noexcept;
            constexpr iterator cbegin(void) const noexcept;
            constexpr iterator cend(void) const noexcept;

            constexpr T& operator*(void) const;
            constexpr T* operator->(void) const;
            constexpr iterator& operator++() noexcept;
            constexpr iterator operator++(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;

            constexpr bool eq(const iterator& rhs) const noexcept;
            
            friend constexpr bool operator==(const iterator& a, const iterator& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const iterator& a, const iterator& b) noexcept
            {
                return !a.eq(b);
            }

            friend class forward_list;
    };
}

#include "iterator.cpp"