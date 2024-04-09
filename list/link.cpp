#include "link.hpp"

namespace sss
{
    template<typename T>
    constexpr list<T>::link::link(void) noexcept:
        value {}
    {

    }
    template<typename T>
    constexpr list<T>::link::link(
        const list<T>::link& link,
        std::optional<std::reference_wrapper<list<T>::link>> prev
    ) noexcept:
        value {link.value},
        prev {prev}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = {std::make_unique<list<T>::link>(*link.next.value(), *this)};
        }
    }
    template<typename T>
    constexpr list<T>::link::link(link&& link) noexcept:
        value {std::move(link.value)}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = std::move(link.next);
            this->next.value()->prev = *this;
        }
        this->prev = std::move(link.prev);
    }

    template<typename T>
    constexpr list<T>::link::link(T&& value) noexcept:
        value {std::move(value)}
    {
        
    }
    
    template<typename T>
    template<typename... Args> requires std::constructible_from<T, Args...>
    constexpr typename list<T>::link list<T>::link::make(Args&&... args)
    {
        return {T(std::move(args)...)};
    }

    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::cbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr list<T>::iterator list<T>::link::begin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr list<T>::iterator list<T>::link::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::end(void) const noexcept
    {
        return this->cend();
    }
    
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::rcbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::rcend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr list<T>::iterator list<T>::link::rbegin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr list<T>::iterator list<T>::link::rend(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::rbegin(void) const noexcept
    {
        return this->rcbegin();
    }
    template<typename T>
    constexpr list<T>::const_iterator list<T>::link::rend(void) const noexcept
    {
        return this->rcend();
    }

#pragma warning(push)
#pragma warning(disable: 4297)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wterminate"
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename list<T>::link>>
        list<T>::link::next_link(void) const noexcept
    {
        if(this->next.has_value())
        {
            const std::unique_ptr<link>& ptr = this->next.value();
            if(ptr)
            {
                if(!ptr->prev.has_value() || &ptr->prev.value().get() != this)
                {
                    std::terminate();
                }
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename list<T>::link>>
        list<T>::link::next_link(void) noexcept
    {
        if(this->next.has_value())
        {
            std::unique_ptr<link>& ptr = this->next.value();
            if(ptr)
            {
                if(!ptr->prev.has_value() || &ptr->prev.value().get() != this)
                {
                    std::terminate();
                }
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename list<T>::link>>
        list<T>::link::prev_link(void) const noexcept
    {
        if(this->prev.has_value())
        {
            if(!this->prev.value().get().next.has_value() || &*this->prev.value().get().next.value() != this)
            {
                std::terminate();
            }
            return this->prev.value();
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename list<T>::link>>
        list<T>::link::prev_link(void) noexcept
    {
        if(this->prev.has_value())
        {
            if(!this->prev.value().get().next.has_value() || &*this->prev.value().get().next.value() != this)
            {
                std::terminate();
            }
            return this->prev.value();
        }
        return {};
    }
#pragma clang diagnostic pop
#pragma warning(pop)

    template<typename T>
    constexpr const typename list<T>::link&
        list<T>::link::last_link(void) const noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::link& list<T>::link::last_link(void) noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }
    template<typename T>
    constexpr const typename list<T>::link& list<T>::link::first_link(void) const noexcept
    {
        auto prev = this->prev_link();
        if(prev.has_value())
        {
            return prev.value().get().first_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::link& list<T>::link::first_link(void) noexcept
    {
        auto prev = this->prev_link();
        if(prev.has_value())
        {
            return prev.value().get().first_link();
        }
        return *this;
    }

    template<typename T>
    constexpr typename list<T>::link& list<T>::link::append(list&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->append(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::link& list<T>::link::append(link&& link) noexcept
    {
        list<T>::link& first {link.first_link()};
        first.prev = *this;

        if(this->next.has_value() && this->next.value() != nullptr)
        {
            std::swap(*this->next.value(), first);
            first.prev = {};
            this->next.value()->last_link().append(std::move(first));
        }
        else
        {
            this->next = std::make_unique<list<T>::link>(std::move(first));
        }
        return *this->next.value();
    }

    template<typename T>
    constexpr typename list<T>::link& list<T>::link::prepend(list&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->prepend(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename list<T>::link& list<T>::link::prepend(link&& link) noexcept
    {
        if(link.prev.has_value())
        {
            return this->prepend(std::move(link.first_link()));
        }
        std::swap(*this, link);
        this->last_link().append(std::move(link));
        return *this;
    }

    template<typename T>
    constexpr std::pair<typename list<T>::link, std::optional<typename list<T>::link>>
        list<T>::link::pop(std::optional<std::reference_wrapper<link>> prev) noexcept
    {
        link& first = this->first_link();
        std::optional<link> next = {};
        T value = std::move(this->value);
        if(this->next.has_value() && this->next.value())
        {
            this->next.value()->prev = {};
            std::optional<link> n {std::move(*this->next.value())};
            next = std::move(n);
        }
        bool is_first {!this->prev.has_value()};
        if(!is_first)
        {
            this->prev.value().get().next = {};
        }
        if(prev.has_value())
        {
            if(next.has_value())
            {
                next.value().prev = prev;
                std::optional<std::unique_ptr<link>> n {std::make_unique<link>(std::move(next.value()))};
                prev.value().get().next.swap(n);

                next = {};
                if(n.has_value())
                {
                    n.value()->prev = {};
                    n.value()->append(std::move(value));
                    return {std::move(*n.value()), std::move(next)};
                }
            }
            else
            {
                std::optional<std::unique_ptr<link>> n {};
                prev.value().get().next.swap(n);

                next = {};
                if(n.has_value())
                {
                    n.value()->prev = {};
                    n.value()->append(std::move(value));
                    return {std::move(*n.value()), std::move(next)};
                }
            }
        }
        else if(!is_first)
        {
            link n {std::move(first)};
            n.last_link().append(std::move(value));
            return {std::move(n), std::move(next)};
        }
        return {std::move(value), std::move(next)};
    }

    template<typename T>
    constexpr list<T> list<T>::link::split_in_half(void) noexcept
    {
        std::reference_wrapper<link> slow = *this;
        std::optional<std::reference_wrapper<const link>> fast = this->next_link();

        while(fast.has_value())
        {
            fast = fast.value().get().next_link();
            if(fast.has_value())
            {
                fast = fast.value().get().next_link();
                std::optional<std::reference_wrapper<link>> next = slow.get().next_link();
                if(next.has_value())
                {
                    slow = next.value();
                }
                else
                {
                    break;
                }
            }
        }

        std::optional<std::unique_ptr<link>> back {};
        slow.get().next.swap(back);

        list b {};
        if(back.has_value())
        {
            back.value()->prev = {};
            b.first = std::move(*back.value());
        }

        return b;
    }
    template<typename T>
    template<typename F>
    constexpr void list<T>::link::merge(link&& link, F&& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            link.prev.swap(this->prev);
            std::swap(*this, link);
        }
        std::optional<std::reference_wrapper<list<T>::link>> next = this->next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(link), std::move(cmp));
        }
        else
        {
            std::optional<std::unique_ptr<list<T>::link>> b
                {std::make_unique<list<T>::link>(std::move(link))};
            b.value()->prev = *this;
            this->next.swap(b);
        }
    }
    template<typename T>
    template<typename F>
    constexpr void list<T>::link::merge(link&& link, const F& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            link.prev.swap(this->prev);
            std::swap(*this, link);
        }
        std::optional<std::reference_wrapper<list<T>::link>> next = this->next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(link), cmp);
        }
        else
        {
            std::optional<std::unique_ptr<list<T>::link>> b
                {std::make_unique<list<T>::link>(std::move(link))};
            b.value()->prev = *this;
            this->next.swap(b);
        }
    }

    template<typename T>
    constexpr void list<T>::link::operator=(link&& link) noexcept
    {
        this->value = std::move(link.value);
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = std::move(link.next);
            this->next.value()->prev = *this;
        }
        else
        {
            this->next = {};
        }
        this->prev = std::move(link.prev);
    }
}