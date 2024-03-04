#include "iterator.hpp"

namespace sss
{
    template<typename T>
    constexpr forward_list<T>::iterator::iterator(void) noexcept:
        link {std::nullopt}
    {

    }

    template<typename T>
    constexpr forward_list<T>::iterator::iterator(forward_list<T>::link& link) noexcept:
        link {link}
    {

    }

    template<typename T>
    constexpr forward_list<T>::iterator::iterator(forward_list& list) noexcept:
        link {list.get_first_link()}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename forward_list<T>::link>>
        forward_list<T>::iterator::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> forward_list<T>::iterator::next(void) noexcept
    {
        if(this->link.has_value())
        {
            link& link = this->link.value();
            T& value = link.value;
            this->link = link.next_link();
            return {value};
        }
        return {};
    }

    template<typename T>
    constexpr typename forward_list<T>::iterator forward_list<T>::iterator::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::iterator forward_list<T>::iterator::end(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename forward_list<T>::iterator forward_list<T>::iterator::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::iterator forward_list<T>::iterator::cend(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr T& forward_list<T>::iterator::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr T* forward_list<T>::iterator::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename forward_list<T>::iterator& forward_list<T>::iterator::operator++() noexcept
    {
        if(this->link.has_value())
        {
            forward_list<T>::link& link = this->link.value();
            this->link = link.next_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::iterator forward_list<T>::iterator::operator++(int) noexcept
    {
        iterator copy = *this;
        if(this->link.has_value())
        {
            forward_list<T>::link& link = this->link.value();
            this->link = link.next_link();
        }
        return copy;
    }
    template<typename T>
    constexpr void forward_list<T>::iterator::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            forward_list<T>::link& link = this->link.value();
            this->link = link.next_link();
        }
    }

    template<typename T>
    constexpr bool forward_list<T>::iterator::eq(const iterator& rhs) const noexcept
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