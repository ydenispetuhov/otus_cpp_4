#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

template<
        template<typename, typename> typename Container,
        typename Type,
        typename Allocator = std::allocator<Type>,
        typename = std::enable_if_t<
                std::is_same_v<Container<Type, Allocator>, std::vector<Type, Allocator>> ||
                std::is_same_v<Container<Type, Allocator>, std::list<Type, Allocator>>>>
std::ostream &operator<<(std::ostream &os, const Container<Type, Allocator> &container) {
    for (auto iter = std::begin(container); iter != std::end(container); ++iter) {
        if (iter != std::begin(container))
            std::cout << ", ";
        os << *iter;
    }
    return os;
}

namespace motivation {

    void example() {
        std::cout << "*****   motivation::example   *****" << std::endl;

        std::vector<int> vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Compile time error - std::vector does not have method sort
        // vector.sort()

        // Works good
        std::sort(vector.begin(), vector.end());
        std::cout << "vector after sort: \n\t" << vector << std::endl;

        std::list<int> list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Compile time error - std::list::iterator is not random access!
        // std::sort(list.begin(), list.end());

        // Works good - std::list has method sort
        list.sort();
        std::cout << "list after sort: \n\t" << list << std::endl;
    }

} // motivation

namespace first_attempt {

    template<typename T>
    auto sort_container(T &container) -> decltype(container.sort()) {
        container.sort();
    }

    template<typename T>
    auto sort_container(T &container) -> void {
        std::sort(container.begin(), container.end());
    }

    void example() {

        std::cout << "*****   first_attempt::example   *****" << std::endl;

        std::vector<int> vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Works good
        sort_container(vector);
        std::cout << "vector after sort: \n\t" << vector << std::endl;

        std::list<int> list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Compile time error!
        // ambiguous call
        // sort_container(list);
        // std::cout << "list after sort: \n\t" << list << std::endl;
        // :((
    }
} // first_attempt

namespace solution {

    namespace impl {

        template<typename T>
        auto sort_container(T &container, int) -> decltype(container.sort()) {
            container.sort();
        }

        template<typename T>
        auto sort_container(T &container, long) -> void {
            std::sort(container.begin(), container.end());
        }

    } // impl

    template<typename T>
    void sort_container(T &container) {
        impl::sort_container(container, 42);
    }

    void example() {
        std::cout << "*****   solution::example   *****" << std::endl;

        std::vector<int> vector{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Works good
        sort_container(vector);
        std::cout << "vector after sort: \n\t" << vector << std::endl;

        std::list<int> list{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
        // Works now
        sort_container(list);
        std::cout << "list after sort: \n\t" << list << std::endl;
    }

} // solution

int main() {

    motivation::example();
    first_attempt::example();
    solution::example();

    return 0;
}