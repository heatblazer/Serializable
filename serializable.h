#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

template <class T> class Serializable
{

public:

    bool serialize(const T* ob, const char* filename)
    {
        FILE* fp = fopen(filename, "wb");
        if(!fp) {
            return false;
        }
        strcpy(m_filename, filename); // store the name
        // dump the class as pure array
        union dmp {
            T member;
            char c[sizeof(T)];
        };
        union dmp d;
        memcpy(d.c, ob, sizeof(T));

        for(int i=0; i < sizeof(T); i++) {
            fprintf(fp, "%c", d.c[i]);
        }

        fclose(fp);
        return true;
    }

    T&   deserialize(const char* fname)
    {
        FILE* fp = fopen(fname, "rb");

        char c[sizeof(T)]={0};
        int i = 0;
        while (i < sizeof(T)) {
            c[i] = (char)fgetc(fp);
            i++;
        }

        m_object = (T*) c;
        return *m_object;
    }

private:
    char     m_filename[128]; // unused for now
    T*       m_object;
};


#endif // SERIALIZABLE_H
