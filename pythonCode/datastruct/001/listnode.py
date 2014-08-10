#!/usr/bin/python
# -*- coding: utf-8 -*-

class ListNode() :
    def __init__(self, x) :
        self.x = x
        self.next = None


if __name__ == "__main__" :
	a = ListNode(1)
	b = ListNode(2)
	a.next = b

	print a.x
	print b.x
	print a.next.x

