#pragma once

#include <optional>
#include <memory>

namespace sss
{
    template<typename T>
    class ListFwd
    {
        private:
            class Link;

        public:
            class Iter;
            class IterMut;

        private:
            std::optional<Link> first;

            constexpr ListFwd(Link&& first) noexcept;
            constexpr ListFwd(std::optional<Link>&& first) noexcept;
        public:
            constexpr ListFwd(void) noexcept;
            constexpr ListFwd(size_t count, const T& value) noexcept;
            constexpr explicit ListFwd(size_t count) noexcept;
            constexpr ListFwd(const ListFwd& list) noexcept;
            constexpr ListFwd(ListFwd&& list) noexcept;
            constexpr ListFwd(std::initializer_list<T> values) noexcept;
#if _HAS_CXX23 && defined(__cpp_lib_concepts)
            template<typename R>
            constexpr ListFwd(std::from_range_t, const R& range) noexcept;
            template<typename R>
            constexpr ListFwd(std::from_range_t, R&& range) noexcept;
#endif

            constexpr void assign(size_t count, const T& value) noexcept;
            constexpr void assign(std::initializer_list<T> values) noexcept;
            template<typename R>
            constexpr void assign_range(const R& range) noexcept;
            template<typename R>
            constexpr void assign_range(R&& range) noexcept;

            // Element access ------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr std::optional<std::reference_wrapper<const T>> front(void) const noexcept;
            [[nodiscard]] constexpr std::optional<std::reference_wrapper<T>> front(void) noexcept;
            [[nodiscard]] constexpr std::optional<std::reference_wrapper<const T>> back(void) const noexcept;
            [[nodiscard]] constexpr std::optional<std::reference_wrapper<T>> back(void) noexcept;
            
            // Iterators -----------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr Iter cbegin(void) const noexcept;
            [[nodiscard]] constexpr Iter cend(void) const noexcept;
            [[nodiscard]] constexpr IterMut begin(void) noexcept;
            [[nodiscard]] constexpr IterMut end(void) noexcept;
            [[nodiscard]] constexpr Iter begin(void) const noexcept;
            [[nodiscard]] constexpr Iter end(void) const noexcept;

            // Capacity ------------------------------------------------------------------------------------------------

            [[nodiscard]] constexpr bool empty(void) const noexcept;
            [[nodiscard]] constexpr size_t size(void) const noexcept;
            [[nodiscard]] constexpr size_t max_size(void) const noexcept;

            // Modifiers -----------------------------------------------------------------------------------------------
            
            constexpr void clear(void) noexcept;
            
            constexpr std::optional<T> insert(size_t position, const T& value) noexcept;
            constexpr std::optional<T> insert(size_t position, T&& value) noexcept;
            constexpr std::optional<ListFwd> insert(size_t position, ListFwd&& list) noexcept;
            constexpr std::optional<ListFwd> insert(size_t position, const ListFwd& list) noexcept;
            constexpr std::optional<ListFwd> insert(size_t position, size_t count, const T& value) noexcept;
            constexpr std::optional<ListFwd> insert(size_t position, std::initializer_list<T> list) noexcept;
            template<typename R>
            constexpr std::optional<ListFwd> insert_range(size_t position, const R& range) noexcept;
            template<typename R>
            constexpr std::optional<ListFwd> insert_range(size_t position, R&& range) noexcept;
            template<typename... Args>
            constexpr std::optional<T> emplace(size_t position, Args&&... args) noexcept;

            constexpr std::optional<T> take(size_t position) noexcept;
            constexpr std::optional<ListFwd> take(size_t first, size_t last) noexcept;
            constexpr size_t erase(size_t position) noexcept;
            constexpr size_t erase(size_t first, size_t last) noexcept;

            constexpr void push_back(const T& value) noexcept;
            constexpr void push_back(T&& value) noexcept;
            template<typename... Args>
            constexpr void emplace_back(Args&&... args) noexcept;
            constexpr void append(const ListFwd& value) noexcept;
            constexpr void append(ListFwd&& value) noexcept;
            template<typename R>
            constexpr void append_range(const R& range) noexcept;
            template<typename R>
            constexpr void append_range(R&& range) noexcept;

            constexpr void push_front(const T& value) noexcept;
            constexpr void push_front(T&& value) noexcept;
            template<typename... Args>
            constexpr void emplace_front(Args&&... args) noexcept;
            constexpr void prepend(const ListFwd& value) noexcept;
            constexpr void prepend(ListFwd&& value) noexcept;
            template<typename R>
            constexpr void prepend_range(const R& range) noexcept;
            template<typename R>
            constexpr void prepend_range(R&& range) noexcept;

            constexpr std::optional<T> pop_back(void) noexcept;
            constexpr std::optional<T> pop_front(void) noexcept;
            
            constexpr void resize(size_t size) noexcept;
            constexpr void resize(size_t size, const T& value) noexcept;

            constexpr void swap(ListFwd& list) noexcept;

            // Operations ----------------------------------------------------------------------------------------------

            constexpr void merge(const ListFwd& list) noexcept;
            constexpr void merge(ListFwd&& list) noexcept;
            template<typename F>
            constexpr void merge(const ListFwd& list, const F& cmp) noexcept;
            template<typename F>
            constexpr void merge(ListFwd&& list, const F& cmp) noexcept;
            template<typename F>
            constexpr void merge(const ListFwd& list, F&& cmp) noexcept;
            template<typename F>
            constexpr void merge(ListFwd&& list, F&& cmp) noexcept;

            constexpr void splice(size_t position, ListFwd& list) noexcept;
            constexpr std::optional<ListFwd> splice(size_t position, ListFwd&& list) noexcept;
            constexpr void splice(size_t position, ListFwd& list, size_t from_position) noexcept;
            constexpr std::optional<ListFwd> splice(size_t position, ListFwd&& list, size_t from_position) noexcept;
            constexpr void splice(size_t position, ListFwd& list, size_t from_first, size_t from_last) noexcept;
            constexpr std::optional<ListFwd>
                splice(size_t position, ListFwd&& list, size_t from_first, size_t from_last) noexcept;
            
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

            // Operators -----------------------------------------------------------------------------------------------

            constexpr ListFwd& operator=(const ListFwd& list) noexcept;
            constexpr ListFwd& operator=(ListFwd&& list) noexcept;
            constexpr ListFwd& operator=(std::initializer_list<T> values) noexcept;

        private:
            constexpr std::optional<std::reference_wrapper<Link>> get_first_link(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const Link>> get_first_link(void) const noexcept;
            
            constexpr std::optional<std::reference_wrapper<Link>> get_last_link(void) noexcept;
            constexpr std::optional<std::reference_wrapper<const Link>> get_last_link(void) const noexcept;
    };
}

#include "forward_list/link.hpp"
#include "forward_list/iter.hpp"
#include "forward_list/iter_mut.hpp"

#include "forward_list.cpp"