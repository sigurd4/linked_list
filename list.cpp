#include "list.hpp"

namespace sss
{
    template<typename T>
    constexpr List<T>::List(Link&& first) noexcept:
        first {std::move(first)}
    {

    }
    template<typename T>
    constexpr List<T>::List(std::optional<Link>&& first) noexcept:
        first {std::move(first)}
    {

    }
    template<typename T>
    constexpr List<T>::List(void) noexcept:
        first {std::nullopt}
    {

    }
    template<typename T>
    constexpr List<T>::List(size_t count, const T& value) noexcept:
        List()
    {
        this->resize(count, value);
    }
    template<typename T>
    constexpr List<T>::List(size_t count) noexcept:
        List()
    {
        this->resize(count);
    }
    template<typename T>
    constexpr List<T>::List(const List& list) noexcept:
        List()
    {
        if(list.first.has_value())
        {
            this->first = Link(list.first.value(), {});
        }
    }
    template<typename T>
    constexpr List<T>::List(List&& list) noexcept:
        first {std::move(list.first)}
    {
        list.clear();
    }
    template<typename T>
    constexpr List<T>::List(std::initializer_list<T> values) noexcept:
        List()
    {
        this->assign(values);
    }

#if _HAS_CXX23 && defined(__cpp_lib_concepts)
    template<typename T>
    template<typename R>
    constexpr List<T>::List(std::from_range_t, const R& range) noexcept:
        List()
    {
        this->assign_range(range);
    }
    template<typename T>
    template<typename R>
    constexpr List<T>::List(std::from_range_t, R&& range) noexcept:
        List()
    {
        this->assign_range(range);
    }
#endif
    
    template<typename T>
    constexpr void List<T>::assign(size_t count, const T& value) noexcept
    {
        this->clear();
        this->resize(count, value);
    }
    template<typename T>
    constexpr void List<T>::assign(std::initializer_list<T> values) noexcept
    {
        this->clear();

        std::optional<std::reference_wrapper<Link>> last {};
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
    }
    template<typename T>
    template<typename R>
    constexpr void List<T>::assign_range(const R& values) noexcept
    {
        this->clear();

        std::optional<std::reference_wrapper<Link>> last {};
        for(T value : values)
        {
            if(!last.has_value())
            {
                std::optional<Link> first {std::move(value)};
                this->first.swap(first);
                last = {this->first.value()};
            }
            else
            {
                last = {last.value().get().append(std::move(value))};
            }
        }
    }
    template<typename T>
    template<typename R>
    constexpr void List<T>::assign_range(R&& values) noexcept
    {
        this->clear();

        std::optional<std::reference_wrapper<Link>> last {};
        for(T& value : std::move(values))
        {
            if(!last.has_value())
            {
                std::optional<Link> first {std::move(value)};
                this->first.swap(first);
                last = {this->first.value()};
            }
            else
            {
                last = {last.value().get().append(std::move(value))};
            }
        }
    }

