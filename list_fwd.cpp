#include "list_fwd.hpp"

namespace sss
{
    template<typename T>
    constexpr ListFwd<T>::ListFwd(Link&& first) noexcept:
        first {std::move(first)}
    {

    }
    template<typename T>
    constexpr ListFwd<T>::ListFwd(std::optional<Link>&& first) noexcept:
        first {std::move(first)}
    {

    }
    template<typename T>
    constexpr ListFwd<T>::ListFwd(void) noexcept:
        first {std::nullopt}
    {

    }
    template<typename T>
    constexpr ListFwd<T>::ListFwd(size_t count, const T& value) noexcept:
        ListFwd()
    {
        this->resize(count, value);
    }
    template<typename T>
    constexpr ListFwd<T>::ListFwd(size_t count) noexcept:
        ListFwd()
    {
        this->resize(count);
    }
    template<typename T>
    constexpr ListFwd<T>::ListFwd(const ListFwd& list) noexcept:
        ListFwd()
    {
        if(list.first.has_value())
        {
            this->first = Link(list.first.value());
        }
    }
    template<typename T>
    constexpr ListFwd<T>::ListFwd(ListFwd&& list) noexcept:
        first {std::move(list.first)}
    {
        list.clear();
    }

    template<typename T>
    constexpr ListFwd<T>::ListFwd(std::initializer_list<T> values) noexcept:
        ListFwd()
    {
        this->assign(values);
    }
    
#if _HAS_CXX23 && defined(__cpp_lib_concepts)
    template<typename T>
    template<typename R>
    constexpr ListFwd<T>::ListFwd(std::from_range_t, const R& range) noexcept:
        ListFwd()
    {
        this->assign_range(range);
    }
    template<typename T>
    template<typename R>
    constexpr ListFwd<T>::ListFwd(std::from_range_t, R&& range) noexcept:
        ListFwd()
    {
        this->assign_range(range);
    }
#endif

