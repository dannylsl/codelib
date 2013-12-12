#!/bin/python
#encoding = UTF-8

class Foo() :

    def __init__(self, name) :
        self.name = name
        self.height = 135  # Common varibale
        self.__age = 10   # Pesudo Private variable

    def getHeight(self) :
        return self.height

    def getName(self) :
        return self.name

    def getAge(self) :
        return self.__age


if __name__ == '__main__' :
    foo = Foo("Jame Green")
    print "*" * 10, " Show foo __dict__" , "*" * 10
    print foo.__dict__
    print "*" * 30
    print ">>> Access __age by foo.getAge()"
    print foo.getName(), " is ", foo.height, "cm high and ", foo.getAge(), "years old"
    print ">>> Access __age by foo._Foo__age"
    print foo.name," is ", foo.getHeight(), "cm high and ", foo._Foo__age, "years old"
    print ">>> Failed to access __age by foo.__age"
    print foo.name," is ", foo.getHeight(), "cm high and ", foo.__age, "years old"
    # It returns Error : Foo instance has no attribute named '__age'
    # Because varibale with double underline (__age)  before will be changed to variable with
    # single underline and class Name before (_Foo__age)

