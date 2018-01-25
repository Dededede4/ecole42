from django.conf.urls import url
from . import views

urlpatterns = [
	url('^ex01/django$', views.django),
	url('^ex01/affichage', views.affichage),
	url('^ex01/templates', views.templates),
]