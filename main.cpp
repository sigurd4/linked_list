#include <iostream>
#include <format>
#include <sstream>
#include <array>
#include <string>
#include <list>

#include "list.hpp"
#include "forward_list.hpp"

template<typename L>
std::string fmt_list(const L& x);

// Type that cannot be copied
class int_nocopy
{
    public:
        int value;
    
        int_nocopy():
            value(0)
        {

        }

        int_nocopy(int value):
            value(value)
        {

        }

        int_nocopy(int_nocopy&& value):
            value(std::move(value.value))
        {

        }

        int_nocopy& operator=(int_nocopy&& value)
        {
            this->value = std::move(value.value);
            return *this;
        }
};

bool operator==(const int_nocopy& a, const int_nocopy& b)
{
    return a.value == b.value;
}
std::strong_ordering operator<=>(const int_nocopy& a, const int_nocopy& b)
{
    return a.value <=> b.value;
}

template<typename O>
O&& operator<<(O&& __os, const int_nocopy& __x)
{
    __os << __x.value;
    return __os;
}

template<typename T>
void assert_eq(const T& a, const T& b)
{
    if(!(a == b) || a != b)
    {
        throw "Unequal";
    }
}

template<typename L, typename LC>
void test_constructor()
{
    LC lc {LC(5ull, 1)};
    assert_eq(lc, {1, 1, 1, 1, 1});
    
    lc = {LC(0ull, 1)};
    assert_eq(lc, {});
    
    lc = {LC(1ull, 1)};
    assert_eq(lc, {1});

    LC lc2 {lc};
    assert_eq(lc, lc2);
    
    L l {L(5ull)};
    assert_eq(l, {0, 0, 0, 0, 0});

    l = {1, 2, 3};
    L l2 {std::move(l)};
    assert_eq(l, {});
    assert_eq(l2, {1, 2, 3});

    const LC lc3 = {1, 2, 3};
    lc2 = {lc3};
    assert_eq(lc3, {1, 2, 3});
    assert_eq(lc2, {1, 2, 3}); 
}

template<typename L, typename LC>
void test_assign()
{
    LC lc {};
    lc.assign(5ull, 1);
    assert_eq(lc, {1, 1, 1, 1, 1});

    L l {1, 2, 3};
    l.assign({3, 2, 1});
    assert_eq(l, {3, 2, 1});

    const std::array<int, 3> ac {1, 2, 3};
    lc.assign_range(ac);
    assert_eq(lc, {1, 2, 3});

    std::array<int_nocopy, 3> a {1, 2, 3};
    l.assign_range(std::move(a));
    assert_eq(l, {1, 2, 3});
}

template<typename L>
void test_front_back()
{
    L l {1, 2, 3};
    int_nocopy front {1};
    int_nocopy back {3};
    assert_eq(l.front(), {std::ref(front)});
    assert_eq(l.back(), {std::ref(back)});
}

template<typename L>
void test_double_sided_iter()
{
    L l {1, 2, 3};

    int_nocopy i = 1;
    for(int_nocopy& x : l.begin())
    {
        assert_eq(x, i);
        i.value++;
    }
    for(int_nocopy& x : l.rbegin())
    {
        i.value--;
        assert_eq(x, i);
    }
    
    const L l2 {1, 2, 3};

    i = 1;
    for(const int_nocopy& x : l2.begin())
    {
        assert_eq(x, i);
        i.value++;
    }
    for(const int_nocopy& x : l2.rbegin())
    {
        i.value--;
        assert_eq(x, i);
    }
}

template<typename L>
void test_iter()
{
    L l {1, 2, 3};

    int_nocopy i = 1;
    for(int_nocopy& x : l.begin())
    {
        assert_eq(x, i);
        i.value++;
    }
    
    const L l2 {1, 2, 3};

    i = 1;
    for(const int_nocopy& x : l2.begin())
    {
        assert_eq(x, i);
        i.value++;
    }
}

template<typename L>
void test_capacity()
{
    L l {};
    assert_eq(l.empty(), true);
    assert_eq(l.size(), 0ull);

    l = {1, 2, 3};
    assert_eq(l.empty(), false);
    assert_eq(l.size(), 3ull);

    assert_eq(l.max_size() >= 768614336404564650ull, true);
}

