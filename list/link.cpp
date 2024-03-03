#include "link.hpp"

namespace sss
{
    template<typename T>
    constexpr List<T>::Link::Link(void) noexcept:
        value {}
    {

    }
    template<typename T>
    constexpr List<T>::Link::Link(const Link& link, std::optional<std::reference_wrapper<Link>> prev) noexcept:
        value {link.value},
        prev {prev}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = {std::make_unique<Link>(*link.next.value(), *this)};
        }
    }
    template<typename T>
    constexpr List<T>::Link::Link(Link&& link) noexcept:
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
    constexpr List<T>::Link::Link(T&& value) noexcept:
        value {std::move(value)}
    {
        
    }
    
    template<typename T>
    template<typename... Args>
    constexpr typename List<T>::Link List<T>::Link::make(Args&&... args)
    {
        return {T(std::move(args)...)};
    }

    template<typename T>
    constexpr List<T>::Iter List<T>::Link::cbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::Link::begin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::Link::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::end(void) const noexcept
    {
        return this->cend();
    }
    
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::rcbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::rcend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::Link::rbegin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::Link::rend(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::rbegin(void) const noexcept
    {
        return this->rcbegin();
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::Link::rend(void) const noexcept
    {
        return this->rcend();
    }

#pragma warning(push)
#pragma warning(disable: 4297)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wterminate"
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename List<T>::Link>>
        List<T>::Link::next_link(void) const noexcept
    {
        if(this->next.has_value())
        {
            const std::unique_ptr<Link>& ptr = this->next.value();
            if(ptr)
            {
                if(!ptr->prev.has_value() || &ptr->prev.value().get() != this)
                {
                    throw "Broken chain on next";
                }
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename List<T>::Link>>
        List<T>::Link::next_link(void) noexcept
    {
        if(this->next.has_value())
        {
            std::unique_ptr<Link>& ptr = this->next.value();
            if(ptr)
            {
                if(!ptr->prev.has_value() || &ptr->prev.value().get() != this)
                {
                    throw "Broken chain on next";
                }
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename List<T>::Link>>
        List<T>::Link::prev_link(void) const noexcept
    {
        if(this->prev.has_value())
        {
            if(!this->prev.value().get().next.has_value() || &*this->prev.value().get().next.value() != this)
            {
                throw "Broken chain on prev";
            }
            return this->prev.value();
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename List<T>::Link>>
        List<T>::Link::prev_link(void) noexcept
    {
        if(this->prev.has_value())
        {
            if(!this->prev.value().get().next.has_value() || &*this->prev.value().get().next.value() != this)
            {
                throw "Broken chain on prev";
            }
            return this->prev.value();
        }
        return {};
    }
#pragma clang diagnostic pop
#pragma warning(pop)

    template<typename T>
    constexpr const typename List<T>::Link&
        List<T>::Link::last_link(void) const noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::Link& List<T>::Link::last_link(void) noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }
    template<typename T>
    constexpr const typename List<T>::Link& List<T>::Link::first_link(void) const noexcept
    {
        auto prev = this->prev_link();
        if(prev.has_value())
        {
            return prev.value().get().first_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::Link& List<T>::Link::first_link(void) noexcept
    {
        auto prev = this->prev_link();
        if(prev.has_value())
        {
            return prev.value().get().first_link();
        }
        return *this;
    }

    template<typename T>
    constexpr typename List<T>::Link& List<T>::Link::append(List&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->append(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::Link& List<T>::Link::append(Link&& link) noexcept
    {
        Link& first {link.first_link()};
        first.prev = *this;

        if(this->next.has_value() && this->next.value() != nullptr)
        {
            std::swap(*this->next.value(), first);
            first.prev = {};
            this->next.value()->last_link().append(std::move(first));
        }
        else
        {
            this->next = std::make_unique<Link>(std::move(first));
        }
        return *this->next.value();
    }

    template<typename T>
    constexpr typename List<T>::Link& List<T>::Link::prepend(List&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->prepend(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename List<T>::Link& List<T>::Link::prepend(Link&& link) noexcept
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
    constexpr std::pair<typename List<T>::Link, std::optional<typename List<T>::Link>>
        List<T>::Link::pop(std::optional<std::reference_wrapper<Link>> prev) noexcept
    {
        Link& first = this->first_link();
        std::optional<Link> next = {};
        T value = std::move(this->value);
        if(this->next.has_value() && this->next.value())
        {
            this->next.value()->prev = {};
            std::optional<Link> n {std::move(*this->next.value())};
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
                std::optional<std::unique_ptr<Link>> n {std::make_unique<Link>(std::move(next.value()))};
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
                std::optional<std::unique_ptr<Link>> n {};
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
            Link n {std::move(first)};
            n.last_link().append(std::move(value));
            return {std::move(n), std::move(next)};
        }
        return {std::move(value), std::move(next)};
    }

    template<typename T>
    constexpr List<T> List<T>::Link::split_in_half(void) noexcept
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

        List b {};
        if(back.has_value())
        {
            back.value()->prev = {};
            b.first = std::move(*back.value());
        }

        return b;
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::Link::merge(Link&& link, F&& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            link.prev.swap(this->prev);
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
            b.value()->prev = *this;
            this->next.swap(b);
        }
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::Link::merge(Link&& link, const F& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            link.prev.swap(this->prev);
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
            b.value()->prev = *this;
            this->next.swap(b);
        }
    }

    template<typename T>
    constexpr void List<T>::Link::operator=(Link&& link) noexcept
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