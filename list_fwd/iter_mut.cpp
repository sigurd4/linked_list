#include "iter_mut.hpp"

namespace sss
{
    template<typename T>
    constexpr ListFwd<T>::IterMut::IterMut(void) noexcept:
        link {std::nullopt}
    {

    }

    template<typename T>
    constexpr ListFwd<T>::IterMut::IterMut(Link& link) noexcept:
        link {link}
    {

    }

    template<typename T>
    constexpr ListFwd<T>::IterMut::IterMut(ListFwd& list) noexcept:
        link {list.get_first_link()}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename ListFwd<T>::Link>>
        ListFwd<T>::IterMut::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> ListFwd<T>::IterMut::next(void) noexcept
    {
        if(this->link.has_value())
        {
            Link& link = this->link.value();
            T& value = link.value;
            this->link = link.next_link();
            return {value};
        }
        return {};
    }

    template<typename T>
    constexpr typename ListFwd<T>::IterMut ListFwd<T>::IterMut::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::IterMut ListFwd<T>::IterMut::end(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename ListFwd<T>::IterMut ListFwd<T>::IterMut::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::IterMut ListFwd<T>::IterMut::cend(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr T& ListFwd<T>::IterMut::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr T* ListFwd<T>::IterMut::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename ListFwd<T>::IterMut& ListFwd<T>::IterMut::operator++() noexcept
    {
        if(this->link.has_value())
        {
            Link& link = this->link.value();
            this->link = link.next_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::IterMut ListFwd<T>::IterMut::operator++(int) noexcept
    {
        IterMut copy = *this;
        if(this->link.has_value())
        {
            Link& link = this->link.value();
            this->link = link.next_link();
        }
        return copy;
    }
    template<typename T>
    constexpr void ListFwd<T>::IterMut::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            Link& link = this->link.value();
            this->link = link.next_link();
        }
    }

    template<typename T>
    constexpr bool ListFwd<T>::IterMut::eq(const IterMut& rhs) const noexcept
    {
        if(!this->get_link().has_value())
        {
            return !rhs.get_link().has_value();
        }
        if(!rhs.get_link().has_value())
        {
            return false;
        }
        const T* a = &this->get_link().value().get().value;
        const T* b = &rhs.get_link().value().get().value;
        return a == b;
    }
}