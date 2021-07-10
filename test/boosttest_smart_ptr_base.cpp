#include "../src/smart_pointer/smart_ptr_base.hpp"
#include "boost/test/unit_test.hpp"

template <typename T> class concrete_smart_ptr : public smart_ptr<T> {
public:
    concrete_smart_ptr(T* ptr = nullptr)
        : smart_ptr<T>(ptr)
    {
    }
    ~concrete_smart_ptr() { delete this->ptr_; }
};

struct Tuple {
    int x;
    Tuple(int x)
        : x(x)
    {
    }
};

typedef concrete_smart_ptr<int> int_ptr;
typedef concrete_smart_ptr<Tuple> tuple_ptr;

BOOST_AUTO_TEST_CASE(test_get)
{
    /*
    Test smart_ptr<T>::get()
    */
    int* raw_p = new int[1];
    int_ptr p { raw_p };
    BOOST_CHECK_EQUAL(raw_p, p.get());
}

BOOST_AUTO_TEST_CASE(test_operator_star)
{
    /*
    Test smart_ptr<T>::operator*
    */
    const int val = 5;
    int* raw_p = new int[1];
    raw_p[0] = val;

    int_ptr p { raw_p };
    BOOST_CHECK_EQUAL(raw_p[0], *p);
}

BOOST_AUTO_TEST_CASE(test_operator_arrow)
{
    /*
    Test smart_ptr<T>::operator->
    */
    const int x = 5;
    Tuple* raw_p = new Tuple(x);

    tuple_ptr p { raw_p };
    BOOST_CHECK_EQUAL(raw_p->x, p->x);
}

BOOST_AUTO_TEST_CASE(test_operator_bool)
{
    /*
    Test smart_ptr<T>::operator bool
    */
    int* raw_p = nullptr;
    int_ptr p { raw_p };

    BOOST_CHECK_EQUAL((bool)raw_p, (bool)p);
}
