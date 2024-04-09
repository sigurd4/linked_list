#pragma once

#include "concepts.hpp"

#include <optional>
#include <memory>
#include <ranges>
#include <execution>

namespace sss
{
    template<typename T>
    class list : public std::ranges::view_interface<list<T>>
    {
        private:
            class link;

        public:
            class const_iterator;
            class iterator;

        private:
            std::optional<link> first;

            constexpr list(link&& first) noexcept;
            constexpr list(std::optional<link>&& first) noexcept;
        public:
            constexpr list(void) noexcept;
            constexpr list(size_t count, const T& value) noexcept;
            constexpr explicit list(size_t count) noexcept;
            constexpr list(const list& list) noexcept;
            constexpr list(list&& list) noexcept;
            constexpr list(std::initializer_list<T> values) noexcept;
#if _HAS_CXX23 && defined(__cpp_lib_concepts)
            template<typename R> requires std::ranges::range<R>
            constexpr list(std::from_range_t, const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr list(std::from_range_t, R&& range) noexcept;
#endif

            constexpr list& assign(size_t count, const T& value) noexcept;
            constexpr list& assign(std::initializer_list<T> values) noexcept;
            constexpr list& assign(std::initializer_list<T> values) noexcept requires std::copyable<T>;
            template<typename R> requires std::ranges::range<R>
            constexpr list& assign_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr list& assign_range(R&& range) noexcept;

            // Element access ------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr std::optional<std::reference_wrapper<const T>> front(void) const noexcept;
            [[nodiscard]] constexpr std::optional<std::reference_wrapper<T>> front(void) noexcept;
            [[nodiscard]] constexpr std::optional<std::reference_wrapper<const T>> back(void) const noexcept;
            [[nodiscard]] constexpr std::optional<std::reference_wrapper<T>> back(void) noexcept;

            // const_iteratorators -----------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr const_iterator cbegin(void) const noexcept;
            [[nodiscard]] constexpr const_iterator cend(void) const noexcept;
            [[nodiscard]] constexpr iterator begin(void) noexcept;
            [[nodiscard]] constexpr iterator end(void) noexcept;
            [[nodiscard]] constexpr const_iterator begin(void) const noexcept;
            [[nodiscard]] constexpr const_iterator end(void) const noexcept;

            [[nodiscard]] constexpr const_iterator crbegin(void) const noexcept;
            [[nodiscard]] constexpr const_iterator crend(void) const noexcept;
            [[nodiscard]] constexpr iterator rbegin(void) noexcept;
            [[nodiscard]] constexpr iterator rend(void) noexcept;
            [[nodiscard]] constexpr const_iterator rbegin(void) const noexcept;
            [[nodiscard]] constexpr const_iterator rend(void) const noexcept;

            // Capacity ------------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr bool empty(void) const noexcept;
            [[nodiscard]] constexpr size_t size(void) const noexcept;
            [[nodiscard]] constexpr size_t max_size(void) const noexcept;

            // Modifiers -----------------------------------------------------------------------------------------------
            
            constexpr list& clear(void) noexcept;
            
            constexpr std::optional<T> insert(size_t position, const T& value) noexcept;
            constexpr std::optional<T> insert(size_t position, T&& value) noexcept;
            constexpr std::optional<list> insert(size_t position, list&& list) noexcept;
            constexpr std::optional<list> insert(size_t position, const list& list) noexcept;
            constexpr std::optional<list> insert(size_t position, size_t count, const T& value) noexcept;
            constexpr std::optional<list> insert(size_t position, std::initializer_list<T> list) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr std::optional<list> insert_range(size_t position, const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr std::optional<list> insert_range(size_t position, R&& range) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr std::optional<T> emplace(size_t position, Args&&... args) noexcept;
            
            constexpr std::optional<T> take(size_t position) noexcept;
            constexpr std::optional<list> take(size_t first, size_t last) noexcept;
            constexpr size_t erase(size_t position) noexcept;
            constexpr size_t erase(size_t first, size_t last) noexcept;
            
            constexpr list& push_back(const T& value) noexcept;
            constexpr list& push_back(T&& value) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr list& emplace_back(Args&&... args) noexcept;
            constexpr list& append(const list& value) noexcept;
            constexpr list& append(list&& value) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr list& append_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr list& append_range(R&& range) noexcept;
            
            constexpr list& push_front(const T& value) noexcept;
            constexpr list& push_front(T&& value) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr list& emplace_front(Args&&... args) noexcept;
            constexpr list& prepend(const list& value) noexcept;
            constexpr list& prepend(list&& value) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr list& prepend_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr list& prepend_range(R&& range) noexcept;

            constexpr std::optional<T> pop_back(void) noexcept;
            constexpr std::optional<T> pop_front(void) noexcept;

            constexpr list& resize(size_t size) noexcept;
            constexpr list& resize(size_t size, const T& value) noexcept;

            constexpr list& swap(list& list) noexcept;

            // Operations ----------------------------------------------------------------------------------------------

            constexpr list& merge(const list& list) noexcept;
            constexpr list& merge(list&& list) noexcept;
            template<typename F>
            constexpr list& merge(const list& list, const F& cmp) noexcept;
            template<typename F>
            constexpr list& merge(list&& list, const F& cmp) noexcept;
            template<typename F>
            constexpr list& merge(const list& list, F&& cmp) noexcept;
            template<typename F>
            constexpr list& merge(list&& list, F&& cmp) noexcept;

            constexpr list& splice(size_t position, list& list) noexcept;
            constexpr std::optional<list> splice(size_t position, list&& list) noexcept;
            constexpr list& splice(size_t position, list& list, size_t from_position) noexcept;
            constexpr std::optional<list> splice(size_t position, list&& list, size_t from_position) noexcept;
            constexpr list& splice(size_t position, list& list, size_t from_first, size_t from_last) noexcept;
            constexpr std::optional<list>
                splice(size_t position, list&& list, size_t from_first, size_t from_last) noexcept;

            constexpr size_t remove(const T& value) noexcept;
            template<typename F>
            constexpr size_t remove_if(const F& predicate) noexcept;
            template<typename F>
            constexpr size_t remove_if(F&& predicate) noexcept;
            
            constexpr list& reverse(void) noexcept;
            
            constexpr size_t unique(void) noexcept;
            template<typename F>
            constexpr size_t unique(const F& predicate) noexcept;
            template<typename F>
            constexpr size_t unique(F&& predicate) noexcept;

            constexpr list& sort(void) noexcept;
            template<typename F> requires sss::comparison<F, T>
            constexpr list& sort(const F& predicate) noexcept;
            template<typename F> requires sss::comparison<F, T>
            constexpr list& sort(F&& predicate) noexcept;
            template<typename P> requires sss::execution_policy<P>
            constexpr list& sort(P policy) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P> && sss::comparison<F, T>
            constexpr list& sort(P policy, const F& predicate) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P> && sss::comparison<F, T>
            constexpr list& sort(P policy, F&& predicate) noexcept;

            // Extra ---------------------------------------------------------------------------------------------------

            template<typename F>
            constexpr list<std::invoke_result_t<F, T&&>> transform(const F& map) noexcept;
            template<typename F>
            constexpr list<std::invoke_result_t<F, T&&>> transform(F&& map) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P>
            constexpr list<std::invoke_result_t<F, T&&>> transform(P policy, const F& map) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P>
            constexpr list<std::invoke_result_t<F, T&&>> transform(P policy, F&& map) noexcept;

            template<typename U>
            template<typename F>
            friend constexpr list<std::invoke_result_t<F, U&&>> list<U>::transform(const F& map) noexcept;
            template<typename U>
            template<typename F>
            friend constexpr list<std::invoke_result_t<F, U&&>> list<U>::transform(F&& map) noexcept;

            // Operators -----------------------------------------------------------------------------------------------

            constexpr list& operator=(const list& list) noexcept;
            constexpr list& operator=(list&& list) noexcept;
            constexpr list& operator=(std::initializer_list<T> values) noexcept;

        private:
            constexpr std::optional<std::reference_wrapper<link>> get_first_link(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const link>> get_first_link(void) const noexcept;
            
            constexpr std::optional<std::reference_wrapper<link>> get_last_link(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const link>> get_last_link(void) const noexcept;
    };
}

#include "list/link.hpp"
#include "list/const_iterator.hpp"
#include "list/iterator.hpp"

#include "list.cpp"