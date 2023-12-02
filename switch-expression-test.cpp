
#include <type_traits>

template<typename T, typename...Ts>
struct first_t {
    using type = T;
};

template<typename... Ts>
class switch_expression_class final {
    static_assert(sizeof ...(Ts) > 0);
    using key_t = typename first_t<Ts...>::type;

public:
    switch_expression_class(const Ts&... args)
        :expression(args...)
    {

    }

    template<typename TClass, typename... TVs>
    bool apply(TClass& instance, const key_t& in_key, TVs&&... args){
        key = in_key;
        assert(!set);
        set = true;
        return evaluate(instance, std::make_index_sequence<sizeof ...(Ts)>{},
                        std::forward<TVs>(args)...);
    }
private:
    template<typename TClass, std::size_t...Is,  typename... TVs>
    bool evaluate(TClass& instance, std::index_sequence<Is...>, TVs&&... args){
        bool applied = (... && try_apply<Is>(instance, std::forward<TVs>(args)...));
        assert(applied);
        return applied;
    }

    template<std::size_t I, typename TClass, typename... TVs>
    bool try_apply(TClass& instance, TVs&&... args) {
        if constexpr (I + 1 < sizeof ...(Ts)){
            using candidate_t = std::decay_t<decltype(std::get<I>(instance))>;
            if constexpr (std::is_same_v<key_t, candidate_t>){
                // todo:: check if callable
                if (key == std::get<I>(expression)){
                    auto* function = std::get<I + 1>(expression);
                    instance.(*function)(std::forward<TVs>(args)...);
                    return true;
                }
            }
        }
    }

    std::tuple<Ts...> expression;
    key_t key;
    bool set { false };
};

class stub{
public :
    void foo(int){}
    void bar(int){}
};

template<typename... Ts>
switch_expression_class(Ts...)->switch_expression_class<Ts...>;

int main(){

    stub s;
    switch_expression_class(
            0, &stub::foo,
            1, &stub::bar
    ).apply(s, 1, 13);

    return 0;
}
