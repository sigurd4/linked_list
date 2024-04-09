#include "link.hpp"

namespace sss
{
    template<typename T>
    constexpr forward_list<T>::link::link(void) noexcept:
        value {}
    {

    }
    template<typename T>
    constexpr forward_list<T>::link::link(const link& link) noexcept:
        value {link.value}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = {std::make_unique<forward_list<T>::link>(*link.next.value())};
        }
    }
    template<typename T>
    constexpr forward_list<T>::link::link(link&& link) noexcept:
        value {std::move(link.value)}
    {
        if(link.next.has_value() && link.next.value() != nullptr)
        {
            this->next = std::move(link.next);
        }
    }

    template<typename T>
    constexpr forward_list<T>::link::link(T&& value) noexcept:
        value {std::move(value)}
    {
        
    }
    
    template<typename T>
    template<typename... Args> requires std::constructible_from<T, Args...>
    constexpr typename forward_list<T>::link forward_list<T>::link::make(Args&&... args)
    {
        return {T(std::move(args)...)};
    }

    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::link::cbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::link::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr forward_list<T>::iterator forward_list<T>::link::begin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr forward_list<T>::iterator forward_list<T>::link::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::link::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::link::end(void) const noexcept
    {
        return this->cend();
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename forward_list<T>::link>> forward_list<T>::link::next_link(void) const noexcept
    {
        if(this->next.has_value())
        {
            const std::unique_ptr<link>& ptr = this->next.value();
            if(ptr)
            {
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename forward_list<T>::link>> forward_list<T>::link::next_link(void) noexcept
    {
        if(this->next.has_value())
        {
            std::unique_ptr<link>& ptr = this->next.value();
            if(ptr)
            {
                return {*ptr.get()};
            }
        }
        return {};
    }
    template<typename T>
    constexpr const typename forward_list<T>::link& forward_list<T>::link::last_link(void) const noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::link& forward_list<T>::link::last_link(void) noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_link();
        }
        return *this;
    }

    template<typename T>
    constexpr std::pair<std::optional<std::reference_wrapper<const typename forward_list<T>::link>>, const typename forward_list<T>::link&>
        forward_list<T>::link::last_two_links(std::optional<std::reference_wrapper<const link>> prev) const noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_two_links({*this});
        }
        return {prev, *this};
    }
    template<typename T>
    constexpr std::pair<std::optional<std::reference_wrapper<typename forward_list<T>::link>>, typename forward_list<T>::link&>
        forward_list<T>::link::last_two_links(std::optional<std::reference_wrapper<link>> prev) noexcept
    {
        auto next = this->next_link();
        if(next.has_value())
        {
            return next.value().get().last_two_links({*this});
        }
        return {prev, *this};
    }

    template<typename T>
    constexpr typename forward_list<T>::link& forward_list<T>::link::append(forward_list&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->append(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::link& forward_list<T>::link::append(link&& link) noexcept
    {
        if(this->next.has_value() && this->next.value() != nullptr)
        {
            std::swap(*this->next.value(), link);
            this->next.value()->last_link().append(std::move(link));
        }
        else
        {
            this->next = std::make_unique<forward_list<T>::link>(std::move(link));
        }
        return *this->next.value();
    }

    template<typename T>
    constexpr typename forward_list<T>::link& forward_list<T>::link::prepend(forward_list&& list) noexcept
    {
        if(list.first.has_value())
        {
            return this->prepend(std::move(list.first.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr typename forward_list<T>::link& forward_list<T>::link::prepend(link&& link) noexcept
    {
        std::swap(*this, link);
        this->last_link().append(std::move(link));
        return *this;
    }

    template<typename T>
    constexpr std::pair<typename forward_list<T>::link, std::optional<typename forward_list<T>::link>>
        forward_list<T>::link::pop(
            std::optional<std::reference_wrapper<link>> prev,
            std::optional<std::reference_wrapper<link>> direct_prev,
            link& first
        ) noexcept
    {
        std::optional<link> next = {};
        T value = std::move(this->value);
        if(this->next.has_value() && this->next.value())
        {
            std::optional<link> n {std::move(*this->next.value())};
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
                std::optional<std::unique_ptr<link>> n {std::make_unique<link>(std::move(next.value()))};
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
                std::optional<std::unique_ptr<link>> n {};
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
            link n {std::move(first)};
            n.last_link().append(std::move(value));
            return {std::move(n), std::move(next)};
        }
        return {std::move(value), std::move(next)};
    }

    template<typename T>
    constexpr forward_list<T> forward_list<T>::link::split_in_half(void) noexcept
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

        forward_list b {};
        if(back.has_value())
        {
            b.first = std::move(*back.value());
        }

        return b;
    }
    template<typename T>
    template<typename F>
    constexpr void forward_list<T>::link::merge(link&& link, F&& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            std::swap(*this, link);
        }
        std::optional<std::reference_wrapper<forward_list<T>::link>> next = this->next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(link), std::move(cmp));
        }
        else
        {
            std::optional<std::unique_ptr<forward_list<T>::link>> b
                {std::make_unique<forward_list<T>::link>(std::move(link))};
            this->next.swap(b);
        }
    }
    template<typename T>
    template<typename F>
    constexpr void forward_list<T>::link::merge(link&& link, const F& cmp) noexcept
    {
        if(cmp(link.value, this->value))
        {
            std::swap(*this, link);
        }
        std::optional<std::reference_wrapper<forward_list<T>::link>> next = this->next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(link), cmp);
        }
        else
        {
            std::optional<std::unique_ptr<forward_list<T>::link>> b {std::make_unique<link>(std::move(link))};
            this->next.swap(b);
        }
    }

    template<typename T>
    constexpr void forward_list<T>::link::operator=(link&& link) noexcept
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