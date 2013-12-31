#!/usr/bin/python
# -*- encoding = utf8 -*-

from ConfigParser import ConfigParser
import os

class camHBconfig() :

    def __init__(self, filename) :
        print "camHBconfig __init__ called"
        if os.path.exists(filename) == False :
            raise ValueError('Failed to create camHBconfig Instance: File %s not exist'%filename)
        else :
            # Initialize Instance
            self.filename = filename
            self.read_data_from_conf()
            pass


    def read_data_from_conf(self) :
        self.config = ConfigParser()
        self.config.read(self.filename)

        areas_list = self.config.options('areas')
        self.area_count = len(areas_list)

        self.areas = list()

        for area in areas_list :
            content = self.config.get('areas', area)
            self.areas.append((area,content))


    def area_count_update(self) :
        self.area_count = len(self.config.options('areas'))


    def get_area_count(self) :
        print self.area_count
        return self.area_count


    def get_areas(self) :
        ret_list = list()
        for area in self.areas :
            area_name = area[0]
            pos_arr = area[1].split('|')
            pos_start = pos_arr[0].split(',')
            pos_end = pos_arr[1].split(',')
            start_x = pos_start[0]
            start_y = pos_start[1]
            end_x = pos_end[0]
            end_y = pos_end[1]
            ret_list.append((area_name, start_x, start_y, end_x, end_y))
#        print ret_list
#        return self.areas
        return ret_list

    def areas_update_for_remove(self,area_name) :
        print "remove area_name = %s"%area_name
        print "source"
        print self.areas
        for area in self.areas :
            if area_name in area :
                self.areas.remove(area)

        print "processed"
        print self.areas

    def areas_update_for_add(self, area_name, content) :
        print "add area_name = %s"%area_name
        print "source"
        print self.areas
        flag = False
        for area in self.areas :
            if area_name in area :
                flag = True
                break

        if flag == False :
            print "area not exist"
            self.areas.append((area_name, content))
        else:
            print "area exists"

        print "processed"
        print self.areas



    def add_area(self, area_name, content) :
        print "camHBconfig add_area"
        self.area_count = len(self.config.options('areas'))
        self.config.set('areas', area_name, content)
        self.area_count_update()
        self.areas_update_for_add(area_name, content)
        print "add self.area_count = %s"%self.area_count

        with open(self.filename, 'wb') as configfile :
            self.config.write(configfile)


    def remove_area(self, area_name) :
        print "camHBconfig remove_area"

        self.area_count = len(self.config.options('areas'))
        self.config.remove_option('areas', area_name)
        self.area_count_update()
        self.areas_update_for_remove(area_name)
        print "remove self.area_count = %s"%self.area_count

        with open(self.filename, 'wb') as configfile :
            self.config.write(configfile)


    def __del__(self) :
        print "camHBconfig __del__ called"


#if __name__ == '__main__' :

#    camhbConf = camHBconfig('config.ini')
#    camhbConf.get_area_count()
#    camhbConf.get_areas()
#    camhbConf.add_area('area2a','10,10|20,20')
#    camhbConf.remove_area('area1')
#    camhbConf.get_areas()
#    camhbConf.get_area_count()