template<typename L, typename LC>
void test_modifiers()
{
    L l {1, 2, 3};
    l.clear();
    assert_eq(l, {});

    for(size_t i = 0; i <= 3; i++)
    {
        l = {1, 2, 3};
        std::optional<int_nocopy> o {l.insert(i, 0)};
        assert_eq(o.has_value(), false);
    }
    
    for(size_t i = 0; i <= 3; i++)
    {
        L l2 {1, 2, 3};
        l = {1, 2, 3};
        std::optional<L> o {l.insert(i, std::move(l2))};
        assert_eq(o.has_value(), false);
    }

    LC lc {1, 2, 3};
    for(size_t i = 0; i <= 3; i++)
    {
        lc = {1, 2, 3};
        std::optional<LC> o {lc.insert(i, 5ull, 0)};
        assert_eq(o.has_value(), false);
    }

    for(size_t i = 0; i <= 3; i++)
    {
        std::array<int_nocopy, 3> a {1, 2, 3};
        l = {1, 2, 3};
        std::optional<L> o {l.insert_range(i, std::move(a))};
        assert_eq(o.has_value(), false);
    }
    
    const std::array<int, 3> ac {1, 2, 3};
    for(size_t i = 0; i <= 3; i++)
    {
        lc = {1, 2, 3};
        std::optional<LC> o {lc.insert_range(i, ac)};
        assert_eq(o.has_value(), false);
    }
    
    for(size_t i = 0; i < 3; i++)
    {
        l = {1, 2, 3};
        std::optional<int_nocopy> o {l.take(i)};
        assert_eq(o.has_value(), true);
        assert_eq(o.value(), int_nocopy(static_cast<int>(i + 1)));
    }
    
    l = {1, 2, 3};
    std::optional<L> o {l.take(0, 2)};
    assert_eq(o.has_value(), true);
    assert_eq(o.value(), {1, 2});
    
    l = {1, 2, 3};
    o = {l.take(1, 3)};
    assert_eq(o.has_value(), true);
    assert_eq(o.value(), {2, 3});
    
    for(size_t i = 0; i < 3; i++)
    {
        l = {1, 2, 3};
        assert_eq(l.erase(i), 1ull);
    }
    
    l = {1, 2, 3};
    assert_eq(l.erase(1, 3), 2ull);

    lc = {1, 2, 3};
    const int nb {4};
    lc.push_back(nb);
    assert_eq(lc, {1, 2, 3, 4});
    
    l = {1, 2, 3};
    l.push_back(4);
    assert_eq(l, {1, 2, 3, 4});
    
    lc = {1, 2, 3};
    const std::array<int, 3> acb {4, 5, 6};
    lc.append_range(acb);
    assert_eq(lc, {1, 2, 3, 4, 5, 6});
    
    l = {1, 2, 3};
    std::array<int_nocopy, 3> ab {4, 5, 6};
    l.append_range(std::move(ab));
    assert_eq(l, {1, 2, 3, 4, 5, 6});
    
    lc = {1, 2, 3};
    const int nf {0};
    lc.push_front(nf);
    assert_eq(lc, {0, 1, 2, 3});
    
    l = {1, 2, 3};
    l.push_front(0);
    assert_eq(l, {0, 1, 2, 3});
    
    lc = {1, 2, 3};
    const std::array<int, 3> acf {-2, -1, 0};
    lc.prepend_range(acf);
    assert_eq(lc, {-2, -1, 0, 1, 2, 3});
    
    l = {1, 2, 3};
    std::array<int_nocopy, 3> af {-2, -1, 0};
    l.prepend_range(std::move(af));
    assert_eq(l, {-2, -1, 0, 1, 2, 3});
    
    l = {1, 2, 3};
    std::optional<int_nocopy> p = {l.pop_back()};
    assert_eq(p.has_value(), true);
    assert_eq(p.value(), {3});
    assert_eq(l, {1, 2});
    
    l = {1, 2, 3};
    p = {l.pop_front()};
    assert_eq(p.has_value(), true);
    assert_eq(p.value(), {1});
    assert_eq(l, {2, 3});

    l = {1, 2, 3};
    l.resize(4);
    assert_eq(l, {1, 2, 3, 0});

    lc = {1, 2, 3};
    lc.resize(4, 4);
    assert_eq(lc, {1, 2, 3, 4});

    l = {1, 2, 3};
    L l2 {4, 5, 6};
    l.swap(l2);
    assert_eq(l, {4, 5, 6});
    assert_eq(l2, {1, 2, 3});
}

