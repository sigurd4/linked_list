#include "iter.hpp"

namespace sss
{
    template<typename T>
    constexpr List<T>::Iter::Iter(void) noexcept
    {

    }

    template<typename T>
    constexpr List<T>::Iter::Iter(const Link& link, bool is_reverse) noexcept:
        link {link},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr List<T>::Iter::Iter(const List& list, bool is_reverse) noexcept:
        link {is_reverse ? list.get_last_link() : list.get_first_link()},
        is_reverse {is_reverse}
    {

    }

    template<typename T>
    constexpr List<T>::Iter::Iter(const IterMut& iterator) noexcept:
        link {iterator.link},
        is_reverse {iterator.is_reverse}
    {

    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename List<T>::Link>>
        List<T>::Iter::get_link() const noexcept
    {
        return this->link;
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> List<T>::Iter::next(void) noexcept
    {
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
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
    constexpr typename List<T>::Iter List<T>::Iter::cbegin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::Iter List<T>::Iter::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr typename List<T>::Iter List<T>::Iter::begin(void) const noexcept
    {
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::Iter List<T>::Iter::end(void) const noexcept
    {
        return {};
    }

    template<typename T>
    constexpr const T& List<T>::Iter::operator*(void) const
    {
        return this->link.value().get().value;
    }
    template<typename T>
    constexpr const T* List<T>::Iter::operator->(void) const
    {
        return &this->link.value().get().value;
    }
    template<typename T>
    constexpr typename List<T>::Iter& List<T>::Iter::operator++() noexcept
    {
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
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
    constexpr typename List<T>::Iter List<T>::Iter::operator++(int) noexcept
    {
        Iter copy = *this;
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
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
    constexpr typename List<T>::Iter& List<T>::Iter::operator--() noexcept
    {
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
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
    constexpr typename List<T>::Iter List<T>::Iter::operator--(int) noexcept
    {
        Iter copy = *this;
        if(this->link.has_value())
        {
            const Link& link = this->link.value();
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
    constexpr void List<T>::Iter::operator+=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            const Link& link = this->link.value();
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
    constexpr void List<T>::Iter::operator-=(size_t steps) noexcept
    {
        for(; steps > 0; steps--)
        {
            if(!this->link.has_value())
            {
                break;
            }
            const Link& link = this->link.value();
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
    constexpr bool List<T>::Iter::eq(const Iter& rhs) const noexcept
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