from django.urls import path
from . import views
urlpatterns = [
    path('', views.title_screen, name='title_screen'),
    path('worldmap', views.worldmap, name='worldmap'),
    
    path('new', views.title_screen_new_game, name='title_screen_new_game'),
    path('addball', views.add_ball, name='addball'),
    path('worldmap/right', views.worldmap_turn_right, name='worldmap_right'),
    path('worldmap/up', views.worldmap_turn_up, name='worldmap_up'),
    path('worldmap/down', views.worldmap_turn_down, name='worldmap_down'),
    path('worldmap/left', views.worldmap_turn_left, name='worldmap_left'),
    path('battle/<int:id>/', views.battle, name='battle'),
    path('battle/try/<int:id>/', views.battle_try, name='battletry'),
    path('moviedex', views.moviedex, name='moviedex'),
    path('moviedex/<int:pos>/', views.moviedex, name='moviedex_pos'),
    path('detail', views.detail, name='detail'),
    path('detail/<int:id>/', views.detail, name='detail'),
    path('options', views.option, name='option'),
    path('options/save_game', views.save, name='save_list'),
    path('options/save_game/<int:pass42>', views.save, name='save_pass'),
    path('options/save_real_game/<int:id>', views.savereal, name='save_real'),
    
    path('options/load_game/<int:id>', views.load_pass, name='load_pass'),
    path('options/save_game/<int:id>', views.save, name='save_pass'),
    path('options/load_real_game/<int:id>', views.load_real, name='load_real'),
]
