#include <iostream>

// test serializable
#include "serializable.h"

using namespace std;

struct A {
    char name[64];
    int i;
    struct {
        float x; float y; float z; float w;
    } vec4;
    int (*fp)(void*);
    int     bigarr[128];
};

static int fpp(void* p)
{
    printf("AAAAAAAAAAAAAAAAAAAAA\n");
    return 100;
}

int main(int argc, char *argv[])
{
    A a;
    a.i = 1000;
    strcpy(a.name, "ILIAN TREST");
    a.vec4.w = a.vec4.x = a.vec4.y = a.vec4.z = 2.200;
    a.fp = fpp;

    Serializable<A> ser;


    ser.serialize(&a, "Aserialize");

    A& pa = ser.deserialize("Aserialize");


    pa.fp(0);


    return 0;
}
