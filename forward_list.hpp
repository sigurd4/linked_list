#pragma once

#include <optional>
#include <memory>

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

            constexpr void assign(size_t count, const T& value) noexcept;
            constexpr void assign(std::initializer_list<T> values) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr void assign_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr void assign_range(R&& range) noexcept;

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
            
            constexpr void clear(void) noexcept;
            
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

            constexpr void push_back(const T& value) noexcept;
            constexpr void push_back(T&& value) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr void emplace_back(Args&&... args) noexcept;
            constexpr void append(const forward_list& value) noexcept;
            constexpr void append(forward_list&& value) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr void append_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr void append_range(R&& range) noexcept;

            constexpr void push_front(const T& value) noexcept;
            constexpr void push_front(T&& value) noexcept;
            template<typename... Args> requires std::constructible_from<T, Args...>
            constexpr void emplace_front(Args&&... args) noexcept;
            constexpr void prepend(const forward_list& value) noexcept;
            constexpr void prepend(forward_list&& value) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr void prepend_range(const R& range) noexcept;
            template<typename R> requires std::ranges::range<R>
            constexpr void prepend_range(R&& range) noexcept;

            constexpr std::optional<T> pop_back(void) noexcept;
            constexpr std::optional<T> pop_front(void) noexcept;
            
            constexpr void resize(size_t size) noexcept;
            constexpr void resize(size_t size, const T& value) noexcept;

            constexpr void swap(forward_list& list) noexcept;

            // Operations ----------------------------------------------------------------------------------------------

            constexpr void merge(const forward_list& list) noexcept;
            constexpr void merge(forward_list&& list) noexcept;
            template<typename F>
            constexpr void merge(const forward_list& list, const F& cmp) noexcept;
            template<typename F>
            constexpr void merge(forward_list&& list, const F& cmp) noexcept;
            template<typename F>
            constexpr void merge(const forward_list& list, F&& cmp) noexcept;
            template<typename F>
            constexpr void merge(forward_list&& list, F&& cmp) noexcept;

            constexpr void splice(size_t position, forward_list& list) noexcept;
            constexpr std::optional<forward_list> splice(size_t position, forward_list&& list) noexcept;
            constexpr void splice(size_t position, forward_list& list, size_t from_position) noexcept;
            constexpr std::optional<forward_list> splice(size_t position, forward_list&& list, size_t from_position) noexcept;
            constexpr void splice(size_t position, forward_list& list, size_t from_first, size_t from_last) noexcept;
            constexpr std::optional<forward_list>
                splice(size_t position, forward_list&& list, size_t from_first, size_t from_last) noexcept;
            
            constexpr size_t remove(const T& value) noexcept;
            template<typename F>
            constexpr size_t remove_if(const F& predicate) noexcept;
            template<typename F>
            constexpr size_t remove_if(F&& predicate) noexcept;

            constexpr void reverse(void) noexcept;

            constexpr size_t unique(void) noexcept;
            template<typename F>
            constexpr size_t unique(const F& predicate) noexcept;
            template<typename F>
            constexpr size_t unique(F&& predicate) noexcept;

            constexpr void sort(void) noexcept;
            template<typename F>
            constexpr void sort(const F& predicate) noexcept;
            template<typename F>
            constexpr void sort(F&& predicate) noexcept;

            // Extra ---------------------------------------------------------------------------------------------------
            
            template<typename U, typename F> requires std::is_function_v<F>
            constexpr forward_list<U> transform(const F& map) noexcept;
            template<typename U, typename F> requires std::is_function_v<F>
            constexpr forward_list<U> transform(F&& map) noexcept;

            template<typename U>
            template<typename V, typename F> requires std::is_function_v<F>
            friend constexpr forward_list<V> forward_list<U>::transform(const F& map) noexcept;
            template<typename U>
            template<typename V, typename F> requires std::is_function_v<F>
            friend constexpr forward_list<V> forward_list<U>::transform(F&& map) noexcept;

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