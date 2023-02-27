#include <iostream>
#include <variant>

template<typename F, typename Ret, typename A, typename... Rest>
A extract_argument_impl(Ret(F::*)(A, Rest...));

template<typename F, typename Ret, typename A, typename... Rest>
A extract_argument_impl(Ret(F::*)(A, Rest...) const);

template<typename TFunction>
auto extract_first(TFunction&&) {
    using type_t = decltype(extract_argument_impl(&TFunction::operator()));
    return type_t{};
}

template<typename T, typename TVariant, typename TFunction>
void call_final(const TVariant& variant, TFunction&& func) {
    using arg_t = std::decay_t<decltype(extract_first(std::forward<TFunction>(func)))>;
    if constexpr (std::is_same_v<std::decay_t<T>, arg_t>){
       func(std::get<T>(variant));
    }
}

template<std::size_t Index, typename T, typename... Ts, typename... Fs>
void conditional_call_impl(const std::variant<Ts...>& variant, Fs&&... func) {
    if (variant.index() == Index){
        (call_final<T>(variant, std::forward<Fs>(func)), ...);
    }
}

template<typename... Ts, std::size_t... Is, typename... Fs>
void conditional_call_sequence(std::index_sequence<Is...>, const std::variant<Ts...>& variant, Fs&&... func) {
    (conditional_call_impl<Is, Ts>(variant, std::forward<Fs>(func)...), ...);
}

template<typename... Ts, typename... Fs>
void conditional_call(const std::variant<Ts...>& variant, Fs&&... func) {
    conditional_call_sequence(std::make_index_sequence<sizeof...(Ts)>{}, variant, std::forward<Fs>(func)...);
}

int main()
{
    std::variant<int, float> val = 1;
    conditional_call(val,
        [](int a) {std::cout << "int" << "\n"; },
        [](float a) {std::cout << "float" << "\n"; });
}
