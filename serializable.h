#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

template <class T> class Serializable
{

public:

    Serializable(T* obj)
    {
        m_object = obj;
    }

    virtual void callTestCustomFunction()  = 0;
    virtual void registerType(T* t)
    {
        m_object = t;
    }

    virtual bool serialize(const char* filename)
    {
        FILE* fp = fopen(filename, "wb");
        if(!fp) {
            return false;
        }
        strcpy(m_filename, filename); // store the name
        // dump the class as pure array
        char dmp[sizeof(T)] = {0}; // set it to 0
        memcpy(dmp, m_object, sizeof(T)); // copy all chars into the array

        // set them into a the file
        for(int i=0; i < sizeof(T); i++) {
            fprintf(fp, "%c", dmp[i]);
        }

        fclose(fp);
        return true;
    }

    virtual T&   deserialize(const char* fname)
    {
        FILE* fp = fopen(fname, "rb");
        // added a check if file is open
        if(!fp) {
            return *(T*)0;
        }

        char c[sizeof(T)]={0};
        int i = 0;
        /*
        while (i < sizeof(T)) {
            c[i] = (char)fgetc(fp);
            i++;
        }*/
        fgets(c, sizeof(T), fp);

        m_object = (T*)c;
        //added fix close
        fclose(fp);
        return *m_object;
    }

private:
    char     m_filename[128]; // unused for now
    T*       m_object;
};


#endif // SERIALIZABLE_H
