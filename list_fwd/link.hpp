#pragma once

#include "../list_fwd.hpp"

namespace sss
{
    template<typename T>
    class ListFwd<T>::Link
    {
        public:
            T value;
            std::optional<std::unique_ptr<Link>> next {std::nullopt};

        public:
            constexpr Link(void) noexcept;
            constexpr explicit Link(const Link& link) noexcept;
            constexpr Link(Link&& link) noexcept;
            constexpr Link(T&& value) noexcept;

            template<typename... Args>
            static constexpr Link make(Args&&... args);

            constexpr Iter cbegin(void) const noexcept;
            constexpr Iter cend(void) const noexcept;
            constexpr IterMut begin(void) noexcept;
            constexpr IterMut end(void) noexcept;
            constexpr Iter begin(void) const noexcept;
            constexpr Iter end(void) const noexcept;

            constexpr std::optional<std::reference_wrapper<const Link>> next_link(void) const noexcept;
            constexpr std::optional<std::reference_wrapper<Link>> next_link(void) noexcept;

            constexpr std::pair<std::optional<std::reference_wrapper<const Link>>, const Link&>
                last_two_links(std::optional<std::reference_wrapper<const Link>> prev = {}) const noexcept;
            constexpr std::pair<std::optional<std::reference_wrapper<Link>>, Link&>
                last_two_links(std::optional<std::reference_wrapper<Link>> prev = {}) noexcept;

            constexpr const Link& last_link(void) const noexcept;
            constexpr Link& last_link(void) noexcept;

            constexpr Link& append(ListFwd<T>&& next) noexcept;
            constexpr Link& append(Link&& next) noexcept;
            constexpr Link& prepend(ListFwd<T>&& prev) noexcept;
            constexpr Link& prepend(Link&& prev) noexcept;
            constexpr std::pair<Link, std::optional<Link>>
                pop(
                    std::optional<std::reference_wrapper<Link>> prev,
                    std::optional<std::reference_wrapper<Link>> direct_prev,
                    Link& first
                ) noexcept;
            
            constexpr ListFwd split_in_half(void) noexcept;
            template<typename F>
            constexpr void merge(Link&& link, F&& cmp) noexcept;
            template<typename F>
            constexpr void merge(Link&& link, const F& cmp) noexcept;

            constexpr void operator=(Link&& link) noexcept;
    };
}

#include "link.cpp"