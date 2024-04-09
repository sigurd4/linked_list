#pragma once

#include "../list.hpp"

#include "link.hpp"
#include "const_iterator.hpp"

namespace sss
{
    template<typename T>
    class list<T>::iterator
    {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = T;
            using difference_type   = std::make_signed_t<size_t>;
            using pointer           = T*;
            using reference         = T&;

        private:
            std::optional<std::reference_wrapper<link>> link;
            
        public:
            bool is_reverse;

            constexpr iterator(void) noexcept;
            constexpr iterator(list<T>::link& link, bool is_reverse) noexcept;
            constexpr iterator(list& list, bool is_reverse) noexcept;
            friend constexpr const_iterator::const_iterator(const iterator& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<list<T>::link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<T>> next(void) noexcept;
            constexpr std::optional<std::reference_wrapper<T>> prev(void) noexcept;

            constexpr iterator begin(void) const noexcept;
            constexpr iterator end(void) const noexcept;
            constexpr iterator cbegin(void) const noexcept;
            constexpr iterator cend(void) const noexcept;

            constexpr T& operator*(void) const;
            constexpr T* operator->(void) const;
            constexpr iterator& operator++() noexcept;
            constexpr iterator operator++(int) noexcept;
            constexpr iterator& operator--() noexcept;
            constexpr iterator operator--(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;
            constexpr void operator-=(size_t steps) noexcept;

            constexpr bool eq(const iterator& rhs) const noexcept;
            
            friend constexpr bool operator==(const iterator& a, const iterator& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const iterator& a, const iterator& b) noexcept
            {
                return !a.eq(b);
            }

            friend class list;
    };
}

#include "iterator.cpp"