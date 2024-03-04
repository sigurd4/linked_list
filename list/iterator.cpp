#include "iterator.hpp"

namespace sss
{
    template<typename T>
    constexpr list<T>::iterator::iterator(void) noexcept:
        link {std::nullopt}
    {

    }

    template<typename T>
    constexpr list<T>::iterator::iterator(list<T>::link& link, bool is_reverse) noexcept:
        link {link},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr list<T>::iterator::iterator(list& list, bool is_reverse) noexcept:
        link {is_reverse ? list.get_last_link() : list.get_first_link()},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename list<T>::link>>
        list<T>::iterator::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> list<T>::iterator::next(void) noexcept
    {
        if(this->link.has_value())
        {
            link& link = this->link.value();
            T& value = link.value;
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
    constexpr std::optional<std::reference_wrapper<T>> list<T>::iterator::prev(void) noexcept
    {
        if(this->link.has_value())
        {
            link& link = this->link.value();
            T& value = link.value;
            if(!this->is_reverse)
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
    constexpr typename list<T>::iterator list<T>::iterator::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::iterator list<T>::iterator::end(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename list<T>::iterator list<T>::iterator::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::iterator list<T>::iterator::cend(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr T& list<T>::iterator::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr T* list<T>::iterator::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename list<T>::iterator& list<T>::iterator::operator++() noexcept
    {
        if(this->link.has_value())
        {
            list<T>::link& link = this->link.value();
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
    constexpr typename list<T>::iterator list<T>::iterator::operator++(int) noexcept
    {
        iterator copy = *this;
        if(this->link.has_value())
        {
            list<T>::link& link = this->link.value();
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
    constexpr typename list<T>::iterator& list<T>::iterator::operator--() noexcept
    {
        if(this->link.has_value())
        {
            link& link = this->link.value();
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
    constexpr typename list<T>::iterator list<T>::iterator::operator--(int) noexcept
    {
        iterator copy = *this;
        if(this->link.has_value())
        {
            link& link = this->link.value();
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
    constexpr void list<T>::iterator::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            list<T>::link& link = this->link.value();
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
    constexpr void list<T>::iterator::operator-=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            link& link = this->link.value();
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
    constexpr bool list<T>::iterator::eq(const iterator& rhs) const noexcept
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