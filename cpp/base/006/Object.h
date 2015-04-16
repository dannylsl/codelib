#ifndef __OBJECT_H
#define __OBJECT_H

class Object{
public:
    Object(const char* name);
    Object(Object&o);
    ~Object();
    char* get_obj_name() const;
    static void objInfo();

    static int id;
private:
    char* _name;
};

#endif
