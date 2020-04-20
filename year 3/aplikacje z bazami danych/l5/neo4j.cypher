//match (n:Ksiazka) delete n
create (:Ksiazka{
    ISBN: '83-246-0279-8',
    Tytul: 'Microsoft Access. Podrecznik administratora',
    Autor: 'Helen Feddema',
    Rok_Wydania: 2006,
    Cena: 69
})

create (:Ksiazka{
    ISBN: '83-246-0653-X',
    Tytul: 'SQL Server 2005. Programowanie. Od podstaw',
    Autor: 'Robert Vieira',
    Rok_Wydania: 2007,
    Cena: 97
})

create (:Egzemplarz{
    Sygnatura: 'S0001'
})

create (:Egzemplarz{
    Sygnatura: 'S0002'
})

create (:Egzemplarz{
    Sygnatura: 'S0003'
})

create (:Czytelnik{
    PESEL: '55101011111',
    Nazwisko: 'Kowalski',
    Miasto: 'Wroclaw',
    Data_Urodzenia: date('1955-10-10'),
    Ostatnie_Wypozyczenie: date('2020-02-01')
})

create (:Czytelnik{
    PESEL: '60101033333',
    Nazwisko: 'Maliniak',
    Miasto: 'Wroclaw',
    Data_Urodzenia: date('1960-10-10'),
    Ostatnie_Wypozyczenie: date('2020-03-01')
})

match 
(a:Ksiazka {Tytul: 'Microsoft Access. Podrecznik administratora'}),
(b:Egzemplarz {Sygnatura: 'S0001'})
merge
(a)-[:Zawiera]->(b)

match 
(a:Ksiazka {Tytul: 'SQL Server 2005. Programowanie. Od podstaw'}),
(b:Egzemplarz {Sygnatura: 'S0002'})
merge
(a)-[:Zawiera]->(b)

match 
(a:Ksiazka {Tytul: 'SQL Server 2005. Programowanie. Od podstaw'}),
(b:Egzemplarz {Sygnatura: 'S0003'})
merge
(a)-[:Zawiera]->(b)

// match
// (:Ksiazka) -[r:Zawiera]-> (:Egzemplarz)
// delete r

match 
(a:Czytelnik {PESEL: '55101011111'}),
(b:Egzemplarz {Sygnatura: 'S0001'})
merge
(a)-[:Wypozyczyl {Data: date('2019-12-01'), Liczba_Dni: 30}]->(b)

match 
(a:Czytelnik {PESEL: '55101011111'}),
(b:Egzemplarz {Sygnatura: 'S0002'})
merge
(a)-[:Wypozyczyl {Data: date('2020-02-01'), Liczba_Dni: 30}]->(b)

match 
(a:Czytelnik {PESEL: '60101033333'}),
(b:Egzemplarz {Sygnatura: 'S0001'})
merge
(a)-[:Wypozyczyl {Data: date('2020-03-01'), Liczba_Dni: 60}]->(b)

match 
(a:Czytelnik {PESEL: '60101033333'}),
(b:Egzemplarz {Sygnatura: 'S0003'})
merge
(a)-[:Wypozyczyl {Data: date('2020-01-15'), Liczba_Dni: 30}]->(b)

CREATE CONSTRAINT peselC
ON (n:Czytelnik)
ASSERT n.PESEL IS UNIQUE

CREATE CONSTRAINT sygnaturaC
ON (n:Egzemplarz)
ASSERT n.Sygnatura IS UNIQUE

// Znajdź czytelnika, który wypożyczył chociaż jedną książkę na 30 dni
match
(a:Czytelnik)-[r:Wypozyczyl]->(b:Egzemplarz)
where
r.Liczba_Dni=30
return distinct
a.Nazwisko

// Znajdź czytelników, którzy urodzili się przed 1960 rokiem
match
(a:Czytelnik)
where
a.Data_Urodzenia < date('1960-1-1')
return
a

// Znajdź ile jest egzemplarzy danej ksiazki
match
(a:Ksiazka)-[r:Zawiera]->(b:Egzemplarz)
return
a.Tytul, count(r)

// Znajdź ile osób wypożyczyło daną książkę
match
(a:Czytelnik) - [:Wypozyczyl] -> (:Egzemplarz) <- [:Zawiera] - (b:Ksiazka)
return
b.Tytul, count(distinct a)

// Zmien cenę książki
match
(n:Ksiazka {Tytul:'Microsoft Access. Podrecznik administratora'})
set
n.Cena = 59

// Dodaj egzemplarz ksiazki. Merge to match-or-create
match
(a:Ksiazka {Tytul: 'Microsoft Access. Podrecznik administratora'})
merge
(a)-[:Zawiera]->(:Egzemplarz {Sygnatura: 'S0004'})

// Cofnij te zmianę
match
(:Ksiazka {Tytul: 'Microsoft Access. Podrecznik administratora'})
-[r:Zawiera]->(n:Egzemplarz {Sygnatura: 'S0004'})
delete r,n

// Usun czytelnika, detach usuwa także wszystkie relacje
match
(n:Czytelnik {PESEL: "60101033333"})
detach delete n