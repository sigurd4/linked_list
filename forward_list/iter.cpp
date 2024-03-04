#include "iter.hpp"

namespace sss
{
    template<typename T>
    constexpr ListFwd<T>::Iter::Iter(void) noexcept
    {

    }

    template<typename T>
    constexpr ListFwd<T>::Iter::Iter(const Link& link) noexcept:
        link {link}
    {

    }

    template<typename T>
    constexpr ListFwd<T>::Iter::Iter(const ListFwd& list) noexcept:
        link {list.get_first_link()}
    {

    }

    template<typename T>
    constexpr ListFwd<T>::Iter::Iter(const IterMut& iterator) noexcept:
        link {iterator.link}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename ListFwd<T>::Link>> ListFwd<T>::Iter::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> ListFwd<T>::Iter::next(void) noexcept
    {
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
            const T& value = link.value;
            this->link = link.next_link();
            return {value};
        }
        return {};
    }

    template<typename T>
    constexpr typename ListFwd<T>::Iter ListFwd<T>::Iter::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Iter ListFwd<T>::Iter::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename ListFwd<T>::Iter ListFwd<T>::Iter::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Iter ListFwd<T>::Iter::end(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr const T& ListFwd<T>::Iter::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr const T* ListFwd<T>::Iter::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Iter& ListFwd<T>::Iter::operator++() noexcept
    {
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
            this->link = link.next_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Iter ListFwd<T>::Iter::operator++(int) noexcept
    {
        Iter copy = *this;
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
            this->link = link.next_link();
        }
        return copy;
    }
    template<typename T>
    constexpr void ListFwd<T>::Iter::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            const Link& link = this->link.value();
            this->link = link.next_link();
        }
    }

    template<typename T>
    constexpr bool ListFwd<T>::Iter::eq(const Iter& rhs) const noexcept
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