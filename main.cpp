#include <iostream>

// test serializable
#include "serializable.h"

// C libs
#include <stdio.h>
#include <string.h> // for strcpy

using namespace std;

class A : public Serializable<A>
{
public:
    A() : Serializable(this)
    {
    }

    ~A()
    {
    }

    //!TODO - remove it from the Serialize interface
    //! \brief callTestCustomFunction
    //!
    void callTestCustomFunction()
    {
        _foo();
    }


    void setStringArray(const char* str)
    {
        strcpy(string_arr, str);
    }


    void printStrArray(void)
    {
        std::cout << string_arr << std::endl;
    }

private:
    void _foo()
    {
        std::cout << "A`s method" << std::endl;
    }

    int array[128];
    char string_arr[256];
};



int main(int argc, char *argv[])
{
    A a;

//    a.setStringArray("Ilian serializira obekta si");
//    a.serialize("Aserialize.ser");
    A& tmp = a.deserialize("Aserialize.ser");
    tmp.printStrArray();

    return 0;
}
