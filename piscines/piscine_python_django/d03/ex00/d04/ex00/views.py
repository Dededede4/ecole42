from django.shortcuts import render, HttpResponse

# Create your views here.
def bar(request):
	return render(request, "./index.html")