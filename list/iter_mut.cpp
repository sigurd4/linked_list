#include "iter_mut.hpp"

namespace sss
{
    template<typename T>
    constexpr List<T>::IterMut::IterMut(void) noexcept:
        link {std::nullopt}
    {

    }

    template<typename T>
    constexpr List<T>::IterMut::IterMut(Link& link, bool is_reverse) noexcept:
        link {link},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr List<T>::IterMut::IterMut(List& list, bool is_reverse) noexcept:
        link {is_reverse ? list.get_last_link() : list.get_first_link()},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename List<T>::Link>>
        List<T>::IterMut::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> List<T>::IterMut::next(void) noexcept
    {
        if(this->link.has_value())
        {
            Link& link = this->link.value();
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
    constexpr std::optional<std::reference_wrapper<T>> List<T>::IterMut::prev(void) noexcept
    {
        if(this->link.has_value())
        {
            Link& link = this->link.value();
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
    constexpr typename List<T>::IterMut List<T>::IterMut::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::IterMut List<T>::IterMut::end(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename List<T>::IterMut List<T>::IterMut::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::IterMut List<T>::IterMut::cend(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr T& List<T>::IterMut::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr T* List<T>::IterMut::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename List<T>::IterMut& List<T>::IterMut::operator++() noexcept
    {
        if(this->link.has_value())
        {
            Link& link = this->link.value();
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
    constexpr typename List<T>::IterMut List<T>::IterMut::operator++(int) noexcept
    {
        IterMut copy = *this;
        if(this->link.has_value())
        {
            Link& link = this->link.value();
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
    constexpr typename List<T>::IterMut& List<T>::IterMut::operator--() noexcept
    {
        if(this->link.has_value())
        {
            Link& link = this->link.value();
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
    constexpr typename List<T>::IterMut List<T>::IterMut::operator--(int) noexcept
    {
        IterMut copy = *this;
        if(this->link.has_value())
        {
            Link& link = this->link.value();
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
    constexpr void List<T>::IterMut::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            Link& link = this->link.value();
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
    constexpr void List<T>::IterMut::operator-=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            Link& link = this->link.value();
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
    constexpr bool List<T>::IterMut::eq(const IterMut& rhs) const noexcept
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