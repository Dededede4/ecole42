#/usr/local/bin/python3

class HotBeverage:
	price = 0.3
	name = "hot beverage"
	descr = "Just some hot water in a cup."

	def description(self):
		return self.descr

	def __str__(self):
		return	("name : %s\n"
				"price : %s\n"
				"description : %s") %(self.name, self.price, self.description())


class Coffee(HotBeverage):
	name = "coffee" 
	price = 0.4
	descr = "A coffee, to stay awake."

class Tea(HotBeverage):
	name = "tea" 

class Chocolate(HotBeverage):
	name = "chocolate"
	price = 0.5
	descr = "Chocolate, sweet chocolate..."

class Cappuccino(HotBeverage):
	name = "cappuccino"
	price = 0.45
	descr = "Un po' di Italia nella sua tazza!"
