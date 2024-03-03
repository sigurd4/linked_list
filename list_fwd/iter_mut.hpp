#pragma once

#include "../list_fwd.hpp"

#include "link.hpp"
#include "iter.hpp"

namespace sss
{
    template<typename T>
    class ListFwd<T>::IterMut
    {
        private:
            std::optional<std::reference_wrapper<Link>> link;
            
        public:
            constexpr IterMut(void) noexcept;
            constexpr IterMut(Link& link) noexcept;
            constexpr IterMut(ListFwd& list) noexcept;
            friend constexpr Iter::Iter(const IterMut& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<Link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<T>> next(void) noexcept;

            constexpr IterMut begin(void) const noexcept;
            constexpr IterMut end(void) const noexcept;
            constexpr IterMut cbegin(void) const noexcept;
            constexpr IterMut cend(void) const noexcept;

            constexpr T& operator*(void) const;
            constexpr T* operator->(void) const;
            constexpr IterMut& operator++() noexcept;
            constexpr IterMut operator++(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;

            constexpr bool eq(const IterMut& rhs) const noexcept;
            
            friend constexpr bool operator==(const IterMut& a, const IterMut& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const IterMut& a, const IterMut& b) noexcept
            {
                return !a.eq(b);
            }

            friend class ListFwd;
    };
}

#include "iter_mut.cpp"