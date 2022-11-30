#include <type_traits>
#include <memory>

template <typename T>
struct is_smart_pointer_helper : public std::false_type {};

template <typename T>
struct is_smart_pointer_helper<std::unique_ptr<T>> : public std::true_type {};

template <typename T>
struct is_smart_pointer_helper<std::shared_ptr<T>> : public std::true_type {};

template <typename T>
struct is_smart_pointer_helper<std::weak_ptr<T>> : public std::true_type {};

template <typename T>
struct is_smart_pointer : public is_smart_pointer_helper<typename std::decay<T>::type> {};
