#include "../src/smart_pointer/shared_ptr.hpp"
#include "boost/test/unit_test.hpp"
#include <type_traits>
#include <utility>

BOOST_AUTO_TEST_SUITE (test_shared_count)
BOOST_AUTO_TEST_CASE (test_get_count)
{
    /*
    Test shared_count::shared_count()
    Test shared_count::get_count()
    */
    BOOST_CHECK_EQUAL (shared_count ().get_count (), 1);
}

BOOST_AUTO_TEST_CASE (test_add_count)
{
    /*
    Test shared_count::add_count()
    */
    shared_count sc;
    BOOST_CHECK_EQUAL (sc.get_count (), 1);
    sc.add_count ();
    BOOST_CHECK_EQUAL (sc.get_count (), 2);
}

BOOST_AUTO_TEST_CASE (test_reduce_count)
{
    /*
    Test shared_count::reduce_count()
    */
    shared_count sc;
    BOOST_CHECK_EQUAL (sc.get_count (), 1);
    BOOST_CHECK_EQUAL (sc.reduce_count (), 0);
    BOOST_CHECK_EQUAL (sc.get_count (), 0);
}
BOOST_AUTO_TEST_SUITE_END ()

BOOST_AUTO_TEST_SUITE (test_shared_ptr)
BOOST_AUTO_TEST_CASE (test_copy_constructor)
{
    /*
    Test the copy constructor
    shared_ptr(const shared_ptr<T>& other)
    */
    shared_ptr<int> p1{ new int[1] };
    BOOST_CHECK_EQUAL (p1.use_count (), 1);
    shared_ptr<int> p2{ p1 };
    BOOST_CHECK_EQUAL (p1.use_count (), 2);
    BOOST_CHECK_EQUAL (p2.use_count (), 2);

    shared_ptr<int> p1_null{ nullptr };
    BOOST_CHECK_EQUAL (p1_null.use_count (), 0);
    shared_ptr<int> p2_null{ p1_null };
    BOOST_CHECK_EQUAL (p1_null.use_count (), 0);
    BOOST_CHECK_EQUAL (p2_null.use_count (), 0);
}

BOOST_AUTO_TEST_CASE (test_move_constructor)
{
    /*
    Test the move constructor
    shared_ptr(shared_ptr<T>&& other)
    */
    shared_ptr<int> p1{ new int[1] };
    BOOST_CHECK_EQUAL (p1.use_count (), 1);
    shared_ptr<int> p2{ std::move (p1) };
    BOOST_TEST (!p1.get ());
    BOOST_CHECK_EQUAL (p1.use_count (), 0);
    BOOST_CHECK_EQUAL (p2.use_count (), 1);

    shared_ptr<int> p1_null{ nullptr };
    BOOST_CHECK_EQUAL (p1_null.use_count (), 0);
    shared_ptr<int> p2_null{ std::move (p1_null) };
    BOOST_CHECK_EQUAL (p1_null.use_count (), 0);
    BOOST_CHECK_EQUAL (p2_null.use_count (), 0);
}

BOOST_AUTO_TEST_CASE (test_operator_assign)
{
    /*
    Test
    shared_ptr<T>& operator=(shared_ptr<T> other)
    */
    BOOST_TEST (std::is_copy_assignable<shared_ptr<int> >::value);
    BOOST_TEST (std::is_move_assignable<shared_ptr<int> >::value);

    shared_ptr<int> p1{ new int[1] };
    shared_ptr<int> p2{ new int[1] };

    BOOST_CHECK_EQUAL (p1.use_count (), 1);
    BOOST_TEST (p1.get () != p2.get ());
    p2 = p1;
    BOOST_CHECK_EQUAL (p1.use_count (), 2);
    BOOST_CHECK_EQUAL (p2.use_count (), 2);
    BOOST_CHECK_EQUAL (p1.get (), p2.get ());
}

BOOST_AUTO_TEST_CASE (test_swap)
{
    /*
    Test
    void swap(shared_ptr<T>& other)
    */
    int* raw_p1 = new int[1];
    int* raw_p2 = new int[1];
    shared_ptr<int> p1{ raw_p1 };
    shared_ptr<int> p2{ raw_p2 };
    shared_ptr<int> p3 = p2;

    BOOST_CHECK_EQUAL (p1.use_count (), 1);
    BOOST_CHECK_EQUAL (p1.get (), raw_p1);
    BOOST_CHECK_EQUAL (p2.use_count (), 2);
    BOOST_CHECK_EQUAL (p2.get (), raw_p2);

    p1.swap (p2);
    BOOST_CHECK_EQUAL (p2.use_count (), 1);
    BOOST_CHECK_EQUAL (p2.get (), raw_p1);
    BOOST_CHECK_EQUAL (p1.use_count (), 2);
    BOOST_CHECK_EQUAL (p1.get (), raw_p2);
}

BOOST_AUTO_TEST_CASE (test_use_cont)
{
    shared_ptr<int> p1{ new int[1] };
    BOOST_CHECK_EQUAL (p1.use_count (), 1);
    shared_ptr<int> p2{ nullptr };
    BOOST_CHECK_EQUAL (p2.use_count (), 0);
}

BOOST_AUTO_TEST_CASE (test_dynamic_pointer_cast)
{
    class Base
    {
      public:
        virtual ~Base () {}
    };

    class Derived : public Base
    {
      public:
        ~Derived () {}
    };

    shared_ptr<Base> p_b{ new Derived () };
    BOOST_CHECK_EQUAL (p_b.use_count (), 1);

    shared_ptr<Derived> p_d = dynamic_pointer_cast<Derived> (p_b);
    BOOST_CHECK_EQUAL (p_b.use_count (), 2);
    BOOST_CHECK_EQUAL (p_d.use_count (), 2);
    BOOST_CHECK_EQUAL (p_b.get (), p_d.get ());
}
BOOST_AUTO_TEST_SUITE_END ()