    // Element access --------------------------------------------------------------------------------------------------
    
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> List<T>::front(void) const noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        const Link& last = this->first.value();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> List<T>::front(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        Link& last = this->first.value();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> List<T>::back(void) const noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        const Link& last = this->first.value().last_link();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> List<T>::back(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        Link& last = this->first.value().last_link();
        return {last.value};
    }

    // Iterators -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr List<T>::Iter List<T>::cbegin(void) const noexcept
    {
        return {*this, false};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::begin(void) noexcept
    {
        return {*this, false};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::end(void) const noexcept
    {
        return this->cend();
    }
    
    template<typename T>
    constexpr List<T>::Iter List<T>::crbegin(void) const noexcept
    {
        return {*this, true};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::crend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::rbegin(void) noexcept
    {
        return {*this, true};
    }
    template<typename T>
    constexpr List<T>::IterMut List<T>::rend(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::rbegin(void) const noexcept
    {
        return this->crbegin();
    }
    template<typename T>
    constexpr List<T>::Iter List<T>::rend(void) const noexcept
    {
        return this->crend();
    }

    // Capacity --------------------------------------------------------------------------------------------------------
    
    template<typename T>
    constexpr bool List<T>::empty(void) const noexcept
    {
        return !this->first.has_value();
    }
    template<typename T>
    constexpr size_t List<T>::size(void) const noexcept
    {
        size_t n {0};
        for(Iter iter = this->cbegin(), end = this->cend(); iter != end; iter++)
        {
            n++;
        }
        return n;
    }
    template<typename T>
    constexpr size_t List<T>::max_size(void) const noexcept
    {
        return std::numeric_limits<size_t>::max();
    }

    // Modifiers -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr void List<T>::clear(void) noexcept
    {
        this->first = {};
    }

    template<typename T>
    constexpr std::optional<T> List<T>::insert(size_t position, const T& value) noexcept
    {
        return this->emplace(position, value);
    }
    template<typename T>
    constexpr std::optional<T> List<T>::insert(size_t position, T&& value) noexcept
    {
        return this->emplace(position, std::move(value));
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::insert(size_t position, List&& list) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
            if(current.has_value())
            {
                if(list.first.has_value())
                {
                    current.value().get().prepend(std::move(list.first.value()));
                }
                return {};
            }
            else
            {
                if(list.first.has_value())
                {
                    this->first = std::move(list.first.value());
                }
                return {};
            }
        }
        IterMut iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<Link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            if(list.first.has_value())
            {
                prev.value().get().append(std::move(list.first.value()));
            }
            return {};
        }
        return {std::move(list)};
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::insert(size_t position, const List& list) noexcept
    {
        return this->insert(position, List(list));
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::insert(size_t position, size_t count, const T& value) noexcept
    {
        return this->insert(position, List(count, value));
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::insert(size_t position, std::initializer_list<T> values) noexcept
    {
        return this->insert(position, List(values));
    }
    template<typename T>
    template<typename R>
    constexpr std::optional<List<T>> List<T>::insert_range(size_t position, const R& range) noexcept
    {
        List list {};
        list.assign_range(range);
        return this->insert(position, std::move(list));
    }
    template<typename T>
    template<typename R>
    constexpr std::optional<List<T>> List<T>::insert_range(size_t position, R&& range) noexcept
    {
        List list {};
        list.assign_range(std::move(range));
        return this->insert(position, std::move(list));
    }
    template<typename T>
    template<typename... Args>
    constexpr std::optional<T> List<T>::emplace(size_t position, Args&&... args) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
            if(current.has_value())
            {
                current.value().get().prepend(Link::make(args...));
                return {};
            }
            else
            {
                this->first = Link::make(args...);
                return {};
            }
        }
        IterMut iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<Link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(Link::make(args...));
            return {};
        }
        return {T(std::move(args)...)};
    }

    template<typename T>
    constexpr std::optional<T> List<T>::take(size_t position) noexcept
    {
        IterMut iter = this->begin();
        iter += position;
        std::optional<std::reference_wrapper<Link>> current {iter.get_link()};
        if(current.has_value())
        {
            std::optional<std::reference_wrapper<Link>> prev = current.value().get().prev_link();
            bool is_first = !prev.has_value();
            std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
            if(is_first)
            {
                this->first = std::move(pop.second);
            }
            return std::move(pop.first.value);
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::take(size_t first, size_t last) noexcept
    {
        if(first > last)
        {
            std::swap(first, last);
        }
        IterMut iter = this->begin();
        std::optional<std::reference_wrapper<Link>> prev {};
        if(first > 0)
        {
            iter += first - 1;
            prev = iter.get_link();
            iter++;
        }
        std::optional<std::reference_wrapper<Link>> current {iter.get_link()};
        if(current.has_value())
        {
            if(first == last)
            {
                return {};
            }
            for(size_t i {first + 1}; i < last; i++)
            {
                iter++;
                std::optional<std::reference_wrapper<Link>> next {iter.get_link()};
                if(!next.has_value())
                {
                    break;
                }
                current = next;
            }
            bool is_first = !prev.has_value();
            std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
            if(is_first)
            {
                this->first = std::move(pop.second);
            }
            List o {std::move(pop.first)};
            return {std::move(o)};
        }
        return {};
    }
    template<typename T>
    constexpr size_t List<T>::erase(size_t position) noexcept
    {
        std::optional<T> take {this->take(position)};
        if(take.has_value())
        {
            return 1;
        }
        return 0;
    }
    template<typename T>
    constexpr size_t List<T>::erase(size_t first, size_t last) noexcept
    {
        if(first > last)
        {
            std::swap(first, last);
        }
        IterMut iter = this->begin();
        std::optional<std::reference_wrapper<Link>> prev {};
        if(first > 0)
        {
            iter += first - 1;
            prev = iter.get_link();
            iter++;
        }
        std::optional<std::reference_wrapper<Link>> current {iter.get_link()};
        if(current.has_value())
        {
            if(first == last)
            {
                return 0;
            }
            size_t n {1};
            for(size_t i {first + 1}; i < last; i++)
            {
                iter++;
                std::optional<std::reference_wrapper<Link>> next {iter.get_link()};
                if(!next.has_value())
                {
                    break;
                }
                n++;
                current = next;
            }
            bool is_first = !prev.has_value();
            std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
            if(is_first)
            {
                this->first = std::move(pop.second);
            }
            return n;
        }
        return 0;
    }

    template<typename T>
    constexpr void List<T>::push_back(const T& value) noexcept
    {
        return this->emplace_back(value);
    }
    template<typename T>
    constexpr void List<T>::push_back(T&& value) noexcept
    {
        return this->emplace_back(std::move(value));
    }
    template<typename T>
    template<typename... Args>
    constexpr void List<T>::emplace_back(Args&&... args) noexcept
    {
        if(!this->first.has_value())
        {
            std::optional<Link> first {Link::make(args...)};
            this->first.swap(first);
            return;
        }
        Link& last = this->first.value().last_link();
        last.append(Link::make(args...));
    }
    template<typename T>
    constexpr void List<T>::append(const List& list) noexcept
    {
        this->append(List(list));
    }
    template<typename T>
    constexpr void List<T>::append(List&& list) noexcept
    {
        if(!list.first.has_value())
        {
            return;
        }
        if(!this->first.has_value())
        {
            this->first = std::move(list.first);
            return;
        }
        Link& last = this->first.value().last_link();
        last.append(std::move(list.first.value()));
    }
    template<typename T>
    template<typename R>
    constexpr void List<T>::append_range(R&& range) noexcept
    {
        List list {};
        list.assign_range(std::move(range));
        return this->append(std::move(list));
    }
    template<typename T>
    template<typename R>
    constexpr void List<T>::append_range(const R& range) noexcept
    {
        List list {};
        list.assign_range(range);
        return this->append(std::move(list));
    }

    template<typename T>
    constexpr void List<T>::push_front(const T& value) noexcept
    {
        return this->emplace_front(value);
    }
    template<typename T>
    constexpr void List<T>::push_front(T&& value) noexcept
    {
        return this->emplace_front(std::move(value));
    }
    template<typename T>
    template<typename... Args>
    constexpr void List<T>::emplace_front(Args&&... args) noexcept
    {
        if(!this->first.has_value())
        {
            std::optional<Link> first {Link::make(args...)};
            this->first.swap(first);
            return;
        }
        this->first.value().prepend(Link::make(args...));
    }
    template<typename T>
    constexpr void List<T>::prepend(const List& list) noexcept
    {
        this->prepend(List(list));
    }
    template<typename T>
    constexpr void List<T>::prepend(List&& list) noexcept
    {
        if(!list.first.has_value())
        {
            return;
        }
        if(!this->first.has_value())
        {
            this->first = std::move(list.first);
            return;
        }
        this->first.value().prepend(std::move(list.first.value()));
    }
    template<typename T>
    template<typename R>
    constexpr void List<T>::prepend_range(R&& range) noexcept
    {
        List list {};
        list.assign_range(std::move(range));
        return this->prepend(std::move(list));
    }
    template<typename T>
    template<typename R>
    constexpr void List<T>::prepend_range(const R& range) noexcept
    {
        List list {};
        list.assign_range(range);
        return this->prepend(std::move(list));
    }
    
    template<typename T>
    constexpr std::optional<T> List<T>::pop_back(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        Link& first = this->first.value();
        Link& last = first.last_link();

        std::optional<std::reference_wrapper<Link>> prev = last.prev_link();
        bool empty = !prev.has_value();
        std::pair<Link, std::optional<Link>> pop = last.pop(prev);
        T value = std::move(pop.first.value);
        if(empty)
        {
            this->first = {};
        }
        return {std::move(value)};
    }
    template<typename T>
    constexpr std::optional<T> List<T>::pop_front(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        std::pair<Link, std::optional<Link>> pop = this->get_first_link().value().get().pop({});
        T value = std::move(pop.first.value);
        this->first = std::move(pop.second);

        return {std::move(value)};
    }

    template<typename T>
    constexpr void List<T>::resize(size_t size) noexcept
    {
        std::optional<std::reference_wrapper<Link>> last = this->get_first_link();
        size_t i = 0;
        if(last.has_value())
        {
            i++;
            for(; i < size; i++)
            {
                std::optional<std::reference_wrapper<Link>> next = last.value().get().next_link();
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
                std::optional<Link> first {Link::make()};
                this->first.swap(first);
                last = this->get_first_link();
                continue;
            }
            last.value().get().append(Link::make());
            last = last.value().get().next_link();
        }
    }
    template<typename T>
    constexpr void List<T>::resize(size_t size, const T& value) noexcept
    {
        std::optional<std::reference_wrapper<Link>> last = this->get_first_link();
        size_t i = 0;
        if(last.has_value())
        {
            i++;
            for(; i < size; i++)
            {
                std::optional<std::reference_wrapper<Link>> next = last.value().get().next_link();
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
                std::optional<Link> first {Link::make(value)};
                this->first.swap(first);
                last = this->get_first_link();
                continue;
            }
            last.value().get().append(Link::make(value));
            last = last.value().get().next_link();
        }
    }

    template<typename T>
    constexpr void List<T>::swap(List& list) noexcept
    {
        this->first.swap(list.first);
    }

    // Operations ------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr void List<T>::merge(const List& list) noexcept
    {
        return this->merge(List(list));
    }
    template<typename T>
    constexpr void List<T>::merge(List&& list) noexcept
    {
        return this->merge(std::move(list), [](const T& a, const T& b) {
            return a < b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::merge(const List& list, F&& cmp) noexcept
    {
        return this->merge(List(list), std::move(cmp));
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::merge(List&& list, F&& cmp) noexcept
    {
        if(list.empty())
        {
            return;
        }
        if(this->empty())
        {
            std::swap(*this, list);
            return;
        }

        if(cmp(list.front().value(), this->front().value()))
        {
            std::swap(*this, list);
        }
        std::optional<std::reference_wrapper<Link>> next = this->first.value().next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(list.first.value()), std::move(cmp));
        }
        else
        {
            std::optional<std::unique_ptr<Link>> b {std::make_unique<Link>(std::move(list.first.value()))};
            b.value()->prev = this->first.value();
            this->first.value().next.swap(b);
        }
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::merge(const List& list, const F& cmp) noexcept
    {
        return this->merge(List(list), cmp);
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::merge(List&& list, const F& cmp) noexcept
    {
        if(list.empty())
        {
            return;
        }
        if(this->empty())
        {
            std::swap(*this, list);
            return;
        }

        if(cmp(list.front().value(), this->front().value()))
        {
            std::swap(*this, list);
        }
        std::optional<std::reference_wrapper<Link>> next = this->first.value().next_link();
        if(next.has_value())
        {
            next.value().get().merge(std::move(list.first.value()), cmp);
        }
        else
        {
            std::optional<std::unique_ptr<Link>> b {std::make_unique<Link>(std::move(list.first.value()))};
            b.value()->prev = this->first.value();
            this->first.value().next.swap(b);
        }
    }
    
    template<typename T>
    constexpr void List<T>::splice(size_t position, List& list) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
            if(current.has_value())
            {
                current.value().get().prepend(std::move(list));
                list.clear();
                return;
            }
            else
            {
                this->first = std::move(list.first);
                list.clear();
                return;
            }
        }
        IterMut iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<Link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(std::move(list));
            list.clear();
            return;
        }
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::splice(size_t position, List&& list) noexcept
    {
        if(position == 0)
        {
            std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
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
        IterMut iter = this->begin();
        iter += position - 1;
        std::optional<std::reference_wrapper<Link>> prev {iter.get_link()};
        if(prev.has_value())
        {
            prev.value().get().append(std::move(list));
            return {};
        }
        return {std::move(list)};
    }
    template<typename T>
    constexpr void List<T>::splice(size_t position, List& list, size_t from_position) noexcept
    {
        this->splice(position, list, from_position, from_position + 1);
    }
    template<typename T>
    constexpr std::optional<List<T>> List<T>::splice(size_t position, List&& list, size_t from_position) noexcept
    {
        return this->splice(position, std::move(list), from_position, from_position + 1);
    }
    template<typename T>
    constexpr void List<T>::splice(size_t position, List& list, size_t from_first, size_t from_last) noexcept
    {
        std::optional<List> splice = list.take(from_first, from_last);
        if(splice.has_value())
        {
            this->splice(position, std::move(splice.value()));
        }
    }
    template<typename T>
    constexpr std::optional<List<T>>
        List<T>::splice(size_t position, List&& list, size_t from_first, size_t from_last) noexcept
    {
        std::optional<List> splice = list.take(from_first, from_last);
        if(splice.has_value())
        {
            return this->splice(position, std::move(splice.value()));
        }
        return {std::move(list)};
    }

    template<typename T>
    constexpr size_t List<T>::remove(const T& value) noexcept
    {
        return this->remove_if([value](const T& x) {
            return x == value;
        });
    }
    template<typename T>
    template<typename F>
    constexpr size_t List<T>::remove_if(const F& predicate) noexcept
    {
        std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
        size_t n = 0;
        while(true)
        {
            if(!current.has_value())
            {
                break;
            }
            if(predicate(current.value().get().value))
            {
                std::optional<std::reference_wrapper<Link>> prev = current.value().get().prev_link();
                bool is_first = !prev.has_value();
                std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
                if(is_first)
                {
                    this->first = std::move(pop.second);
                    current = this->get_first_link();
                }
                else
                {
                    current = prev.value().get().next_link();
                }
            }
            else
            {
                current = current.value().get().next_link();
            }
        }

        return n;
    }
    template<typename T>
    template<typename F>
    constexpr size_t List<T>::remove_if(F&& predicate) noexcept
    {
        std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
        size_t n = 0;
        while(true)
        {
            if(!current.has_value())
            {
                break;
            }
            if(predicate(current.value().get().value))
            {
                std::optional<std::reference_wrapper<Link>> prev = current.value().get().prev_link();
                bool is_first = !prev.has_value();
                std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
                if(is_first)
                {
                    this->first = std::move(pop.second);
                    current = this->get_first_link();
                }
                else
                {
                    current = prev.value().get().next_link();
                }
            }
            else
            {
                current = current.value().get().next_link();
            }
        }

        return n;
    }
    
    template<typename T>
    constexpr void List<T>::reverse(void) noexcept
    {
        List r {};
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
    }

    template<typename T>
    constexpr size_t List<T>::unique(void) noexcept
    {
        return this->unique([](const T& a, const T& b) {
            return a == b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr size_t List<T>::unique(F&& predicate) noexcept
    {
        List<std::reference_wrapper<const T>> found {};
        
        std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
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
                std::optional<std::reference_wrapper<Link>> prev {current.value().get().prev_link()};
                bool is_first = !prev.has_value();
                std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
                if(is_first)
                {
                    this->first = std::move(pop.second);
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
                current = current.value().get().next_link();
            }
        }

        return n;
    }
    template<typename T>
    template<typename F>
    constexpr size_t List<T>::unique(const F& predicate) noexcept
    {
        List<std::reference_wrapper<const T>> found {};
        
        std::optional<std::reference_wrapper<Link>> current {this->get_first_link()};
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
                std::optional<std::reference_wrapper<Link>> prev {current.value().get().prev_link()};
                bool is_first = !prev.has_value();
                std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev);
                if(is_first)
                {
                    this->first = std::move(pop.second);
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
                current = current.value().get().next_link();
            }
        }

        return n;
    }

    template<typename T>
    constexpr void List<T>::sort(void) noexcept
    {
        return this->sort([](const T& a, const T& b) {
            return a < b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::sort(const F& predicate) noexcept
    {
        // Do nothing if length is 0 or 1
        if(!this->first.has_value() || !this->first.value().next_link().has_value())
        {
            return;
        }

        // Split in halves
        List b {this->first.value().split_in_half()};

        // Sort each half
        this->sort(predicate);
        b.sort(predicate);

        // Merge halves
        this->merge(std::move(b), predicate);
    }
    template<typename T>
    template<typename F>
    constexpr void List<T>::sort(F&& predicate) noexcept
    {
        // Do nothing if length is 0 or 1
        if(!this->first.has_value() || !this->first.value().next_link().has_value())
        {
            return;
        }

        // Split in halves
        List b {this->first.value().split_in_half()};

        // Sort each half
        this->sort(predicate);
        b.sort(predicate);

        // Merge halves
        this->merge(std::move(b), std::move(predicate));
    }

    // Operators -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr List<T>& List<T>::operator=(const List& list) noexcept
    {
        if(list.first.has_value())
        {
            this->first = Link{list.first.value(), {}};
        }
        else
        {
            this->first = {};
        }
        return *this;
    }
    template<typename T>
    constexpr List<T>& List<T>::operator=(List&& list) noexcept
    {
        this->clear();
        this->first = std::move(list.first);
        list.clear();
        return *this;
    }
    template<typename T>
    constexpr List<T>& List<T>::operator=(std::initializer_list<T> values) noexcept
    {
        this->assign(values);
        return *this;
    }
    
    template<typename T>
    constexpr bool operator==(const List<T>& a, const List<T>& b) noexcept
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
    constexpr bool operator!=(const List<T>& a, const List<T>& b) noexcept
    {
        if(a.size() != b.size())
        {
            return true;
        }

        auto iter1 {a.cbegin()};
        auto iter2 {b.cbegin()};

        while(true)
        {
            std::optional<std::reference_wrapper<const T>> next1 {iter1.next()};
            std::optional<std::reference_wrapper<const T>> next2 {iter2.next()};

            if(next1 != next2)
            {
                return true;
            }
            if(!next1.has_value() || !next2.has_value())
            {
                break;
            }
        }
        return false;
    }

    template<typename T>
    constexpr std::compare_three_way_result<T, T>::type operator<=>(const List<T>& a, const List<T>& b) noexcept
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
    constexpr std::optional<std::reference_wrapper<typename List<T>::Link>> List<T>::get_first_link(void) noexcept
    {
        return this->first.transform([](Link& link) {
            return std::ref(link.first_link());
        });
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename List<T>::Link>>
        List<T>::get_first_link(void) const noexcept
    {
        return this->first.transform([](const Link& link) {
            return std::cref(link.first_link());
        });
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename List<T>::Link>> List<T>::get_last_link(void) noexcept
    {
        return this->first.transform([](Link& link) {
            return std::ref(link.last_link());
        });
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename List<T>::Link>>
        List<T>::get_last_link(void) const noexcept
    {
        return this->first.transform([](const Link& link) {
            return std::cref(link.last_link());
        });
    }
}