from django.shortcuts import render
from django.shortcuts import redirect
from django.http import HttpResponse
from django.conf import settings
from django.http import Http404  

import random

from . import DataManagment

def title_screen(request):
    return render(request, 'thegame/title_screen.html')

def title_screen_new_game(request):
    dm = DataManagment.DataManagment()
    dm.new_file(-42)
    dm.dump()
    dm.load()
    return redirect('worldmap')

def add_ball(request):
    dm = DataManagment.DataManagment()
    dm.add_ball()
    dm.dump()
    return redirect('worldmap')

def worldmap(request):
    referer = request.META.get('HTTP_REFERER')
    dm = DataManagment.DataManagment()
    goBall = False
    goFight = False
    if dm.find_random():
        goBall = True
    elif dm.find_random():
        goFight = True
    movieid = dm.get_movie_rand()
    return render(request, 'thegame/worldmap.html', {'dm' : dm, 'goBall' : goBall, 'goFight': goFight, 'movieid':movieid })

def worldmap_turn_right(request):
    dm = DataManagment.DataManagment()
    dm.go_right()
    dm.setdir(2)
    dm.dump()
    return redirect('worldmap')

def worldmap_turn_left(request):
    dm = DataManagment.DataManagment()
    dm.go_left()
    dm.setdir(1)
    dm.dump()
    return redirect('worldmap')

def worldmap_turn_up(request):
    dm = DataManagment.DataManagment()
    dm.go_up()
    dm.setdir(3)
    dm.dump()
    return redirect('worldmap')

def worldmap_turn_down(request):
    dm = DataManagment.DataManagment()
    dm.go_down()
    dm.setdir(0)
    dm.dump()
    return redirect('worldmap')

def battle(request, id):
    dm = DataManagment.DataManagment()
    movie = dm.get_movie(id)
    if movie == None:
        return redirect('worldmap')
    chance = 50 - (movie['strength'] * 10) + (dm.get_strength() * 5)
    if (chance <= 1):
        chance = 1
    elif (chance >= 90):
        chance = 90
    return render(request, 'thegame/battle.html', {'id':id, 'movie': movie, 'chance': chance, 'dm': dm, 'try': False, 'success': False})

def battle_try(request, id):
    dm = DataManagment.DataManagment()
    if (dm.get_balls() == 0):
        return redirect('worldmap')
    movie = dm.get_movie(id)
    if movie == None:
        return redirect('worldmap')
    chance = 50 - (movie['strength'] * 10) + (dm.get_strength() * 5)
    if (chance <= 1):
        chance = 1
    elif (chance >= 90):
        chance = 90
    dm.del_ball()

    success = False
    if ((chance - 1) >= random.randint(0, 100)):
        dm.catch_movie(id)
        dm.strength_up()
        success = True

    dm.dump()
    dm.load()
    return render(request, 'thegame/battle.html', {'id':id, 'movie': movie, 'chance': chance, 'dm': dm, 'try': True, 'success': success})

def moviedex(request, pos = 0):
    data = DataManagment.DataManagment()

    movies = data.get_movies_array();
    stop = pos + 8
    nextpos = 0
    pastpos = 0
    if (pos < len(movies) - 1):
        nextpos = pos + 1
    else:
        nextpos = len(movies) - 1
    if (pos > 0):
        pastpos = pos - 1
    else:
        pastpos = 0
    context = {'movies' : movies[pos:stop], 'pos': pos, 'next' : nextpos, 'past' : pastpos}
    return render(request, 'thegame/moviedex.html', context)

def detail(request, id = None):
    data = DataManagment.DataManagment()

    if id == None:
        return worldmap(request)
    try:
        context = data.get_movie(int(id))
        return render(request, 'thegame/detail.html', context)
    except Exception:
        return worldmap(request)

def option(request):
    return render(request, 'thegame/option.html')

def save(request, pass42 = 0):
    dm = DataManagment.DataManagment()

    data = dm.get_save_file()

    context = {
        'cursor': pass42,
        'prev': (pass42 - 1) % 3,
        'next': (pass42 + 1) % 3,
    }
    context['A'] = True
    context['B'] = True
    context['C'] = True
    if data[0] == None:
        context['A'] = False
    else:
        context['maxA'] = dm.get_movie_count(0)
        context['countA'] = dm.get_movie_catched(0)
    if data[1] == None:
        context['B'] = None
    else:
        context['maxB'] = dm.get_movie_count(1)
        context['countB'] = dm.get_movie_catched(1)
    if data[2] == None:
        context['C'] = None
    else:
        context['maxC'] = dm.get_movie_count(2)
        context['countC'] = dm.get_movie_catched(2)
    context['current'] = pass42 % 3
    context['next'] = (pass42 + 1) % 3
    context['prev'] = (pass42 - 1) % 3
    return render(request, 'thegame/save.html', context)

def savereal(request, id = 0):
    dm = DataManagment.DataManagment()

    dm.set_save(id)
    dm.dump(True)
    return worldmap(request)

def load_pass(request, id = 0):
    dm = DataManagment.DataManagment()

    data = dm.get_save_file()

    context = {
        'cursor': id,
        'prev': (id - 1) % 3,
        'next': (id + 1) % 3,
    }
    context['A'] = True
    context['B'] = True
    context['C'] = True
    if data[0] == None:
        context['A'] = False
    else:
        context['maxA'] = dm.get_movie_count(0)
        context['countA'] = dm.get_movie_catched(0)
    if data[1] == None:
        context['B'] = None
    else:
        context['maxB'] = dm.get_movie_count(1)
        context['countB'] = dm.get_movie_catched(1)
    if data[2] == None:
        context['C'] = None
    else:
        context['maxC'] = dm.get_movie_count(2)
        context['countC'] = dm.get_movie_catched(2)
    return render(request, 'thegame/load.html', context)

def load_real(request, id ):
    dm = DataManagment.DataManagment()

    data = dm.get_save_file()
    if data[id] != None:
        dm.set_active_file(id)
        dm.dump(True)
        return worldmap(request)
    else:
        return load_pass(request, id)