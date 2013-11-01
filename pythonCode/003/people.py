class people :
	# basic property
	name = ''
	age = 0

	#private property. can not be access
	__weight = 0
	
	#define constructure function
	def __init__(self, name, age, weight) :
		self.name = name
		self.age  = age
		self.__weight = weight

	def speak(self) :
		print  "%s is speaking: I am %d years old"%(self.name, self.age)



