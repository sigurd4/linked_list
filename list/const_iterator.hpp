#pragma once

#include "../list.hpp"

namespace sss
{
    template<typename T>
    class list<T>::const_iterator
    {
        private:
            std::optional<std::reference_wrapper<const link>> link;

        public:
            bool is_reverse;

            constexpr const_iterator(void) noexcept;
            constexpr const_iterator(const list<T>::link& link, bool is_reverse) noexcept;
            constexpr const_iterator(const list& list, bool is_reverse) noexcept;
            constexpr const_iterator(const iterator& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<const list<T>::link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<const T>> next(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const T>> prev(void) noexcept;

            constexpr const_iterator begin(void) const noexcept;
            constexpr const_iterator end(void) const noexcept;
            constexpr const_iterator cbegin(void) const noexcept;
            constexpr const_iterator cend(void) const noexcept;

            constexpr const T& operator*(void) const;
            constexpr const T* operator->(void) const;
            constexpr const_iterator& operator++() noexcept;
            constexpr const_iterator operator++(int) noexcept;
            constexpr const_iterator& operator--() noexcept;
            constexpr const_iterator operator--(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;
            constexpr void operator-=(size_t steps) noexcept;

            constexpr bool eq(const const_iterator& rhs) const noexcept;
            
            friend constexpr bool operator==(const const_iterator& a, const const_iterator& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const const_iterator& a, const const_iterator& b) noexcept
            {
                return !a.eq(b);
            }

            friend class list;
    };
}

#include "const_iterator.cpp"