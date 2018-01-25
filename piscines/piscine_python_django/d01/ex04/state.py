import sys

if __name__ == '__main__':
    finded = False
    states = {
            "Oregon" : "OR",
            "Alabama" : "AL",
            "New Jersey": "NJ",
            "Colorado" : "CO"
            }
    capital_cities = {
            "OR": "Salem",
            "AL": "Montgomery",
            "NJ": "Trenton",
            "CO": "Denver"
            }
    if (len(sys.argv) != 2):
        sys.exit()
    
    for key, value in capital_cities.items():
        if (value == sys.argv[1]):
            for key2, value2 in states.items():
                if (value2 == key):
                    print (key2)
                    finded = True
    if (finded == False):
        print("Unknown capital city")
