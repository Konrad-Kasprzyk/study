from django.contrib import admin

# Register your models here.
from .models import Wydarzenie, Osoba

admin.site.register(Wydarzenie)
admin.site.register(Osoba)