    template<typename T>
    constexpr void ListFwd<T>::assign(size_t count, const T& value) noexcept
    {
        this->clear();
        this->resize(count, value);
    }
    template<typename T>
    constexpr void ListFwd<T>::assign(std::initializer_list<T> values) noexcept
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
                std::optional<Link> first {Link{std::move(value)}};
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
    constexpr void ListFwd<T>::assign_range(const R& values) noexcept
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
    constexpr void ListFwd<T>::assign_range(R&& values) noexcept
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
    constexpr std::optional<std::reference_wrapper<const T>> ListFwd<T>::front(void) const noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        const Link& last = this->first.value();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> ListFwd<T>::front(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        Link& last = this->first.value();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const T>> ListFwd<T>::back(void) const noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        const Link& last = this->first.value().last_link();
        return {last.value};
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<T>> ListFwd<T>::back(void) noexcept
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
    constexpr ListFwd<T>::Iter ListFwd<T>::cbegin(void) const noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::cend(void) const noexcept
    {
        return {};
    }
    template<typename T>
    constexpr ListFwd<T>::IterMut ListFwd<T>::begin(void) noexcept
    {
        return {*this};
    }
    template<typename T>
    constexpr ListFwd<T>::IterMut ListFwd<T>::end(void) noexcept
    {
        return {};
    }
    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::begin(void) const noexcept
    {
        return this->cbegin();
    }
    template<typename T>
    constexpr ListFwd<T>::Iter ListFwd<T>::end(void) const noexcept
    {
        return this->cend();
    }

    // Capacity --------------------------------------------------------------------------------------------------------
    
    template<typename T>
    constexpr bool ListFwd<T>::empty(void) const noexcept
    {
        return !this->first.has_value();
    }
    template<typename T>
    constexpr size_t ListFwd<T>::size(void) const noexcept
    {
        size_t n {0};
        for(Iter iter = this->cbegin(), end = this->cend(); iter != end; iter++)
        {
            n++;
        }
        return n;
    }
    template<typename T>
    constexpr size_t ListFwd<T>::max_size(void) const noexcept
    {
        return std::numeric_limits<size_t>::max();
    }

    // Modifiers -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr void ListFwd<T>::clear(void) noexcept
    {
        this->first = {};
    }
    
    template<typename T>
    constexpr std::optional<T> ListFwd<T>::insert(size_t position, const T& value) noexcept
    {
        return this->emplace(position, value);
    }
    template<typename T>
    constexpr std::optional<T> ListFwd<T>::insert(size_t position, T&& value) noexcept
    {
        return this->emplace(position, std::move(value));
    }
    template<typename T>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::insert(size_t position, ListFwd&& list) noexcept
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
    constexpr std::optional<ListFwd<T>> ListFwd<T>::insert(size_t position, const ListFwd& list) noexcept
    {
        return this->insert(position, ListFwd(list));
    }
    template<typename T>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::insert(size_t position, size_t count, const T& value) noexcept
    {
        return this->insert(position, ListFwd(count, value));
    }
    template<typename T>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::insert(size_t position, std::initializer_list<T> values) noexcept
    {
        return this->insert(position, ListFwd(values));
    }
    template<typename T>
    template<typename R>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::insert_range(size_t position, const R& range) noexcept
    {
        ListFwd list {};
        list.assign_range(range);
        return this->insert(position, std::move(list));
    }
    template<typename T>
    template<typename R>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::insert_range(size_t position, R&& range) noexcept
    {
        ListFwd list {};
        list.assign_range(std::move(range));
        return this->insert(position, std::move(list));
    }
    template<typename T>
    template<typename... Args>
    constexpr std::optional<T> ListFwd<T>::emplace(size_t position, Args&&... args) noexcept
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
    constexpr std::optional<T> ListFwd<T>::take(size_t position) noexcept
    {
        IterMut iter = this->begin();
        std::optional<std::reference_wrapper<Link>> prev {};
        if(position > 0)
        {
            iter += position - 1;
            prev = iter.get_link();
            iter++;
        }
        std::optional<std::reference_wrapper<Link>> current {iter.get_link()};
        if(current.has_value())
        {
            bool is_first = !prev.has_value();
            std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev, prev, this->first.value());
            if(is_first)
            {
                this->first = std::move(pop.second);
            }
            return std::move(pop.first.value);
        }
        return {};
    }
    template<typename T>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::take(size_t first, size_t last) noexcept
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
            std::optional<std::reference_wrapper<Link>> direct_prev {prev};
            for(size_t i {first + 1}; i < last; i++)
            {
                iter++;
                std::optional<std::reference_wrapper<Link>> next {iter.get_link()};
                if(!next.has_value())
                {
                    break;
                }
                direct_prev = current;
                current = next;
            }
            bool is_first = !prev.has_value();
            std::pair<Link, std::optional<Link>> pop = current.value()
                .get()
                .pop(prev, direct_prev, this->first.value());
            if(is_first)
            {
                this->first = std::move(pop.second);
            }
            ListFwd o {std::move(pop.first)};
            return {std::move(o)};
        }
        return {};
    }
    template<typename T>
    constexpr size_t ListFwd<T>::erase(size_t position) noexcept
    {
        std::optional<T> take {this->take(position)};
        if(take.has_value())
        {
            return 1;
        }
        return 0;
    }
    template<typename T>
    constexpr size_t ListFwd<T>::erase(size_t first, size_t last) noexcept
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
            std::optional<std::reference_wrapper<Link>> direct_prev {prev};
            for(size_t i {first + 1}; i < last; i++)
            {
                iter++;
                std::optional<std::reference_wrapper<Link>> next {iter.get_link()};
                if(!next.has_value())
                {
                    break;
                }
                direct_prev = current;
                n++;
                current = next;
            }
            bool is_first = !prev.has_value();
            std::pair<Link, std::optional<Link>> pop = current.value()
                .get()
                .pop(prev, direct_prev, this->first.value());
            if(is_first)
            {
                this->first = std::move(pop.second);
            }
            return n;
        }
        return 0;
    }
    
    template<typename T>
    constexpr void ListFwd<T>::push_back(const T& value) noexcept
    {
        return this->emplace_back(value);
    }
    template<typename T>
    constexpr void ListFwd<T>::push_back(T&& value) noexcept
    {
        return this->emplace_back(std::move(value));
    }
    template<typename T>
    template<typename... Args>
    constexpr void ListFwd<T>::emplace_back(Args&&... args) noexcept
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
    constexpr void ListFwd<T>::append(const ListFwd& list) noexcept
    {
        this->append(ListFwd(list));
    }
    template<typename T>
    constexpr void ListFwd<T>::append(ListFwd&& list) noexcept
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
    constexpr void ListFwd<T>::append_range(R&& range) noexcept
    {
        ListFwd list {};
        list.assign_range(std::move(range));
        return this->append(std::move(list));
    }
    template<typename T>
    template<typename R>
    constexpr void ListFwd<T>::append_range(const R& range) noexcept
    {
        ListFwd list {};
        list.assign_range(range);
        return this->append(std::move(list));
    }

    template<typename T>
    constexpr void ListFwd<T>::push_front(const T& value) noexcept
    {
        return this->emplace_front(value);
    }
    template<typename T>
    constexpr void ListFwd<T>::push_front(T&& value) noexcept
    {
        return this->emplace_front(std::move(value));
    }
    template<typename T>
    template<typename... Args>
    constexpr void ListFwd<T>::emplace_front(Args&&... args) noexcept
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
    constexpr void ListFwd<T>::prepend(const ListFwd& list) noexcept
    {
        this->prepend(ListFwd(list));
    }
    template<typename T>
    constexpr void ListFwd<T>::prepend(ListFwd&& list) noexcept
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
    constexpr void ListFwd<T>::prepend_range(R&& range) noexcept
    {
        ListFwd list {};
        list.assign_range(std::move(range));
        return this->prepend(std::move(list));
    }
    template<typename T>
    template<typename R>
    constexpr void ListFwd<T>::prepend_range(const R& range) noexcept
    {
        ListFwd list {};
        list.assign_range(range);
        return this->prepend(std::move(list));
    }

    template<typename T>
    constexpr std::optional<T> ListFwd<T>::pop_back(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        Link& first = this->first.value();
        std::pair<std::optional<std::reference_wrapper<Link>>, Link&> last_two = first.last_two_links();

        bool empty = !last_two.first.has_value();
        std::pair<Link, std::optional<Link>> pop = last_two.second.pop(last_two.first, last_two.first, first);
        T value = std::move(pop.first.value);
        if(empty)
        {
            this->first = {};
        }
        return {std::move(value)};
    }
    template<typename T>
    constexpr std::optional<T> ListFwd<T>::pop_front(void) noexcept
    {
        if(!this->first.has_value())
        {
            return {};
        }
        Link& first {this->first.value()};
        std::pair<Link, std::optional<Link>> pop = first.pop({}, {}, first);
        T value = std::move(pop.first.value);
        this->first = std::move(pop.second);

        return {std::move(value)};
    }

    template<typename T>
    constexpr void ListFwd<T>::resize(size_t size) noexcept
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
    constexpr void ListFwd<T>::resize(size_t size, const T& value) noexcept
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
    constexpr void ListFwd<T>::swap(ListFwd& list) noexcept
    {
        this->first.swap(list.first);
    }

    // Operations ------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr void ListFwd<T>::merge(const ListFwd& list) noexcept
    {
        return this->merge(ListFwd(list));
    }
    template<typename T>
    constexpr void ListFwd<T>::merge(ListFwd&& list) noexcept
    {
        return this->merge(std::move(list), [](const T& a, const T& b) {
            return a < b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::merge(const ListFwd& list, F&& cmp) noexcept
    {
        return this->merge(ListFwd(list), std::move(cmp));
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::merge(ListFwd&& list, F&& cmp) noexcept
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
            this->first.value().next.swap(b);
        }
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::merge(const ListFwd& list, const F& cmp) noexcept
    {
        return this->merge(List(list), cmp);
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::merge(ListFwd&& list, const F& cmp) noexcept
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
            this->first.value().next.swap(b);
        }
    }

    template<typename T>
    constexpr void ListFwd<T>::splice(size_t position, ListFwd& list) noexcept
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
    constexpr std::optional<ListFwd<T>> ListFwd<T>::splice(size_t position, ListFwd&& list) noexcept
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
    constexpr void ListFwd<T>::splice(size_t position, ListFwd& list, size_t from_position) noexcept
    {
        this->splice(position, list, from_position, from_position + 1);
    }
    template<typename T>
    constexpr std::optional<ListFwd<T>> ListFwd<T>::splice(size_t position, ListFwd&& list, size_t from_position) noexcept
    {
        return this->splice(position, std::move(list), from_position, from_position + 1);
    }
    template<typename T>
    constexpr void ListFwd<T>::splice(size_t position, ListFwd& list, size_t from_first, size_t from_last) noexcept
    {
        std::optional<ListFwd> splice = list.take(from_first, from_last);
        if(splice.has_value())
        {
            this->splice(position, std::move(splice.value()));
        }
    }
    template<typename T>
    constexpr std::optional<ListFwd<T>>
        ListFwd<T>::splice(size_t position, ListFwd&& list, size_t from_first, size_t from_last) noexcept
    {
        std::optional<ListFwd> splice = list.take(from_first, from_last);
        if(splice.has_value())
        {
            return this->splice(position, std::move(splice.value()));
        }
        return {std::move(list)};
    }

    template<typename T>
    constexpr size_t ListFwd<T>::remove(const T& value) noexcept
    {
        return this->remove_if([value](const T& x) {
            return x == value;
        });
    }
    template<typename T>
    template<typename F>
    constexpr size_t ListFwd<T>::remove_if(const F& predicate) noexcept
    {
        std::optional<std::reference_wrapper<Link>> prev {};
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
                bool is_first = !prev.has_value();
                std::pair<T, std::optional<Link>> pop = current.value().get().pop(prev, prev, this->first.value());
                if(is_first)
                {
                    this->first = pop.second;
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
    constexpr size_t ListFwd<T>::remove_if(F&& predicate) noexcept
    {
        std::optional<std::reference_wrapper<Link>> prev {};
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
                bool is_first = !prev.has_value();
                std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev, prev, this->first.value());
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
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }

    template<typename T>
    constexpr void ListFwd<T>::reverse(void) noexcept
    {
        ListFwd r {};
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
    constexpr size_t ListFwd<T>::unique(void) noexcept
    {
        return this->unique([](const T& a, const T& b) {
            return a == b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr size_t ListFwd<T>::unique(const F& predicate) noexcept
    {
        ListFwd<std::reference_wrapper<const T>> found {};
        
        std::optional<std::reference_wrapper<Link>> prev {};
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
                bool is_first = !prev.has_value();
                std::pair<T, std::optional<Link>> pop = current.value().get().pop(prev, prev, this->first.value());
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
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }
    template<typename T>
    template<typename F>
    constexpr size_t ListFwd<T>::unique(F&& predicate) noexcept
    {
        ListFwd<std::reference_wrapper<const T>> found {};
        
        std::optional<std::reference_wrapper<Link>> prev {};
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
                bool is_first = !prev.has_value();
                std::pair<Link, std::optional<Link>> pop = current.value().get().pop(prev, prev, this->first.value());
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
                prev = current;
                current = current.value().get().next_link();
            }
        }

        return n;
    }

    template<typename T>
    constexpr void ListFwd<T>::sort(void) noexcept
    {
        return this->sort([](const T& a, const T& b) {
            return a < b;
        });
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::sort(const F& predicate) noexcept
    {
        // Do nothing if length is 0 or 1
        if(!this->first.has_value() || !this->first.value().next_link().has_value())
        {
            return;
        }

        // Split in halves
        ListFwd b {this->first.value().split_in_half()};

        // Sort each half
        this->sort(predicate);
        b.sort(predicate);

        // Merge halves
        this->merge(std::move(b), predicate);
    }
    template<typename T>
    template<typename F>
    constexpr void ListFwd<T>::sort(F&& predicate) noexcept
    {
        // Do nothing if length is 0 or 1
        if(!this->first.has_value() || !this->first.value().next_link().has_value())
        {
            return;
        }

        // Split in halves
        ListFwd b {this->first.value().split_in_half()};

        // Sort each half
        this->sort(predicate);
        b.sort(predicate);

        // Merge halves
        this->merge(std::move(b), std::move(predicate));
    }

    // Operators -------------------------------------------------------------------------------------------------------

    template<typename T>
    constexpr ListFwd<T>& ListFwd<T>::operator=(const ListFwd& list) noexcept
    {
        if(list.first.has_value())
        {
            this->first = Link{list.first.value()};
        }
        else
        {
            this->first = {};
        }
        return *this;
    }
    template<typename T>
    constexpr ListFwd<T>& ListFwd<T>::operator=(ListFwd&& list) noexcept
    {
        this->clear();
        this->first = std::move(list.first);
        list.clear();
        return *this;
    }
    template<typename T>
    constexpr ListFwd<T>& ListFwd<T>::operator=(std::initializer_list<T> values) noexcept
    {
        this->assign(values);
        return *this;
    }

    template<typename T>
    constexpr bool operator==(const ListFwd<T>& a, const ListFwd<T>& b) noexcept
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
    constexpr std::compare_three_way_result<T, T>::type operator<=>(const ListFwd<T>& a, const ListFwd<T>& b) noexcept
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
    constexpr std::optional<std::reference_wrapper<typename ListFwd<T>::Link>> ListFwd<T>::get_first_link(void) noexcept
    {
        return this->first.transform([](Link& link) {
            return std::ref(link);
        });
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename ListFwd<T>::Link>>
        ListFwd<T>::get_first_link(void) const noexcept
    {
        return this->first.transform([](const Link& link) {
            return std::cref(link);
        });
    }

    template<typename T>
    constexpr std::optional<std::reference_wrapper<typename ListFwd<T>::Link>> ListFwd<T>::get_last_link(void) noexcept
    {
        return this->first.transform([](Link& link) {
            return std::ref(link.last_link());
        });
    }
    template<typename T>
    constexpr std::optional<std::reference_wrapper<const typename ListFwd<T>::Link>> ListFwd<T>::get_last_link(void) const noexcept
    {
        return this->first.transform([](const Link& link) {
            return std::cref(link.last_link());
        });
    }
}
