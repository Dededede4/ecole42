#/usr/local/bin/python3

import random
from beverages import *

class CoffeeMachine:
	nb_drink = 0;
	def __init__(self):
		pass

	class EmptyCup(HotBeverage):
		name = "empty cup"
		price = 0.9
		descr = "An empty cup?! Gimme my money back!"

	class BrokenMachineException(Exception):
		def __init__(self, msg= "This coffee machine has to be repaired."):
			Exception.__init__(self, msg)

	def repair(self):
		self.nb_drink = 0;

	def serve(self, drink):
		self.nb_drink += 1
		if (self.nb_drink > 10):
			raise self.BrokenMachineException()

		if(random.choice([True, False])):
			return self.EmptyCup();
		else:
			return drink;

if __name__ == '__main__':
	cm = CoffeeMachine()
	boisson = cm.serve(HotBeverage);
	print(boisson.name)
	boisson = cm.serve(Coffee);
	print(boisson.name)
	boisson = cm.serve(Tea);
	print(boisson.name)
	boisson = cm.serve(Chocolate);
	print(boisson.name)
	boisson = cm.serve(Cappuccino);
	print(boisson.name)
	boisson = cm.serve(Cappuccino);
	print(boisson.name)
	boisson = cm.serve(HotBeverage);
	print(boisson.name)
	boisson = cm.serve(Coffee);
	print(boisson.name)
	boisson = cm.serve(Tea);
	print(boisson.name)
	boisson = cm.serve(Tea);
	print(boisson.name)
	try:
		boisson = cm.serve(Chocolate);
	except CoffeeMachine.BrokenMachineException as err:
		print("ERROR: {0}".format(err))
	try:
		boisson = cm.serve(Chocolate);
	except CoffeeMachine.BrokenMachineException as err:
		print("ERROR: {0}".format(err))
	cm.repair()
	boisson = cm.serve(HotBeverage);
	print(boisson.name)
	boisson = cm.serve(Coffee);
	print(boisson.name)
	boisson = cm.serve(Tea);
	print(boisson.name)
	boisson = cm.serve(Chocolate);
	print(boisson.name)
	boisson = cm.serve(Cappuccino);
	print(boisson.name)
	boisson = cm.serve(Cappuccino);
	print(boisson.name)
	boisson = cm.serve(HotBeverage);
	print(boisson.name)
	boisson = cm.serve(Coffee);
	print(boisson.name)
	boisson = cm.serve(Tea);
	print(boisson.name)
	boisson = cm.serve(Tea);
	print(boisson.name)
	try:
		boisson = cm.serve(Chocolate);
	except CoffeeMachine.BrokenMachineException as err:
		print("ERROR: {0}".format(err))