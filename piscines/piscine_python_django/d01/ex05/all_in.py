import sys

def get_state(query):

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

    
    for key, value in capital_cities.items():
        if (value == query):
            for key2, value2 in states.items():
                if (value2 == key):
                    return (key2)
    return False

def get_city(query):
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

    if (query in states):
        return capital_cities[states[query]]
    else:
        return False

if __name__ == '__main__':
    if (len(sys.argv) != 2):
        sys.exit()

    for word in sys.argv[1].split(","):
        query = word.strip().title()
        if (len(query) > 0):
            state = get_state(query)
            city = get_city(query)
            if (state):
                print("%s is the capital of %s" % (query, state))
            elif (city):
                print("%s is the capital of %s" % (city, query))
            else:
                print("%s is neither a capital city nor a state" % (word.strip()))