#include <safeStack.hh>
#include <iostream>

template <typename T>
T operator>> (T l, std::ostream& s)
{
    s << l;
    return l;
}

template <typename T, typename Function>
auto operator>> (T&& l, Function r) -> decltype(r(std::move(l)))
{
    return r(std::move(l));
}

int main()
{
    using namespace Structures::Safe;

    make_stack<int, 5>()
        >> push(42)                     // stack : [42]
        >> push(60)                     // stack : [42, 60]
        >> Pop                          // stack : [42]
        >> Top                          // element : 42
        >> std::cout                    // print 42 and return 42
        >> [](int i) {return i + 1;}    // increment 42
        >> std::cout;                   // print 43

    std::cout << std::endl;

    return 0;
}
