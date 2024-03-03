#pragma once

#include "../list.hpp"

#include "link.hpp"
#include "iter.hpp"

namespace sss
{
    template<typename T>
    class List<T>::IterMut
    {
        private:
            std::optional<std::reference_wrapper<Link>> link;
            
        public:
            bool is_reverse;

            constexpr IterMut(void) noexcept;
            constexpr IterMut(Link& link, bool is_reverse) noexcept;
            constexpr IterMut(List& list, bool is_reverse) noexcept;
            friend constexpr Iter::Iter(const IterMut& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<Link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<T>> next(void) noexcept;
            constexpr std::optional<std::reference_wrapper<T>> prev(void) noexcept;

            constexpr IterMut begin(void) const noexcept;
            constexpr IterMut end(void) const noexcept;
            constexpr IterMut cbegin(void) const noexcept;
            constexpr IterMut cend(void) const noexcept;

            constexpr T& operator*(void) const;
            constexpr T* operator->(void) const;
            constexpr IterMut& operator++() noexcept;
            constexpr IterMut operator++(int) noexcept;
            constexpr IterMut& operator--() noexcept;
            constexpr IterMut operator--(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;
            constexpr void operator-=(size_t steps) noexcept;

            constexpr bool eq(const IterMut& rhs) const noexcept;
            
            friend constexpr bool operator==(const IterMut& a, const IterMut& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const IterMut& a, const IterMut& b) noexcept
            {
                return !a.eq(b);
            }

            friend class List;
    };
}

#include "iter_mut.cpp"