#pragma once

#include "../list.hpp"

namespace sss
{
    template<typename T>
    class List<T>::Iter
    {
        private:
            std::optional<std::reference_wrapper<const Link>> link;

        public:
            bool is_reverse;

            constexpr Iter(void) noexcept;
            constexpr Iter(const Link& link, bool is_reverse) noexcept;
            constexpr Iter(const List& list, bool is_reverse) noexcept;
            constexpr Iter(const IterMut& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<const Link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<const T>> next(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const T>> prev(void) noexcept;

            constexpr Iter begin(void) const noexcept;
            constexpr Iter end(void) const noexcept;
            constexpr Iter cbegin(void) const noexcept;
            constexpr Iter cend(void) const noexcept;

            constexpr const T& operator*(void) const;
            constexpr const T* operator->(void) const;
            constexpr Iter& operator++() noexcept;
            constexpr Iter operator++(int) noexcept;
            constexpr Iter& operator--() noexcept;
            constexpr Iter operator--(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;
            constexpr void operator-=(size_t steps) noexcept;

            constexpr bool eq(const Iter& rhs) const noexcept;
            
            friend constexpr bool operator==(const Iter& a, const Iter& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const Iter& a, const Iter& b) noexcept
            {
                return !a.eq(b);
            }

            friend class List;
    };
}

#include "iter.cpp"