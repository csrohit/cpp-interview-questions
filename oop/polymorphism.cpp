#include <iostream>




/**
 * Base class demonstrating virtual and non-virtual methods.
 * The virtual method allows dynamic dispatch when called through a base
 * reference or pointer to a derived object.
 */
class Base
{
    public:
    /**
     * Virtual method that can be overridden in derived classes.
     * When called through a Base reference bound to a Derived object,
     * the Derived implementation is selected.
     */
    virtual void sayHello()
    {
        std::cout << "Hello from Base\n";
    }

    /**
     * Non-virtual method that is bound at compile time.
     * Calls through a Base reference will use this Base implementation.
     */
    void sayBye()
    {
        std::cout << "Bye from Base\n";
    }
};



class Derived: public Base
{
    public:
    /**
     * Override of Base::sayHello(). Because Base::sayHello() is virtual,
     * this method is chosen when calling through a Base reference.
     */
    void sayHello() override
    {
        std::cout << "Hello from Derived\n";
    }

    /**
     * Hides Base::sayBye(). This is not virtual, so calls through a Base
     * reference still invoke Base::sayBye().
     */
    void sayBye()
    {
        std::cout << "Bye from Derived\n";
    }
};


/**
 * Example driver showing virtual dispatch and static method binding.
 * It creates Base and Derived objects and then invokes methods on them
 * directly and through a Base reference.
 */
int main()
{
    Base b;
    Derived d;

    /*
     * Calls Base::sayHello() because b is a Base object.
     */
    b.sayHello();

    /*
     * Calls Derived::sayBye() because d is a Derived object and the call
     * is made through the Derived type.
     */
    d.sayBye();


    /*
     * Calls Base::sayBye() because b is still a Base object.
     */
    b.sayBye();

    /*
     * Calls Derived::sayBye() because d is a Derived object.
     */
    d.sayBye();


    /*
     * Base reference bound to a Derived object.
     * The virtual sayHello() call resolves to Derived::sayHello().
     * The non-virtual sayBye() call resolves to Base::sayBye() because
     * it is bound to the static type Base.
     */
    Base& c = d;
    c.sayHello();
    c.sayBye();


    return 0;
}
