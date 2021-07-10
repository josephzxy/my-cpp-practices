#include "../src/smart_pointer/unique_ptr.hpp"
#include "boost/test/unit_test.hpp"
#include <type_traits>
#include <utility>

BOOST_AUTO_TEST_CASE (test_assignablility)
{
    /*
    Test that unique_ptr<T> is not copy assignable
    but move assignable
    */
    int* raw_p = new int[1];
    unique_ptr<int> p1{ raw_p };

    BOOST_TEST (!std::is_copy_assignable<unique_ptr<int> >::value);
    // Does not compile as the copy constructor is deleted
    // unique_ptr<int> p2 = p1;

    BOOST_TEST (std::is_move_assignable<unique_ptr<int> >::value);
    // Compiles as the move constructor is available
    unique_ptr<int> p2 = std::move (p1);
    BOOST_TEST (!p1);
}

BOOST_AUTO_TEST_CASE (test_release)
{
    /*
    Test unique_ptr<T>::release()
    */
    int* raw_p = new int[1];
    unique_ptr<int> p{ raw_p };

    BOOST_TEST (p.release () == raw_p);
    BOOST_TEST (p.get () == nullptr);
}

BOOST_AUTO_TEST_CASE (test_swap)
{
    /*
    Test unique_ptr<T>::swap()
    */
    int* raw_p1 = new int[1];
    int* raw_p2 = new int[1];

    unique_ptr<int> p1{ raw_p1 };
    unique_ptr<int> p2{ raw_p2 };

    p1.swap (p2);
    BOOST_TEST (p1.get () == raw_p2);
    BOOST_TEST (p2.get () == raw_p1);
}
