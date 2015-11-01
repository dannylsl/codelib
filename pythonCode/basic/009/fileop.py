#!/usr/bin/python

def get_sum_rps(RPS_list) :
    length = len(RPS_list)
    sum = 0
    for i in range(1, length) :
        print RPS_list[i]
        sum = sum + float(RPS_list[i])
    return sum


if __name__ == "__main__" :

    fp = open("log.txt", "rw")
    rps_list = list()
    while True :
        line = fp.readline()

        if "minute" in line:
            rps_list =  []
            rps_list.append(line);
        elif "#/sec" in line:
            arr = line.split()
            rps_list.append(arr[4])

        if len(line) == 0 :
            break

    print rps_list

    if get_sum_rps(rps_list) < 3600 :
        print "Create More Instance here"

    fp.close()

