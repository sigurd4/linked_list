#pragma once

#include "../forward_list.hpp"

namespace sss
{
    template<typename T>
    class forward_list<T>::link
    {
        public:
            T value;
            std::optional<std::unique_ptr<link>> next {std::nullopt};

        public:
            constexpr link(void) noexcept;
            constexpr explicit link(const link& link) noexcept;
            constexpr link(link&& link) noexcept;
            constexpr link(T&& value) noexcept;

            template<typename... Args>
            static constexpr link make(Args&&... args);

            constexpr const_iterator cbegin(void) const noexcept;
            constexpr const_iterator cend(void) const noexcept;
            constexpr iterator begin(void) noexcept;
            constexpr iterator end(void) noexcept;
            constexpr const_iterator begin(void) const noexcept;
            constexpr const_iterator end(void) const noexcept;

            constexpr std::optional<std::reference_wrapper<const link>> next_link(void) const noexcept;
            constexpr std::optional<std::reference_wrapper<link>> next_link(void) noexcept;

            constexpr std::pair<std::optional<std::reference_wrapper<const link>>, const link&>
                last_two_links(std::optional<std::reference_wrapper<const link>> prev = {}) const noexcept;
            constexpr std::pair<std::optional<std::reference_wrapper<link>>, link&>
                last_two_links(std::optional<std::reference_wrapper<link>> prev = {}) noexcept;

            constexpr const link& last_link(void) const noexcept;
            constexpr link& last_link(void) noexcept;

            constexpr link& append(forward_list<T>&& next) noexcept;
            constexpr link& append(link&& next) noexcept;
            constexpr link& prepend(forward_list<T>&& prev) noexcept;
            constexpr link& prepend(link&& prev) noexcept;
            constexpr std::pair<link, std::optional<link>>
                pop(
                    std::optional<std::reference_wrapper<link>> prev,
                    std::optional<std::reference_wrapper<link>> direct_prev,
                    link& first
                ) noexcept;
            
            constexpr forward_list split_in_half(void) noexcept;
            template<typename F>
            constexpr void merge(link&& link, F&& cmp) noexcept;
            template<typename F>
            constexpr void merge(link&& link, const F& cmp) noexcept;

            constexpr void operator=(link&& link) noexcept;
    };
}

#include "link.cpp"