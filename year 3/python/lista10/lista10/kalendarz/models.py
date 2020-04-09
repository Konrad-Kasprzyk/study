from django.db import models
from django.utils import timezone


# Create your models here.
class Osoba(models.Model):
    imie = models.TextField(blank=False, null=False, max_length="50")
    nazwisko = models.TextField(blank=False, null=False, max_length="50")
    email = models.TextField(blank=False, null=False, max_length="50")

    class Meta:
        verbose_name = 'osoba'
        verbose_name_plural = 'osoby'

    def __str__(self):
        return "imie: %s, nazwisko: %s, email: %s" % (self.imie, self.nazwisko, self.email)


class Wydarzenie(models.Model):
    data_wydarzenia = models.DateField(default=timezone.now())
    godz_rozpoczecia = models.TimeField(default=timezone.now())
    godz_zakonczenia = models.TimeField(default=timezone.now())
    opis = models.TextField(blank=True, null=True, max_length="500")
    # bo jedna osoba może pójść na wiele wydarzeń i jedno wydarzenie ma wiele uczestników
    uczestnicy = models.ManyToManyField(Osoba)

    class Meta:
        verbose_name = 'wydarzenie'
        verbose_name_plural = 'wydarzenia'
