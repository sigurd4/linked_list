#include "const_iterator.hpp"

namespace sss
{
    template<typename T>
    constexpr list<T>::const_iterator::const_iterator(void) noexcept
    {

    }

    template<typename T>
    constexpr list<T>::const_iterator::const_iterator(const list<T>::link& link, bool is_reverse) noexcept:
        link {link},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr list<T>::const_iterator::const_iterator(const list& list, bool is_reverse) noexcept:
        link {is_reverse ? list.get_last_link() : list.get_first_link()},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr list<T>::const_iterator::const_iterator(const iterator& iterator) noexcept:
        link {iterator.link},
        is_reverse {iterator.is_reverse}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename list<T>::link>>
        list<T>::const_iterator::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> list<T>::const_iterator::next(void) noexcept
    {
        if(this->link.has_value())
        {
            const list<T>::link& link = this->link.value();
            const T& value = link.value;
            if(this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
            return {value};
        }
        return {};
    }

    template<typename T>
    constexpr typename list<T>::const_iterator list<T>::const_iterator::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::const_iterator list<T>::const_iterator::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename list<T>::const_iterator list<T>::const_iterator::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::const_iterator list<T>::const_iterator::end(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr const T& list<T>::const_iterator::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr const T* list<T>::const_iterator::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename list<T>::const_iterator& list<T>::const_iterator::operator++() noexcept
    {
        if(this->link.has_value())
        {
            const list<T>::link& link = this->link.value();
            if(this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
        }
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::const_iterator list<T>::const_iterator::operator++(int) noexcept
    {
        const_iterator copy = *this;
        if(this->link.has_value())
        {
            const list<T>::link& link = this->link.value();
            if(this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
        }
        return copy;
    }
    template<typename T>
    constexpr typename list<T>::const_iterator& list<T>::const_iterator::operator--() noexcept
    {
        if(this->link.has_value())
        {
            const list<T>::link& link = this->link.value();
            if(!this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
        }
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::const_iterator list<T>::const_iterator::operator--(int) noexcept
    {
        const_iterator copy = *this;
        if(this->link.has_value())
        {
            const list<T>::link& link = this->link.value();
            if(!this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
        }
        return copy;
    }
    template<typename T>
    constexpr void list<T>::const_iterator::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            const list<T>::link& link = this->link.value();
            if(this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
        }
    }
    template<typename T>
    constexpr void list<T>::const_iterator::operator-=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            const list<T>::link& link = this->link.value();
            if(!this->is_reverse)
            {
                this->link = link.prev_link();
            }
            else
            {
                this->link = link.next_link();
            }
        }
    }

    template<typename T>
    constexpr bool list<T>::const_iterator::eq(const const_iterator& rhs) const noexcept
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