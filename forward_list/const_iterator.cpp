#include "const_iterator.hpp"

namespace sss
{
    template<typename T>
    constexpr forward_list<T>::const_iterator::const_iterator(void) noexcept
    {

    }

    template<typename T>
    constexpr forward_list<T>::const_iterator::const_iterator(const forward_list<T>::link& link) noexcept:
        link {link}
    {

    }

    template<typename T>
    constexpr forward_list<T>::const_iterator::const_iterator(const forward_list& list) noexcept:
        link {list.get_first_link()}
    {

    }

    template<typename T>
    constexpr forward_list<T>::const_iterator::const_iterator(const iterator& iterator) noexcept:
        link {iterator.link}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename forward_list<T>::link>> forward_list<T>::const_iterator::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> forward_list<T>::const_iterator::next(void) noexcept
    {
        if(this->link.has_value())
        {
            const forward_list<T>::link& link = this->link.value();
            const T& value = link.value;
            this->link = link.next_link();
            return {value};
        }
        return {};
    }

    template<typename T>
    constexpr typename forward_list<T>::const_iterator forward_list<T>::const_iterator::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::const_iterator forward_list<T>::const_iterator::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename forward_list<T>::const_iterator forward_list<T>::const_iterator::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::const_iterator forward_list<T>::const_iterator::end(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr const T& forward_list<T>::const_iterator::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr const T* forward_list<T>::const_iterator::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename forward_list<T>::const_iterator& forward_list<T>::const_iterator::operator++() noexcept
    {
        if(this->link.has_value())
        {
            const forward_list<T>::link& link = this->link.value();
            this->link = link.next_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::const_iterator forward_list<T>::const_iterator::operator++(int) noexcept
    {
        const_iterator copy = *this;
        if(this->link.has_value())
        {
            const forward_list<T>::link& link = this->link.value();
            this->link = link.next_link();
        }
        return copy;
    }
    template<typename T>
    constexpr void forward_list<T>::const_iterator::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            const forward_list<T>::link& link = this->link.value();
            this->link = link.next_link();
        }
    }

    template<typename T>
    constexpr bool forward_list<T>::const_iterator::eq(const const_iterator& rhs) const noexcept
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