template<typename L, typename LC>
void test_operations()
{
    L l {1, 3};
    L l2 {2, 4};
    l.merge(std::move(l2));
    assert_eq(l, {1, 2, 3, 4});

    l = {1, 4};
    l2 = {2, 3};
    l.splice(1, l2);
    assert_eq(l, {1, 2, 3, 4});
    assert_eq(l2, {});
    
    l = {1, 4};
    l2 = {2, 3};
    l.splice(1, std::move(l2));
    assert_eq(l, {1, 2, 3, 4});
    
    l = {1, 4};
    l2 = {2, 3, 5};
    l.splice(1, l2, 0, 2);
    assert_eq(l, {1, 2, 3, 4});
    assert_eq(l2, {5});
    
    l = {1, 4};
    l2 = {2, 3, 5};
    l.splice(1, std::move(l2), 0, 2);
    assert_eq(l, {1, 2, 3, 4});
    
    l = {1, 4};
    l2 = {2, 3, 5};
    l.splice(1, l2, 0);
    l.splice(2, l2, 0);
    assert_eq(l, {1, 2, 3, 4});
    assert_eq(l2, {5});
    
    l = {1, 4};
    l2 = {2, 3, 5};
    l.splice(1, l2, 0);
    l.splice(2, std::move(l2), 0);
    assert_eq(l, {1, 2, 3, 4});
    
    LC lc = {0, 1, 0, 2, 0, 3, 0, 4, 0};
    lc.remove(0);
    assert_eq(lc, {1, 2, 3, 4});
    
    l = {1, 2, 3, 4};
    l.reverse();
    assert_eq(l, {4, 3, 2, 1});
    
    l = {0, 1, 0, 2, 0, 3, 0, 4, 0};
    l.unique();
    assert_eq(l, {0, 1, 2, 3, 4});
    
    l = {3, 2, 1, 4};
    l.sort();
    assert_eq(l, {1, 2, 3, 4});
}

int main()
{
    test_constructor<sss::list<int_nocopy>, sss::list<int>>();
    test_assign<sss::list<int_nocopy>, sss::list<int>>();
    test_front_back<sss::list<int_nocopy>>();
    test_double_sided_iter<sss::list<int_nocopy>>();
    test_capacity<sss::list<int_nocopy>>();
    test_modifiers<sss::list<int_nocopy>, sss::list<int>>();
    test_operations<sss::list<int_nocopy>, sss::list<int>>();
    
    test_constructor<sss::forward_list<int_nocopy>, sss::forward_list<int>>();
    test_assign<sss::forward_list<int_nocopy>, sss::forward_list<int>>();
    test_front_back<sss::forward_list<int_nocopy>>();
    test_iter<sss::forward_list<int_nocopy>>();
    test_capacity<sss::forward_list<int_nocopy>>();
    test_modifiers<sss::forward_list<int_nocopy>, sss::forward_list<int>>();
    test_operations<sss::forward_list<int_nocopy>, sss::forward_list<int>>();

    sss::list<int> list1 {1, 2, 3};

    const sss::list<int> list2 {4, 5, 6};
    list1.append_range(list2);

    std::cout << fmt_list(list1) << std::endl;
}

template<typename L>
std::string fmt_list(const L& x)
{
    std::stringstream buf;
    buf << "[";
    bool first = true;
    for(const auto& e : x)
    {
        if(!first)
        {
            buf << ", ";
        }

        buf << std::to_string(e);
        first = false;
    }
    buf << "]";

    std::string str;
    std::getline(buf, str);
    return str;
}