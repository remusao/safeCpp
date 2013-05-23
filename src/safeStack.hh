#ifndef SAFE_STACK_HH_
# define SAFE_STACK_HH_

# include <cstddef>
# include <memory>


namespace Structures
{
    namespace Safe
    {
        template <typename T, std::size_t N, std::size_t Capacity>
        class Stack
        {
            public:
                Stack();
                Stack(const T&);
                Stack(Stack&&) = default;
                Stack& operator=(Stack&& s) = default;
                ~Stack();


                // Forbiden methods
                Stack(const Stack&) = delete;
                Stack& operator=(const Stack&) = delete;

                // Methods
                Stack<T, N + 1, Capacity> push(const T&);
                Stack<T, N - 1, Capacity> pop();
                T& top();
                const T& top() const;

            private:
                // Every stack is a friend of other ones
                template <typename T2, std::size_t N2, std::size_t Capacity2>
                friend class Stack;

                Stack(std::unique_ptr<T[]>&&);

                std::unique_ptr<T[]> stack_;
        };

        //
        /// Utility function
        //

        /// Create an empty stack
        template <typename T, std::size_t Capacity>
        Stack<T, 0, Capacity> make_stack()
        {
            return Stack<T, 0, Capacity>();
        }
    }
}

//
// Push token
//
template <typename T>
struct Push
{
    const T& e;
};
template <typename T>
Push<T> push(const T& e)
{
    return Push<T>{e};
}

//
// Pop token
//
struct _Pop {};
_Pop Pop = _Pop{};

//
// Top token
//
struct _Top {};
_Top Top = _Top{};

// Specialization for Stack
template <
    template <typename, std::size_t, std::size_t> class Stack,
    typename T,
    std::size_t N,
    std::size_t Capacity>
Stack<T, N + 1, Capacity> operator>> (Stack<T, N, Capacity>&& s, Push<T> r)
{
    return s.push(r.e);
}

template <
    template <typename, std::size_t, std::size_t> class Stack,
    typename T,
    std::size_t N,
    std::size_t Capacity>
Stack<T, N - 1, Capacity> operator>> (Stack<T, N, Capacity>&& s, _Pop)
{
    return s.pop();
}

template <
    template <typename, std::size_t, std::size_t> class Stack,
    typename T,
    std::size_t N,
    std::size_t Capacity>
T& operator>> (Stack<T, N, Capacity>&& s, _Top)
{
    return s.top();
}




// Implementation
# include "safeStack.hxx"


#endif /* !SAFE_STACK_HH */
