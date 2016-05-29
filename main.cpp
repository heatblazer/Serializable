#include <iostream>

// test serializable
#include "serializable.h"

using namespace std;


// demonstarates a test object
struct A {
    char name[64];
    int i;
    struct {
        float x; float y; float z; float w;
    } vec4;
    int fp(void*)
    {
        printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    }

    int     bigarr[128];
};

class B;
class B {
public:
    B():m_int(100) {}
    int foo(){
        printf("FOO\n");
    }
    int setAndGet(int i)
    {
        if (i != m_int) {
            m_int = i;
        }
        return m_int;
    }


private:
    int m_int ;
};

// demonstrates a call to a function
static int fpp(void* p)
{
    printf("Called a function callback\n");
}

int main(int argc, char *argv[])
{
    A a;
    a.i = 1000;
    strcpy(a.name, "ILIAN TREST");
    a.vec4.w = a.vec4.x = a.vec4.y = a.vec4.z = 2.200;

    B b;
    b.setAndGet(2222222);


    Serializable<A> ser;
    Serializable<B> serb;

    // serialize to a file
//    ser.serialize(&a, "Aserialize");

    // deserialize from object
    A& pa = ser.deserialize("Aserialize");

   // serb.serialize(&b, "Bserialize");
    B& pb = serb.deserialize("Bserialize");
    // call a fiunction
    // if want to see the vars use debugging
    pa.fp(0);
    pb.foo();

    return 0;
}
