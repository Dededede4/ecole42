from django.shortcuts import render

# Create your views here.
def truc(request):
	return render(request, "./index.html")