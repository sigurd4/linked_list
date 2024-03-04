#pragma once

#include "../list.hpp"

namespace sss
{
    template<typename T>
    class list<T>::link
    {
        public:
            T value;
            std::optional<std::unique_ptr<link>> next {std::nullopt};
            std::optional<std::reference_wrapper<link>> prev {std::nullopt};

        public:
            constexpr link(void) noexcept;
            constexpr explicit link(
                const list<T>::link& link,
                std::optional<std::reference_wrapper<list<T>::link>> prev
            ) noexcept;
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
            
            constexpr const_iterator rcbegin(void) const noexcept;
            constexpr const_iterator rcend(void) const noexcept;
            constexpr iterator rbegin(void) noexcept;
            constexpr iterator rend(void) noexcept;
            constexpr const_iterator rbegin(void) const noexcept;
            constexpr const_iterator rend(void) const noexcept;

            constexpr std::optional<std::reference_wrapper<const link>> next_link(void) const noexcept;
            constexpr std::optional<std::reference_wrapper<link>> next_link(void) noexcept;
            
            constexpr std::optional<std::reference_wrapper<const link>> prev_link(void) const noexcept;
            constexpr std::optional<std::reference_wrapper<link>> prev_link(void) noexcept;

            constexpr const link& last_link(void) const noexcept;
            constexpr link& last_link(void) noexcept;
            
            constexpr const link& first_link(void) const noexcept;
            constexpr link& first_link(void) noexcept;

            constexpr link& append(list&& next) noexcept;
            constexpr link& append(link&& next) noexcept;
            constexpr link& prepend(list&& prev) noexcept;
            constexpr link& prepend(link&& prev) noexcept;
            constexpr std::pair<link, std::optional<link>>
                pop(std::optional<std::reference_wrapper<link>> prev) noexcept;
            
            constexpr list split_in_half(void) noexcept;
            template<typename F>
            constexpr void merge(link&& link, F&& cmp) noexcept;
            template<typename F>
            constexpr void merge(link&& link, const F& cmp) noexcept;

            constexpr void operator=(link&& link) noexcept;
    };
}

#include "link.cpp"