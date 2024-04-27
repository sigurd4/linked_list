#pragma once

#include "concepts.hpp"

#include <optional>
#include <memory>
#include <execution>

namespace sss
{
    template<typename T>
    class forward_list
    {
        private:
            class link;

        public:
            class const_iterator;
            class iterator;

        private:
            std::optional<link> first;

            constexpr forward_list(link&& first) noexcept;
            constexpr forward_list(std::optional<link>&& first) noexcept;
        public:
            constexpr forward_list(void) noexcept;
            constexpr forward_list(size_t count, const T& value) noexcept;
            constexpr explicit forward_list(size_t count) noexcept;
            constexpr forward_list(const forward_list& list) noexcept;
            constexpr forward_list(forward_list&& list) noexcept;
            constexpr forward_list(std::initializer_list<T> values) noexcept;
#if _HAS_CXX23 && defined(__cpp_lib_concepts)
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list(std::from_range_t, const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list(std::from_range_t, R&& range) noexcept;
#endif

            constexpr forward_list& assign(size_t count, const T& value) noexcept;
            constexpr forward_list& assign(std::initializer_list<T> values) noexcept;
            constexpr forward_list& assign(std::initializer_list<T> values) noexcept requires std::copyable<T>;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list& assign_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list& assign_range(R&& range) noexcept;

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

            // Capacity ------------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr bool empty(void) const noexcept;
            [[nodiscard]] constexpr size_t size(void) const noexcept;
            [[nodiscard]] constexpr size_t max_size(void) const noexcept;

            // Modifiers -----------------------------------------------------------------------------------------------
            
            constexpr forward_list& clear(void) noexcept;
            
            constexpr std::optional<T> insert(size_t position, const T& value) noexcept;
            constexpr std::optional<T> insert(size_t position, T&& value) noexcept;
            constexpr std::optional<forward_list> insert(size_t position, forward_list&& list) noexcept;
            constexpr std::optional<forward_list> insert(size_t position, const forward_list& list) noexcept;
            constexpr std::optional<forward_list> insert(size_t position, size_t count, const T& value) noexcept;
            constexpr std::optional<forward_list> insert(size_t position, std::initializer_list<T> list) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr std::optional<forward_list> insert_range(size_t position, const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr std::optional<forward_list> insert_range(size_t position, R&& range) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr std::optional<T> emplace(size_t position, Args&&... args) noexcept;

            constexpr std::optional<T> take(size_t position) noexcept;
            constexpr std::optional<forward_list> take(size_t first, size_t last) noexcept;
            constexpr size_t erase(size_t position) noexcept;
            constexpr size_t erase(size_t first, size_t last) noexcept;

            constexpr forward_list& push_back(const T& value) noexcept;
            constexpr forward_list& push_back(T&& value) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr forward_list& emplace_back(Args&&... args) noexcept;
            constexpr forward_list& append(const forward_list& value) noexcept;
            constexpr forward_list& append(forward_list&& value) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list& append_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list& append_range(R&& range) noexcept;

            constexpr forward_list& push_front(const T& value) noexcept;
            constexpr forward_list& push_front(T&& value) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr forward_list& emplace_front(Args&&... args) noexcept;
            constexpr forward_list& prepend(const forward_list& value) noexcept;
            constexpr forward_list& prepend(forward_list&& value) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list& prepend_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr forward_list& prepend_range(R&& range) noexcept;

            constexpr std::optional<T> pop_back(void) noexcept;
            constexpr std::optional<T> pop_front(void) noexcept;
            
            constexpr forward_list& resize(size_t size) noexcept;
            constexpr forward_list& resize(size_t size, const T& value) noexcept;

            constexpr forward_list& swap(forward_list& list) noexcept;

            // Operations ----------------------------------------------------------------------------------------------

            constexpr forward_list& merge(const forward_list& list) noexcept;
            constexpr forward_list& merge(forward_list&& list) noexcept;
            template<typename F>
            constexpr forward_list& merge(const forward_list& list, const F& cmp) noexcept;
            template<typename F>
            constexpr forward_list& merge(forward_list&& list, const F& cmp) noexcept;
            template<typename F>
            constexpr forward_list& merge(const forward_list& list, F&& cmp) noexcept;
            template<typename F>
            constexpr forward_list& merge(forward_list&& list, F&& cmp) noexcept;

            constexpr forward_list& splice(size_t position, forward_list& list) noexcept;
            constexpr std::optional<forward_list> splice(size_t position, forward_list&& list) noexcept;
            constexpr forward_list& splice(size_t position, forward_list& list, size_t from_position) noexcept;
            constexpr std::optional<forward_list> splice(size_t position, forward_list&& list, size_t from_position) noexcept;
            constexpr forward_list& splice(size_t position, forward_list& list, size_t from_first, size_t from_last) noexcept;
            constexpr std::optional<forward_list>
                splice(size_t position, forward_list&& list, size_t from_first, size_t from_last) noexcept;
            
            constexpr size_t remove(const T& value) noexcept;
            template<typename F>
            constexpr size_t remove_if(const F& predicate) noexcept;
            template<typename F>
            constexpr size_t remove_if(F&& predicate) noexcept;

            constexpr forward_list& reverse(void) noexcept;

            constexpr size_t unique(void) noexcept;
            template<typename F>
            constexpr size_t unique(const F& predicate) noexcept;
            template<typename F>
            constexpr size_t unique(F&& predicate) noexcept;

            constexpr forward_list& sort(void) noexcept;
            template<typename F> requires sss::comparison<F, T>
            constexpr forward_list& sort(const F& predicate) noexcept;
            template<typename F> requires sss::comparison<F, T>
            constexpr forward_list& sort(F&& predicate) noexcept;
            template<typename P> requires sss::execution_policy<P>
            constexpr forward_list& sort(P policy) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P> && sss::comparison<F, T>
            constexpr forward_list& sort(P policy, const F& predicate) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P> && sss::comparison<F, T>
            constexpr forward_list& sort(P policy, F&& predicate) noexcept;
            
        private:
            template<typename F> requires sss::comparison<F, T>
            constexpr forward_list& sort_par(const F& predicate, size_t threads) noexcept;
            template<typename F> requires sss::comparison<F, T>
            constexpr forward_list& sort_par(F&& predicate, size_t threads) noexcept;
        public:

            // Extra ---------------------------------------------------------------------------------------------------
            
            template<typename F>
            constexpr forward_list<std::invoke_result_t<F, T&&>> transform(const F& map) noexcept;
            template<typename F>
            constexpr forward_list<std::invoke_result_t<F, T&&>> transform(F&& map) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P>
            constexpr forward_list<std::invoke_result_t<F, T&&>> transform(P policy, const F& map) noexcept;
            template<typename P, typename F> requires sss::execution_policy<P>
            constexpr forward_list<std::invoke_result_t<F, T&&>> transform(P policy, F&& map) noexcept;

            template<typename U>
            template<typename F>
            friend constexpr forward_list<std::invoke_result_t<F, U&&>> forward_list<U>::transform(const F& map) noexcept;
            template<typename U>
            template<typename F>
            friend constexpr forward_list<std::invoke_result_t<F, U&&>> forward_list<U>::transform(F&& map) noexcept;

            // Operators -----------------------------------------------------------------------------------------------

            constexpr forward_list& operator=(const forward_list& list) noexcept;
            constexpr forward_list& operator=(forward_list&& list) noexcept;
            constexpr forward_list& operator=(std::initializer_list<T> values) noexcept;

        private:
            constexpr std::optional<std::reference_wrapper<link>> get_first_link(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const link>> get_first_link(void) const noexcept;
            
            constexpr std::optional<std::reference_wrapper<link>> get_last_link(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const link>> get_last_link(void) const noexcept;
    };
}

#include "forward_list/link.hpp"
#include "forward_list/const_iterator.hpp"
#include "forward_list/iterator.hpp"

#include "forward_list.cpp"