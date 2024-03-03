#include "link.hpp"

namespace sss
{
    template<typename T>
    constexpr ListFwd<T>::Link::Link(void) noexcept:
        value {}
    {

    }
    template<typename T>
    constexpr ListFwd<T>::Link::Link(const Link& link) noexcept:
        value {link.value}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = {std::make_unique<Link>(*link.next.value())};
        }
    }
    template<typename T>
    constexpr ListFwd<T>::Link::Link(Link&& link) noexcept:
        value {std::move(link.value)}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = std::move(link.next);
        }
    }

    template<typename T>
    constexpr ListFwd<T>::Link::Link(T&& value) noexcept:
        value {std::move(value)}
    {
        
    }
    
    template<typename T>
    template<typename... Args>
    constexpr typename ListFwd<T>::Link ListFwd<T>::Link::make(Args&&... args)
    {
        return {T(std::move(args)...)};
    }

    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::Link::cbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::Link::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr ListFwd<T>::IterMut ListFwd<T>::Link::begin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr ListFwd<T>::IterMut ListFwd<T>::Link::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::Link::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::Link::end(void) const noexcept
    {
        return this->cend();
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename ListFwd<T>::Link>> ListFwd<T>::Link::next_link(void) const noexcept
    {
        if(this->next.has_value())
        {
            const std::unique_ptr<Link>& ptr = this->next.value();
            if(ptr)
            {
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename ListFwd<T>::Link>> ListFwd<T>::Link::next_link(void) noexcept
    {
        if(this->next.has_value())
        {
            std::unique_ptr<Link>& ptr = this->next.value();
            if(ptr)
            {
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr const typename ListFwd<T>::Link& ListFwd<T>::Link::last_link(void) const noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Link& ListFwd<T>::Link::last_link(void) noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }

    template<typename T>
    constexpr std::pair<std::optional<std::reference_wrapper<const typename ListFwd<T>::Link>>, const typename ListFwd<T>::Link&>
        ListFwd<T>::Link::last_two_links(std::optional<std::reference_wrapper<const Link>> prev) const noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_two_links({*this});
        }
        return {prev, *this};
    }
    template<typename T>
    constexpr std::pair<std::optional<std::reference_wrapper<typename ListFwd<T>::Link>>, typename ListFwd<T>::Link&>
        ListFwd<T>::Link::last_two_links(std::optional<std::reference_wrapper<Link>> prev) noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_two_links({*this});
        }
        return {prev, *this};
    }

    template<typename T>
    constexpr typename ListFwd<T>::Link& ListFwd<T>::Link::append(ListFwd&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->append(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Link& ListFwd<T>::Link::append(Link&& link) noexcept
    {
        if(this->next.has_value() && this->next.value() != nullptr)
        {
            std::swap(*this->next.value(), link);
            this->next.value()->last_link().append(std::move(link));
        }
        else
        {
            this->next = std::make_unique<Link>(std::move(link));
        }
        return *this->next.value();
    }

    template<typename T>
    constexpr typename ListFwd<T>::Link& ListFwd<T>::Link::prepend(ListFwd&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->prepend(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename ListFwd<T>::Link& ListFwd<T>::Link::prepend(Link&& link) noexcept
    {
        std::swap(*this, link);
        this->last_link().append(std::move(link));
        return *this;
    }

    template<typename T>
    constexpr std::pair<typename ListFwd<T>::Link, std::optional<typename ListFwd<T>::Link>>
        ListFwd<T>::Link::pop(
            std::optional<std::reference_wrapper<Link>> prev,
            std::optional<std::reference_wrapper<Link>> direct_prev,
            Link& first
        ) noexcept
    {
        std::optional<Link> next = {};
        T value = std::move(this->value);
        if(this->next.has_value() && this->next.value())
        {
            std::optional<Link> n {std::move(*this->next.value())};
            next = std::move(n);
        }
        bool is_first {!direct_prev.has_value()};
        if(!is_first)
        {
            direct_prev.value().get().next = {};
        }
        if(prev.has_value())
        {
            if(next.has_value())
            {
                std::optional<std::unique_ptr<Link>> n {std::make_unique<Link>(std::move(next.value()))};
                prev.value().get().next.swap(n);

                next = {};
                if(n.has_value())
                {
                    n.value()->append(std::move(value));
                    return {std::move(*n.value()), std::move(next)};
                }
            }
            else
            {
                std::optional<std::unique_ptr<Link>> n {};
                prev.value().get().next.swap(n);

                next = {};
                if(n.has_value())
                {
                    n.value()->append(std::move(value));
                    return {std::move(*n.value()), std::move(next)};
                }
            }
        }
        else if(!is_first)
        {
            Link n {std::move(first)};
            n.last_link().append(std::move(value));
            return {std::move(n), std::move(next)};
        }
        return {std::move(value), std::move(next)};
    }

    template<typename T>
    constexpr ListFwd<T> ListFwd<T>::Link::split_in_half(void) noexcept
    {
        std::reference_wrapper<Link> slow = *this;
        std::optional<std::reference_wrapper<const Link>> fast = this->next_link();

        while(fast.has_value())
        {
            fast = fast.value().get().next_link();
            if(fast.has_value())
            {
                fast = fast.value().get().next_link();
                std::optional<std::reference_wrapper<Link>> next = slow.get().next_link();
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

        std::optional<std::unique_ptr<Link>> back {};
        slow.get().next.swap(back);

        ListFwd b {};
        if(back.has_value())
        {
            b.first = std::move(*back.value());
        }

        return b;
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::Link::merge(Link&& link, F&& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            std::swap(*this, link);
        }
        std::optional<std::reference_wrapper<Link>> next = this->next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(link), std::move(cmp));
        }
        else
        {
            std::optional<std::unique_ptr<Link>> b {std::make_unique<Link>(std::move(link))};
            this->next.swap(b);
        }
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::Link::merge(Link&& link, const F& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            std::swap(*this, link);
        }
        std::optional<std::reference_wrapper<Link>> next = this->next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(link), cmp);
        }
        else
        {
            std::optional<std::unique_ptr<Link>> b {std::make_unique<Link>(std::move(link))};
            this->next.swap(b);
        }
    }

    template<typename T>
    constexpr void ListFwd<T>::Link::operator=(Link&& link) noexcept
    {
        this->value = std::move(link.value);
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = std::move(link.next);
        }
        else
        {
            this->next = {};
        }
    }
}