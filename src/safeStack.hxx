
namespace Structures
{
    namespace Safe
    {
        template <typename T, std::size_t N, std::size_t Capacity>
        Stack<T, N, Capacity>::Stack()
        {
            static_assert(N == 0, "New stack must be empty");
            static_assert(Capacity > 0, "Capacity of the stack must be greater than zero");

            stack_ = std::unique_ptr<T[]>(new T[Capacity]);
        }


        template <typename T, std::size_t N, std::size_t Capacity>
        Stack<T, N, Capacity>::Stack(const T& e)
        {
            static_assert(N == 1, "Size of stack is not valid");
            static_assert(Capacity > 0, "Capacity of the stack must be greater than zero");

            stack_ = std::unique_ptr<T[]>(new T[Capacity]);
            stack_[0] = e;
        }

        template <typename T, std::size_t N, std::size_t Capacity>
        Stack<T, N, Capacity>::Stack(std::unique_ptr<T[]>&& s)
            : stack_(std::move(s))
        {
        }

        template <typename T, std::size_t N, std::size_t Capacity>
        Stack<T, N, Capacity>::~Stack()
        {
        }


        template <typename T, std::size_t N, std::size_t Capacity>
        Stack<T, N + 1, Capacity> Stack<T, N, Capacity>::push(const T& e)
        {
            static_assert(N < Capacity, "Stack overflow");

            stack_[N] = e;
            return Stack<T, N + 1, Capacity>(std::move(stack_));
        }

        template <typename T, std::size_t N, std::size_t Capacity>
        Stack<T, N - 1, Capacity> Stack<T, N, Capacity>::pop()
        {
            static_assert(N > 0, "Can't pop an empty stack");

            return Stack<T, N - 1, Capacity>(std::move(stack_));
        }

        template <typename T, std::size_t N, std::size_t Capacity>
        T& Stack<T, N, Capacity>::top()
        {
            static_assert(N > 0, "Empty stack has no top");

            return stack_[N - 1];
        }


        template <typename T, std::size_t N, std::size_t Capacity>
        const T& Stack<T, N, Capacity>::top() const
        {
            static_assert(N > 0, "Empty stack has no top");

            return stack_[N - 1];
        }
    }
}
