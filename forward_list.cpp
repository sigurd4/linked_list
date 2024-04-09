#include "forward_list.hpp"

#include <thread>

namespace sss
{
    template<typename T>
    constexpr forward_list<T>::forward_list(link&& first) noexcept:
        first {std::move(first)}
    {

    }
    template<typename T>
    constexpr forward_list<T>::forward_list(std::optional<link>&& first) noexcept:
        first {std::move(first)}
    {

    }
    template<typename T>
    constexpr forward_list<T>::forward_list(void) noexcept:
        first {std::nullopt}
    {

    }
    template<typename T>
    constexpr forward_list<T>::forward_list(size_t count, const T& value) noexcept:
        forward_list()
    {
        this->resize(count, value);
    }
    template<typename T>
    constexpr forward_list<T>::forward_list(size_t count) noexcept:
        forward_list()
    {
        this->resize(count);
    }
    template<typename T>
    constexpr forward_list<T>::forward_list(const forward_list& list) noexcept:
        forward_list()
    {
        if(list.first.has_value())
        {
            this->first = link(list.first.value());
        }
    }
    template<typename T>
    constexpr forward_list<T>::forward_list(forward_list&& list) noexcept:
        first {std::move(list.first)}
    {
        list.clear();
    }

    template<typename T>
    constexpr forward_list<T>::forward_list(std::initializer_list<T> values) noexcept:
        forward_list()
    {
        this->assign(values);
    }
    
#if _HAS_CXX23 && defined(__cpp_lib_concepts)
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>::forward_list(std::from_range_t, const R& range) noexcept:
        forward_list()
    {
        this->assign_range(range);
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>::forward_list(std::from_range_t, R&& range) noexcept:
        forward_list()
    {
        this->assign_range(range);
    }
#endif

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::assign(size_t count, const T& value) noexcept
    {
        return this->clear()
            .resize(count, value);
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::assign(std::initializer_list<T> values) noexcept
    {
        this->clear();

        std::optional<std::reference_wrapper<link>> last {};
        T* begin {const_cast<T*>(values.begin())};
        T* end {const_cast<T*>(values.end())};
        for(T* iter {begin}; iter != end; iter++)
        {
            T value {std::move(*iter)};

            if(!last.has_value())
            {
                this->first = std::move(value);
                last = {this->first.value()};
            }
            else
            {
                last = {last.value().get().append(std::move(value))};
            }
        }

        return *this;
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::assign(std::initializer_list<T> values) noexcept requires std::copyable<T>
    {
        this->clear();

        std::optional<std::reference_wrapper<link>> last {};
        for(T value : values)
        {
            if(!last.has_value())
            {
                this->first = std::move(value);
                last = {this->first.value()};
            }
            else
            {
                last = {last.value().get().append(std::move(value))};
            }
        }

        return *this;
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>& forward_list<T>::assign_range(const R& values) noexcept
    {
        this->clear();

        std::optional<std::reference_wrapper<link>> last {};
        for(T value : values)
        {
            if(!last.has_value())
            {
                std::optional<link> first {std::move(value)};
                this->first.swap(first);
                last = {this->first.value()};
            }
            else
            {
                last = {last.value().get().append(std::move(value))};
            }
        }

        return *this;
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>& forward_list<T>::assign_range(R&& values) noexcept
    {
        this->clear();

        std::optional<std::reference_wrapper<link>> last {};
        for(T& value : std::move(values))
        {
            if(!last.has_value())
            {
                std::optional<link> first {std::move(value)};
                this->first.swap(first);
                last = {this->first.value()};
            }
            else
            {
                last = {last.value().get().append(std::move(value))};
            }
        }

        return *this;
    }

    // Element access --------------------------------------------------------------------------------------------------
    
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> forward_list<T>::front(void) const noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        const link& last = this->first.value();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> forward_list<T>::front(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        link& last = this->first.value();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> forward_list<T>::back(void) const noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        const link& last = this->first.value().last_link();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> forward_list<T>::back(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        link& last = this->first.value().last_link();
        return {last.value};
    }

    // const_iteratorators -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::cbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr forward_list<T>::iterator forward_list<T>::begin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr forward_list<T>::iterator forward_list<T>::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr forward_list<T>::const_iterator forward_list<T>::end(void) const noexcept
    {
        return this->cend();
    }

    // Capacity --------------------------------------------------------------------------------------------------------
    
    template<typename T>
    constexpr bool forward_list<T>::empty(void) const noexcept
    {
        return !this->first.has_value();
    }
    template<typename T>
    constexpr size_t forward_list<T>::size(void) const noexcept
    {
        size_t n {0};
        for(const_iterator iter = this->cbegin(), end = this->cend(); iter != end; iter++)
        {
            n++;
        }
        return n;
    }
    template<typename T>
    constexpr size_t forward_list<T>::max_size(void) const noexcept
    {
        return std::numeric_limits<size_t>::max();
    }

    // Modifiers -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::clear(void) noexcept
    {
        this->first = {};
        return *this;
    }
    
    template<typename T>
    constexpr std::optional<T> forward_list<T>::insert(size_t position, const T& value) noexcept
    {
        return this->emplace(position, value);
    }
    template<typename T>
    constexpr std::optional<T> forward_list<T>::insert(size_t position, T&& value) noexcept
    {
        return this->emplace(position, std::move(value));
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::insert(size_t position, forward_list&& list) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
            if(current.has_value())
            {
                current.value().get().prepend(std::move(list));
                return {};
            }
            else
            {
                this->first = std::move(list.first);
                return {};
            }
        }
        iterator iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(std::move(list));
            return {};
        }
        return {std::move(list)};
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::insert(size_t position, const forward_list& list) noexcept
    {
        return this->insert(position, forward_list(list));
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::insert(size_t position, size_t count, const T& value) noexcept
    {
        return this->insert(position, forward_list(count, value));
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::insert(size_t position, std::initializer_list<T> values) noexcept
    {
        return this->insert(position, forward_list(values));
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr std::optional<forward_list<T>> forward_list<T>::insert_range(size_t position, const R& range) noexcept
    {
        forward_list list {};
        list.assign_range(range);
        return this->insert(position, std::move(list));
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr std::optional<forward_list<T>> forward_list<T>::insert_range(size_t position, R&& range) noexcept
    {
        forward_list list {};
        list.assign_range(std::move(range));
        return this->insert(position, std::move(list));
    }
    template<typename T>
    template<typename... Args> requires std::constructible_from<T, Args...>
    constexpr std::optional<T> forward_list<T>::emplace(size_t position, Args&&... args) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
            if(current.has_value())
            {
                current.value().get().prepend(link::make(std::move(args)...));
                return {};
            }
            else
            {
                this->first = link::make(std::move(args)...);
                return {};
            }
        }
        iterator iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(link::make(std::move(args)...));
            return {};
        }
        return {T(std::move(args)...)};
    }
    
    template<typename T>
    constexpr std::optional<T> forward_list<T>::take(size_t position) noexcept
    {
        iterator iter = this->begin();
        std::optional<std::reference_wrapper<link>> prev {};
        if(position > 0)
        {
            iter += position - 1;
            prev = iter.get_link();
            iter++;
        }
        std::optional<std::reference_wrapper<link>> current {iter.get_link()};
        if(current.has_value())
        {
            bool is_first = !prev.has_value();
            auto [pop, first] = current.value().get().pop(prev, prev, this->first.value());
            if(is_first)
            {
                this->first = std::move(first);
            }
            return std::move(pop.value);
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::take(size_t first, size_t last) noexcept
    {
        if(first > last)
        {
            std::swap(first, last);
        }
        iterator iter = this->begin();
        std::optional<std::reference_wrapper<link>> prev {};
        if(first > 0)
        {
            iter += first - 1;
            prev = iter.get_link();
            iter++;
        }
        std::optional<std::reference_wrapper<link>> current {iter.get_link()};
        if(current.has_value())
        {
            if(first == last)
            {
                return {};
            }
            std::optional<std::reference_wrapper<link>> direct_prev {prev};
            for(size_t i {first + 1}; i < last; i++)
            {
                iter++;
                std::optional<std::reference_wrapper<link>> next {iter.get_link()};
                if(!next.has_value())
                {
                    break;
                }
                direct_prev = current;
                current = next;
            }
            bool is_first = !prev.has_value();
            auto [pop, first] = current.value()
                .get()
                .pop(prev, direct_prev, this->first.value());
            if(is_first)
            {
                this->first = std::move(first);
            }
            forward_list o {std::move(pop)};
            return {std::move(o)};
        }
        return {};
    }
    template<typename T>
    constexpr size_t forward_list<T>::erase(size_t position) noexcept
    {
        std::optional<T> take {this->take(position)};
        if(take.has_value())
        {
            return 1;
        }
        return 0;
    }
    template<typename T>
    constexpr size_t forward_list<T>::erase(size_t first, size_t last) noexcept
    {
        if(first > last)
        {
            std::swap(first, last);
        }
        iterator iter = this->begin();
        std::optional<std::reference_wrapper<link>> prev {};
        if(first > 0)
        {
            iter += first - 1;
            prev = iter.get_link();
            iter++;
        }
        std::optional<std::reference_wrapper<link>> current {iter.get_link()};
        if(current.has_value())
        {
            if(first == last)
            {
                return 0;
            }
            size_t n {1};
            std::optional<std::reference_wrapper<link>> direct_prev {prev};
            for(size_t i {first + 1}; i < last; i++)
            {
                iter++;
                std::optional<std::reference_wrapper<link>> next {iter.get_link()};
                if(!next.has_value())
                {
                    break;
                }
                direct_prev = current;
                n++;
                current = next;
            }
            bool is_first = !prev.has_value();
            auto [_, first] = current.value()
                .get()
                .pop(prev, direct_prev, this->first.value());
            if(is_first)
            {
                this->first = std::move(first);
            }
            return n;
        }
        return 0;
    }
    
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::push_back(const T& value) noexcept
    {
        return this->emplace_back(value);
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::push_back(T&& value) noexcept
    {
        return this->emplace_back(std::move(value));
    }
    template<typename T>
    template<typename... Args> requires std::constructible_from<T, Args...>
    constexpr forward_list<T>& forward_list<T>::emplace_back(Args&&... args) noexcept
    {
        if(!this->first.has_value())
        {
            std::optional<link> first {link::make(std::move(args)...)};
            this->first.swap(first);
            return *this;
        }
        link& last = this->first.value().last_link();
        last.append(link::make(std::move(args)...));
        return *this;
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::append(const forward_list& list) noexcept
    {
        return this->append(forward_list(list));
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::append(forward_list&& list) noexcept
    {
        if(!list.first.has_value())
        {
            return *this;
        }
        if(!this->first.has_value())
        {
            this->first = std::move(list.first);
            return *this;
        }
        link& last = this->first.value().last_link();
        last.append(std::move(list.first.value()));
        return *this;
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>& forward_list<T>::append_range(R&& range) noexcept
    {
        forward_list list {};
        list.assign_range(std::move(range));
        return this->append(std::move(list));
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>& forward_list<T>::append_range(const R& range) noexcept
    {
        forward_list list {};
        list.assign_range(range);
        return this->append(std::move(list));
    }

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::push_front(const T& value) noexcept
    {
        return this->emplace_front(value);
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::push_front(T&& value) noexcept
    {
        return this->emplace_front(std::move(value));
    }
    template<typename T>
    template<typename... Args> requires std::constructible_from<T, Args...>
    constexpr forward_list<T>& forward_list<T>::emplace_front(Args&&... args) noexcept
    {
        if(!this->first.has_value())
        {
            std::optional<link> first {link::make(std::move(args)...)};
            this->first.swap(first);
            return *this;
        }
        this->first.value().prepend(link::make(std::move(args)...));
        return *this;
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::prepend(const forward_list& list) noexcept
    {
        return this->prepend(forward_list(list));
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::prepend(forward_list&& list) noexcept
    {
        if(!list.first.has_value())
        {
            return *this;
        }
        if(!this->first.has_value())
        {
            this->first = std::move(list.first);
            return *this;
        }
        this->first.value().prepend(std::move(list.first.value()));
        return *this;
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>& forward_list<T>::prepend_range(R&& range) noexcept
    {
        forward_list list {};
        list.assign_range(std::move(range));
        return this->prepend(std::move(list));
    }
    template<typename T>
    template<typename R> requires std::ranges::range<R>
    constexpr forward_list<T>& forward_list<T>::prepend_range(const R& range) noexcept
    {
        forward_list list {};
        list.assign_range(range);
        return this->prepend(std::move(list));
    }

    template<typename T>
    constexpr std::optional<T> forward_list<T>::pop_back(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        link& first = this->first.value();
        auto [second_last, last] = first.last_two_links();

        bool empty = !second_last.has_value();
        auto [pop, _] = last.pop(second_last, last, first);
        T value = std::move(pop.value);
        if(empty)
        {
            this->first = {};
        }
        return {std::move(value)};
    }
    template<typename T>
    constexpr std::optional<T> forward_list<T>::pop_front(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        auto [pop, first] = this->first.value().pop({}, {}, this->first.value());
        T value = std::move(pop.value);
        this->first = std::move(first);

        return {std::move(value)};
    }

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::resize(size_t size) noexcept
    {
        std::optional<std::reference_wrapper<link>> last = this->get_first_link();
        size_t i = 0;
        if(last.has_value())
        {
            i++;
            for(; i < size; i++)
            {
                std::optional<std::reference_wrapper<link>> next = last.value().get().next_link();
                if(!next.has_value())
                {
                    break;
                }
                last = next;
            }
            last.value().get().next = {};
        }
        for(; i < size; i++)
        {
            if(!last.has_value())
            {
                std::optional<link> first {link::make()};
                this->first.swap(first);
                last = this->get_first_link();
                continue;
            }
            last.value().get().append(link::make());
            last = last.value().get().next_link();
        }
        return *this;
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::resize(size_t size, const T& value) noexcept
    {
        std::optional<std::reference_wrapper<link>> last = this->get_first_link();
        size_t i = 0;
        if(last.has_value())
        {
            i++;
            for(; i < size; i++)
            {
                std::optional<std::reference_wrapper<link>> next = last.value().get().next_link();
                if(!next.has_value())
                {
                    break;
                }
                last = next;
            }
            last.value().get().next = {};
        }
        for(; i < size; i++)
        {
            if(!last.has_value())
            {
                std::optional<link> first {link::make(value)};
                this->first.swap(first);
                last = this->get_first_link();
                continue;
            }
            last.value().get().append(link::make(value));
            last = last.value().get().next_link();
        }
        return *this;
    }

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::swap(forward_list& list) noexcept
    {
        this->first.swap(list.first);
        return *this;
    }

    // Operations ------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::merge(const forward_list& list) noexcept
    {
        return this->merge(forward_list(list));
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::merge(forward_list&& list) noexcept
    {
        return this->merge(std::move(list), [](const T& a, const T& b) {
            return a < b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr forward_list<T>& forward_list<T>::merge(const forward_list& list, F&& cmp) noexcept
    {
        return this->merge(forward_list(list), std::move(cmp));
    }
    template<typename T>
    template<typename F>
    constexpr forward_list<T>& forward_list<T>::merge(forward_list&& list, F&& cmp) noexcept
    {
        if(list.empty())
        {
            return *this;
        }
        if(this->empty())
        {
            std::swap(*this, list);
            return *this;
        }

        if(cmp(list.front().value(), this->front().value()))
        {
            std::swap(*this, list);
        }
        std::optional<std::reference_wrapper<link>> next = this->first.value().next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(list.first.value()), std::move(cmp));
        }
        else
        {
            std::optional<std::unique_ptr<link>> b {std::make_unique<link>(std::move(list.first.value()))};
            this->first.value().next.swap(b);
        }
        return *this;
    }
    template<typename T>
    template<typename F>
    constexpr forward_list<T>& forward_list<T>::merge(const forward_list& list, const F& cmp) noexcept
    {
        return this->merge(list(list), cmp);
    }
    template<typename T>
    template<typename F>
    constexpr forward_list<T>& forward_list<T>::merge(forward_list&& list, const F& cmp) noexcept
    {
        if(list.empty())
        {
            return *this;
        }
        if(this->empty())
        {
            std::swap(*this, list);
            return *this;
        }

        if(cmp(list.front().value(), this->front().value()))
        {
            std::swap(*this, list);
        }
        std::optional<std::reference_wrapper<link>> next = this->first.value().next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(list.first.value()), cmp);
        }
        else
        {
            std::optional<std::unique_ptr<link>> b {std::make_unique<link>(std::move(list.first.value()))};
            this->first.value().next.swap(b);
        }
        return *this;
    }

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::splice(size_t position, forward_list& list) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
            if(current.has_value())
            {
                current.value().get().prepend(std::move(list));
                list.clear();
                return *this;
            }
            else
            {
                this->first = std::move(list.first);
                list.clear();
                return *this;
            }
        }
        iterator iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(std::move(list));
            list.clear();
        }
        return *this;
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::splice(size_t position, forward_list&& list) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
            if(current.has_value())
            {
                current.value().get().prepend(std::move(list));
                return {};
            }
            else
            {
                this->first = std::move(list.first);
                return {};
            }
        }
        iterator iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(std::move(list));
            return {};
        }
        return {std::move(list)};
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::splice(size_t position, forward_list& list, size_t from_position) noexcept
    {
        return this->splice(position, list, from_position, from_position + 1);
    }
    template<typename T>
    constexpr std::optional<forward_list<T>> forward_list<T>::splice(size_t position, forward_list&& list, size_t from_position) noexcept
    {
        return this->splice(position, std::move(list), from_position, from_position + 1);
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::splice(size_t position, forward_list& list, size_t from_first, size_t from_last) noexcept
    {
        if(position > this->size())
        {
            return *this;
        }
        std::optional<forward_list> splice = list.take(from_first, from_last);
        if(splice.has_value())
        {
            this->splice(position, std::move(splice.value()));
        }
        return *this;
    }
    template<typename T>
    constexpr std::optional<forward_list<T>>
        forward_list<T>::splice(size_t position, forward_list&& list, size_t from_first, size_t from_last) noexcept
    {
        if(position > this->size())
        {
            return {std::move(list)};
        }
        std::optional<forward_list> splice = list.take(from_first, from_last);
        if(splice.has_value())
        {
            return this->splice(position, std::move(splice.value()));
        }
        return {std::move(list)};
    }

    template<typename T>
    constexpr size_t forward_list<T>::remove(const T& value) noexcept
    {
        return this->remove_if([value](const T& x) {
            return x == value;
        });
    }
    template<typename T>
    template<typename F>
    constexpr size_t forward_list<T>::remove_if(const F& predicate) noexcept
    {
        std::optional<std::reference_wrapper<link>> prev {};
        std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
        size_t n = 0;
        while(true)
        {
            if(!current.has_value())
            {
                break;
            }
            if(predicate(current.value().get().value))
            {
                bool is_first = !prev.has_value();
                auto [_, first] = current.value().get().pop(prev, prev, this->first.value());
                if(is_first)
                {
                    this->first = first;
                    current = this->get_first_link();
                }
                else
                {
                    current = prev.value().get().next_link();
                }
            }
            else
            {
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }
    template<typename T>
    template<typename F>
    constexpr size_t forward_list<T>::remove_if(F&& predicate) noexcept
    {
        std::optional<std::reference_wrapper<link>> prev {};
        std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
        size_t n = 0;
        while(true)
        {
            if(!current.has_value())
            {
                break;
            }
            if(predicate(current.value().get().value))
            {
                bool is_first = !prev.has_value();
                auto [_, first] = current.value().get().pop(prev, prev, this->first.value());
                if(is_first)
                {
                    this->first = std::move(first);
                    current = this->get_first_link();
                }
                else
                {
                    current = prev.value().get().next_link();
                }
            }
            else
            {
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::reverse(void) noexcept
    {
        forward_list r {};
        std::swap(r, *this);
        while(true)
        {
            std::optional<T> pop = r.pop_front();
            if(!pop.has_value())
            {
                break;
            }
            this->push_front(std::move(pop.value()));
        }
        return *this;
    }

    template<typename T>
    constexpr size_t forward_list<T>::unique(void) noexcept
    {
        return this->unique([](const T& a, const T& b) {
            return a == b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr size_t forward_list<T>::unique(const F& predicate) noexcept
    {
        forward_list<std::reference_wrapper<const T>> found {};
        
        std::optional<std::reference_wrapper<link>> prev {};
        std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
        size_t n = 0;
        while(true)
        {
            if(!current.has_value())
            {
                break;
            }
            const T& value {current.value().get().value};
            bool is_found {false};
            bool should_delete {false};
            for(const T& f : found)
            {
                if(f == value)
                {
                    is_found = true;
                }
                if(predicate(value, f))
                {
                    should_delete = true;
                }
            }
            if(should_delete)
            {
                bool is_first = !prev.has_value();
                auto [_, first] = current.value().get().pop(prev, prev, this->first.value());
                if(is_first)
                {
                    this->first = std::move(first);
                    current = this->get_first_link();
                }
                else
                {
                    current = prev.value().get().next_link();
                }
            }
            else
            {
                if(!is_found)
                {
                    found.push_front(value);
                }
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }
    template<typename T>
    template<typename F>
    constexpr size_t forward_list<T>::unique(F&& predicate) noexcept
    {
        forward_list<std::reference_wrapper<const T>> found {};
        
        std::optional<std::reference_wrapper<link>> prev {};
        std::optional<std::reference_wrapper<link>> current {this->get_first_link()};
        size_t n = 0;
        while(true)
        {
            if(!current.has_value())
            {
                break;
            }
            const T& value {current.value().get().value};
            bool is_found {false};
            bool should_delete {false};
            for(const T& f : found)
            {
                if(f == value)
                {
                    is_found = true;
                }
                if(predicate(value, f))
                {
                    should_delete = true;
                }
            }
            if(should_delete)
            {
                bool is_first = !prev.has_value();
                auto [_, first] = current.value().get().pop(prev, prev, this->first.value());
                if(is_first)
                {
                    this->first = std::move(first);
                    current = this->get_first_link();
                }
                else
                {
                    current = prev.value().get().next_link();
                }
            }
            else
            {
                if(!is_found)
                {
                    found.push_front(value);
                }
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::sort(void) noexcept
    {
        return this->sort(std::execution::seq);
    }
    template<typename T>
    template<typename F> requires sss::comparison<F, T>
    constexpr forward_list<T>& forward_list<T>::sort(const F& predicate) noexcept
    {
        return this->sort(std::execution::seq, predicate);
    }
    template<typename T>
    template<typename F> requires sss::comparison<F, T>
    constexpr forward_list<T>& forward_list<T>::sort(F&& predicate) noexcept
    {
        return this->sort(std::execution::seq, std::move(predicate));
    }
    template<typename T>
    template<typename P> requires sss::execution_policy<P>
    constexpr forward_list<T>& forward_list<T>::sort(P policy) noexcept
    {
        return this->sort(policy, std::less<T> {});
    }
    template<typename T>
    template<typename P, typename F> requires sss::execution_policy<P> && sss::comparison<F, T>
    constexpr forward_list<T>& forward_list<T>::sort(P policy, const F& predicate) noexcept
    {
        // Do nothing if length is 0 or 1
        if(!this->first.has_value() || !this->first.value().next_link().has_value())
        {
            return *this;
        }

        // Split in halves
        forward_list b {this->first.value().split_in_half()};

        // Sort each half
        if constexpr (sss::par_execution_policy<P>)
        {
            std::thread t1 {[&] () {
                b.sort(policy, predicate);
            }};
            this->sort(policy, predicate);
            t1.join();
        }
        else
        {
            this->sort(policy, predicate);
            b.sort(policy, predicate);
        }

        // Merge halves
        return this->merge(std::move(b), predicate);
    }
    template<typename T>
    template<typename P, typename F> requires sss::execution_policy<P> && sss::comparison<F, T>
    constexpr forward_list<T>& forward_list<T>::sort(P policy, F&& predicate) noexcept
    {
        // Do nothing if length is 0 or 1
        if(!this->first.has_value() || !this->first.value().next_link().has_value())
        {
            return *this;
        }

        // Split in halves
        forward_list b {this->first.value().split_in_half()};

        // Sort each half
        if constexpr (sss::par_execution_policy<P>)
        {
            std::thread t1 {[&] () {
                b.sort(policy, predicate);
            }};
            this->sort(policy, predicate);
            t1.join();
        }
        else
        {
            this->sort(policy, predicate);
            b.sort(policy, predicate);
        }

        // Merge halves
        return this->merge(std::move(b), predicate);
    }

    // Extra -----------------------------------------------------------------------------------------------------------

    template<typename T>
    template<typename F>
    constexpr forward_list<std::invoke_result_t<F, T&&>> forward_list<T>::transform(const F& map) noexcept
    {
        forward_list<std::invoke_result_t<F, T&&>> o {};
        auto last {o.get_first_link()};

        while(true)
        {
            std::optional<T> pop {this->pop_front()};
            if(!pop.has_value())
            {
                break;
            }
            auto value {map(std::move(pop.value()))};
            if(!last.has_value())
            {
                o.first = std::move(value);
                last = o.get_first_link();
                continue;
            }
            last.value().get().append(std::move(value));
            last = last.value().get().next_link();
        }

        return o;
    }
    template<typename T>
    template<typename F>
    constexpr forward_list<std::invoke_result_t<F, T&&>> forward_list<T>::transform(F&& map) noexcept
    {
        forward_list<std::invoke_result_t<F, T&&>> o {};
        auto last {o.get_first_link()};

        while(true)
        {
            std::optional<T> pop {this->pop_front()};
            if(!pop.has_value())
            {
                break;
            }
            auto value {map(std::move(pop.value()))};
            if(!last.has_value())
            {
                o.first = std::move(value);
                last = o.get_first_link();
                continue;
            }
            last.value().get().append(std::move(value));
            last = last.value().get().next_link();
        }

        return o;
    }
    template<typename T>
    template<typename P, typename F> requires sss::execution_policy<P>
    constexpr forward_list<std::invoke_result_t<F, T&&>> forward_list<T>::transform(P policy, const F& map) noexcept
    {
        if constexpr (!sss::par_execution_policy<P>)
        {
            return this->transform(map);
        }

        return this->transform([&] (T&& x) {
            return std::async([&] () {
                return map(std::move(x));
            });
        }).transform([](std::future<std::invoke_result_t<F, T&&>> y) {
            return y.get();
        });
    }
    template<typename T>
    template<typename P, typename F> requires sss::execution_policy<P>
    constexpr forward_list<std::invoke_result_t<F, T&&>> forward_list<T>::transform(P policy, F&& map) noexcept
    {
        if constexpr (!sss::par_execution_policy<P>)
        {
            return this->transform(map);
        }

        return this->transform([&] (T&& x) {
            return std::async([&] (T&& x) {
                return map(std::move(x));
            }, std::move(x));
        }).transform([](std::future<std::invoke_result_t<F, T&&>> y) {
            return y.get();
        });
    }

    // Operators -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr forward_list<T>& forward_list<T>::operator=(const forward_list& list) noexcept
    {
        if(list.first.has_value())
        {
            this->first = link{list.first.value()};
        }
        else
        {
            this->first = {};
        }
        return *this;
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::operator=(forward_list&& list) noexcept
    {
        this->clear();
        this->first = std::move(list.first);
        list.clear();
        return *this;
    }
    template<typename T>
    constexpr forward_list<T>& forward_list<T>::operator=(std::initializer_list<T> values) noexcept
    {
        this->assign(values);
        return *this;
    }

    template<typename T>
    constexpr bool operator==(const forward_list<T>& a, const forward_list<T>& b) noexcept
    {
        if(a.size() != b.size())
        {
            return false;
        }

        auto iter1 {a.cbegin()};
        auto iter2 {b.cbegin()};

        while(true)
        {
            std::optional<std::reference_wrapper<const T>> next1 {iter1.next()};
            std::optional<std::reference_wrapper<const T>> next2 {iter2.next()};

            if(!(next1 == next2))
            {
                return false;
            }
            if(!next1.has_value() || !next2.has_value())
            {
                break;
            }
        }
        return true;
    }

    template<typename T>
    constexpr std::compare_three_way_result<T, T>::type operator<=>(const forward_list<T>& a, const forward_list<T>& b) noexcept
    {
        auto iter1 {a.cbegin()};
        auto iter2 {b.cbegin()};

        while(true)
        {
            std::optional<std::reference_wrapper<const T>> next1 {iter1.next()};
            std::optional<std::reference_wrapper<const T>> next2 {iter2.next()};

            bool e1 {next1.has_value()};
            bool e2 {next2.has_value()};
            if(e1 && e2)
            {
                auto cmp {next1.value() <=> next2.value()};
                if(!(cmp == 0))
                {
                    return cmp;
                }
            }
            if(e1 && !e2)
            {
                return std::compare_three_way_result<T, T>::type::greater;
            }
            if(!e1 && e2)
            {
                return std::compare_three_way_result<T, T>::type::less;
            }
            if(!e1 && !e2)
            {
                return std::compare_three_way_result<T, T>::type::equivalent;
            }
        }
    }

    // Private ---------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename forward_list<T>::link>> forward_list<T>::get_first_link(void) noexcept
    {
        return this->first.transform([](link& link) {
            return std::ref(link);
        });
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename forward_list<T>::link>>
        forward_list<T>::get_first_link(void) const noexcept
    {
        return this->first.transform([](const link& link) {
            return std::cref(link);
        });
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename forward_list<T>::link>> forward_list<T>::get_last_link(void) noexcept
    {
        return this->first.transform([](link& link) {
            return std::ref(link.last_link());
        });
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename forward_list<T>::link>> forward_list<T>::get_last_link(void) const noexcept
    {
        return this->first.transform([](const link& link) {
            return std::cref(link.last_link());
        });
    }
}
