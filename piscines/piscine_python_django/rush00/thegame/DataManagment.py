import omdb
import os
import pickle
import random
import json
import copy
from django.conf import settings

class DataManagment:
    save_file = None

    def __init__(self):
        # Should check if the api is up
        self.load()

    def load(self):
        # Query omdb and create gamefile
        try:
            if __name__ == '__main__':
                f = open("/tmp/test", "rb")
            else:
                f = open(settings.SAVE_FILE, "rb")
        except Exception:
            self.save_file = self.init_save()
        else:
            self.save_file = pickle.load(f)
            f.close()

    def dump(self, save=False):
        try:
            if __name__ == '__main__':
                f = open("/tmp/test", "wb")
            else:
                f = open(settings.SAVE_FILE, "wb")
        except Exception:
            # TODO : Custom exeption for saving error
            raise Exception("Error while saving : data may be unavailable")
        if self.save_file == None:
            self.save_file = self.init_save()
        pickle.dump(self.save_file, f)
        f.close()

        f = open('/tmp/bidule', 'w')
        f.write(json.dumps(self.save_file))
        f.close()

    def load_default_settings(self):
        # Load the settings into the game object
        pass

    def init_save(self, name = ''):
        if __name__ == '__main__':
            c = [5, 5]
        else:
            c = [settings.START_X, settings.START_Y]

        save_file = {
            'player' : {
                'strength' : 1,
                'dir' : 0,
                'ball' : 5000,
                'coord' : c,
            },
            'movie' : {},
        }
        return {
            'active' : -1,
            'current' : save_file,
            'curser' : 0,
            0: None,
            1: None,
            2: None,
        }

    ### Getter
    def get_strength(self):
        return self.save_file['current']['player']['strength']

    def get_movie(self, id):
        # Return movie based on id
        save = self.save_file['current']
        try:
            return save['movie'][id]
        except Exception:
            return None
    def get_all_movie(self):
        return self.save_file['current']['movie']

    def get_movies_array(self):
        tab = []
        movies = self.save_file['current']['movie']
        for index, movie in enumerate(self.save_file['current']['movie']):
            tab.append(movie)
        return tab

    def get_movie_rand(self):
        tab = []
        for index, movie in enumerate(self.save_file['current']['movie']):
            if movie['catched'] == False:
                tab.append(index)
        if (len(tab) == 0):
            return None
        return random.choice(tab)

    def get_coord(self):
        save = self.save_file['current']
        return save['player']['coord']

    #def get_coord_percent(self):
    #    coord = self.save_file['current']['player']['coord']
    #    coord = [coord[0]/ settings.SIZE_X, coord[1] / settings.SIZE_Y]

    def get_coord_percentY(self):
        coord = self.save_file['current']['player']['coord']
        return coord[1] / settings.SIZE_Y * 87

    def get_coord_percentX(self):
        coord = self.save_file['current']['player']['coord']
        return coord[0] / settings.SIZE_X * 91

    def get_balls(self):
        return self.save_file['current']['player']['ball']

    def get_strength(self):
        return self.save_file['current']['player']['strength']

    def add_ball(self):
        if self.save_file['current']['player']['ball'] < 9:
            self.save_file['current']['player']['ball'] += 1

    def get_save_file(self):
        return self.save_file

    def get_movie_catched(self, id):
        n = 0

        for movie in self.save_file[id]['movie']:
            if movie['catched']:
                n += 1
        return n

    def get_movie_count(self, id):
        return len(self.save_file[id]['movie'])

    def del_ball(self):
        if self.save_file['current']['player']['ball'] > 0:
            self.save_file['current']['player']['ball'] -= 1

    # Setter
    def set_active_file(self, num):
        print("******* LOADING NEW SAVE *******")
        self.save_file['active'] = num
        self.save_file['current'] = self.save_file[num]

    def set_save(self, num):
        print("******* SAVING *******")
        #self.save_file['active'] = num
        #print(self.save_file[num]['player']['dir'])
        self.save_file[num] = copy.deepcopy(self.save_file['current'])
        #print(self.save_file[num]['player']['dir'])



    ### Model action
    def new_file(self, num):
        if __name__ == '__main__':
            c = [5, 5]
        else:
            c = [settings.START_X, settings.START_Y]
        self.save_file['current'] = {
            'player' : {
                'strength' : 1,
                'dir' : 0,
                'ball' : 5000,
                'coord' : c,
            },
            'movie' : {},
        }

        omdb.set_default('apikey', settings.OMDBAPI_KEY)
        movies = []
        for movie in settings.MOVIE_LIST:
            data = omdb.imdbid(movie)
            movies.append({
                'name': data['title'],
                'strength': int(float(data['imdb_rating'])),
                'rating': data['imdb_rating'],
                'actors': data['actors'],
                'year': data['released'].split(' ')[2],
                'image': data['poster'],
                'director': data['director'],
                'catched': False,
            })

        self.save_file['current']['movie'] = movies

    def strength_up(self):
        self.save_file['current']['player']['strength'] += 1

    def getdir(self):
        return self.save_file['current']['player']['dir']

    def setdir(self, dir):
        self.save_file['current']['player']['dir'] = dir

    def catch_movie(self, id):
        self.save_file['current']['movie'][id]['catched'] = True

    # Movement
    def go_up(self):
        if self.save_file['current']['player']['coord'][1] > 0:
            self.save_file['current']['player']['coord'][1] -= 1

    def go_down(self):
        if self.save_file['current']['player']['coord'][1] < settings.SIZE_Y:
            self.save_file['current']['player']['coord'][1] += 1

    def go_left(self):
        if self.save_file['current']['player']['coord'][0] > 0:
            self.save_file['current']['player']['coord'][0] -= 1

    def go_right(self):
        if self.save_file['current']['player']['coord'][0] < settings.SIZE_X:
            self.save_file['current']['player']['coord'][0] += 1

    def find_random(self):
        return (5 == random.randint(2, 8))


if __name__ == '__main__':
    c = DataManagment()
    settings.configure()

    # Load without file
    c.load()

    c.set_active_file(0)

    print("Coord :", c.get_coord())
    print("Strength :", c.get_strength())
    c.strength_up()
    print("Strength up :", c.get_strength())

    c.dump()

    c.load()
    print("\nRound 2:\nCoord :", c.get_coord())
    print("Strength :", c.get_strength())
    c.strength_up()
    print("Strength up :", c.get_strength())

    c.go_up()
    print("Coord :", c.get_coord())
    c.go_up()
    c.go_up()
    c.go_up()
    c.go_up()
    print("Coord :", c.get_coord())
    c.go_up()
    c.go_up()
    c.go_up()
    print("Coord :", c.get_coord())

    print(c.get_movie_rand())
    #c.new_file(0)

    #m = c.get_movie(0)
    #print(m['name'], m['strength'], m['catched'])

    #c.catch_movie(0)
    #m = c.get_movie(0)
    #print(m['name'], m['strength'], m['catched'])

