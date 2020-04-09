from kalendarz.models import Osoba, Wydarzenie
import datetime
from django.core.management.base import BaseCommand, CommandError


class Command(BaseCommand):
    def add_arguments(self, parser):
        parser.add_argument('arg1', type=str, nargs='?', default="")
        parser.add_argument('arg2', type=str, nargs='?', default="")
        parser.add_argument('arg3', type=str, nargs='?', default="")
        parser.add_argument('arg4', type=str, nargs='?', default="")
        parser.add_argument('arg5', type=str, nargs='?', default="")
        parser.add_argument('arg6', type=str, nargs='?', default="")
        parser.add_argument('arg7', type=str, nargs='?', default="")
        parser.add_argument('arg8', type=str, nargs='?', default="")
        parser.add_argument('arg9', type=str, nargs='?', default="")

    def handle(self, *args, **options):
        if options['arg1'] == 'wydarzenie':
            data = datetime.date(int(options['arg2']), int(options['arg3']), int(options['arg4']))
            start_godz = datetime.time(int(options['arg5']), int(options['arg6']))
            end_godz = datetime.time(int(options['arg7']), int(options['arg8']))
            wyd = Wydarzenie.objects.create(data_wydarzenia=data, godz_rozpoczecia=start_godz,
                                            godz_zakonczenia=end_godz, opis=options['arg9'])
            wyd.uczestnicy.set([])
            self.stdout.write(
                self.style.SUCCESS("dodano wydarzenie w dniu: {}, godzina rozpoczecia: {}, godzina zakonczenia: {}".
                                   format(data, start_godz, end_godz))
            )
        if options['arg1'] == 'dodaj':
            pk = options['arg2']
            imie = options['arg3']
            nazwisko = options['arg4']
            email = options['arg5']

            try:
                wyd = Wydarzenie.objects.get(pk=int(pk))
            except Osoba.DoesNotExist:
                raise CommandError(
                    f'nie można znaleźć wydarzenia o kluczu podstawowym {pk}')

            try:
                ucz = Osoba.objects.get(imie=imie, nazwisko=nazwisko, email=email)
            except Osoba.DoesNotExist:
                raise CommandError(
                    f'nie można znaleźć osoby o imieniu: {imie}, nazwisku: {nazwisko}, email: {email}')

            wyd.uczestnicy.add(ucz)


        if options['arg1'] == 'osoba':
            imie = options['arg2']
            nazwisko = options['arg3']
            email = options['arg4']
            ucz = Osoba.objects.create(imie=imie, nazwisko=nazwisko, email=email)
            self.stdout.write(
                self.style.SUCCESS("dodano osobe o imieniu: {}, nazwisku: {}, email: {}".
                                   format(imie, nazwisko, email))
            )

        if options['arg1'] == 'wyswietl':
            # wyswietl wszystkie wydarzenia i osoby w tym wydarzeniu
            wydarzenia = Wydarzenie.objects.all()
            for wyd in wydarzenia:
                print("wydarzenie od kluczu podstawowym: ",wyd.pk)
                print(wyd.data_wydarzenia)
                print(wyd.godz_rozpoczecia)
                print(wyd.godz_zakonczenia)
                if not wyd.opis:
                    print("brak opisu")
                else:
                    print(wyd.opis)
                print("uczestnicy wydarzenia:")
                uczestnicy = wyd.uczestnicy.all()
                for os in uczestnicy:
                    print(os)
                print()

