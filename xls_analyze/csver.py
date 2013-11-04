import csv
import sys

class csvReader() :
	reader		= None
	csv_list	= list()
	cstate		= list()
	wakeups		= 0.0
	pstate		= list()

	def __init__(self, filename):
		self.reader = csv.reader(open(filename, 'rb'))


	def allprint(self) :
		print self.reader
		sys.exit(0)
		for item in self.reader :
			item = item.strip(' ')
			print ', '.join(item)


	def get_value(self, itemname):
		row = 0
		col = 0
		for line in self.reader :
#items = line.split(',')
			if itemname in line :
				print "find the result"
				print line


	def init_csv_list(self) :
		#Print "remove needless space from self.reader"
		#And store data in csv_list
		for line in self.reader :
			list_tmp = list()
			for item_in_line in line:
				item_stripped = item_in_line.strip()
				if item_stripped != '' and item_stripped.find('----') == -1 :
					list_tmp.append(item_stripped)
			if list_tmp != [] :
				self.csv_list.append(list_tmp)
				list_tmp = []
		#print self.csv_list


	def csv_list_print(self) :
		for line in self.csv_list :
			print line


	def get_cstate(self) :
		cstate_index = self.csv_list.index(['Core C State Residency'])
		core_num = len(self.csv_list[cstate_index + 1])
		core_list= self.csv_list[cstate_index + 1]
		offset = 2
		while True :
			if len(self.csv_list[cstate_index + offset]) == (core_num + 1) :
				self.cstate.append(self.csv_list[cstate_index + offset])
				offset = offset + 1
			else : 
				break
		print self.cstate
		print "Detect %d cores on this device"%core_num
		print "get cstate index = %d"%cstate_index


	def get_wakeup_sec_core(self) :	
		for item in self.csv_list :
			if len(item) == 1 :
				if item[0].find('Wakeups/sec/core') != -1:
					print item
					self.wakeups = float(item[0].split('=')[1])
					print self.wakeups
					break

	def get_pstate(self) :
		pstate_index = self.csv_list.index(['P State Residency'])
		
				


csvr = csvReader('stream_chrome.csv')
csvr.init_csv_list()
#csvr.csv_list_print()
csvr.get_cstate()
csvr.get_wakeup_sec_core()
#csvr.allprint()
#csvr.get_value('CC0')
