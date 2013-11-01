import csv

class csvReader() :
	reader = None

	def __init__(self, filename):
		self.reader = csv.reader(open(filename, 'rb'))

	def allprint(self) :
		for item in self.reader :
			print ', '.join(item)

	def get_value(self, itemname):
		print 'value'
		

csvr = csvReader('stream_chrome.csv')
csvr.allprint()
