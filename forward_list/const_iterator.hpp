#pragma once

#include "../forward_list.hpp"

namespace sss
{
    template<typename T>
    class forward_list<T>::const_iterator
    {
        private:
            std::optional<std::reference_wrapper<const link>> link;

        public:
            constexpr const_iterator(void) noexcept;
            constexpr const_iterator(const forward_list<T>::link& link) noexcept;
            constexpr const_iterator(const forward_list& list) noexcept;
            constexpr const_iterator(const iterator& iterator) noexcept;

            constexpr std::optional<std::reference_wrapper<const forward_list<T>::link>> get_link() const noexcept;

            constexpr std::optional<std::reference_wrapper<const T>> next(void) noexcept;

            constexpr const_iterator begin(void) const noexcept;
            constexpr const_iterator end(void) const noexcept;
            constexpr const_iterator cbegin(void) const noexcept;
            constexpr const_iterator cend(void) const noexcept;

            constexpr const T& operator*(void) const;
            constexpr const T* operator->(void) const;
            constexpr const_iterator& operator++() noexcept;
            constexpr const_iterator operator++(int) noexcept;
            constexpr void operator+=(size_t steps) noexcept;

            constexpr bool eq(const const_iterator& rhs) const noexcept;
            
            friend constexpr bool operator==(const const_iterator& a, const const_iterator& b) noexcept
            {
                return a.eq(b);
            }
            friend constexpr bool operator!=(const const_iterator& a, const const_iterator& b) noexcept
            {
                return !a.eq(b);
            }

            friend class forward_list;
    };
}

#include "const_iterator.cpp"