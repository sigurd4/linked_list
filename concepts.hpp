#pragma once

#include <concepts>
#include <execution>

namespace sss
{
    template<typename C, typename T>
    concept comparison = requires (C f, const T& a, const T& b)
    {
        {f(a, b)} -> std::same_as<bool>;
    };
    template<typename C, typename T, typename U>
    concept mapper = requires (C f, T&& a)
    {
        {f(std::move(a))} -> std::same_as<U>;
    };
    template<typename T>
    concept execution_policy = std::is_execution_policy_v<T>;
    template<typename T>
    concept par_execution_policy = execution_policy<T>
        && (!((!std::same_as<T, std::execution::parallel_policy>) && (!std::same_as<T, std::execution::parallel_unsequenced_policy>)));
    template<typename T>
    concept nonpar_execution_policy = execution_policy<T> && (!par_execution_policy<T>);
}