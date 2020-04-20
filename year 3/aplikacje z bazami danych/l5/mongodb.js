//use biblioteka
//show collections
//db.ksiazki.remove({})
db.createCollection("ksiazki")
db.createCollection("czytelnicy")
db.createCollection("counters")

db.counters.insert({
	"_id":"ksiazki_id",
	"sequence_value": 0
})

db.system.js.save(
    {
        _id: "getNextSequenceValue",
        value : function(sequenceName) { 
            var sequenceDocument = db.counters.findAndModify({
                query:{_id: sequenceName },
                update: {$inc:{sequence_value:1}},
                new:true
            });
            return sequenceDocument.sequence_value; }
    }
)

db.loadServerScripts();

db.ksiazki.insert({
    _id: getNextSequenceValue("ksiazki_id"),
    ISBN: '83-246-0279-8',
    Tytul: "Microsoft Access. Podrecznik administratora",
    Autor: "Helen Feddema",
    Rok_Wydania: 2006,
    Cena: 69,
    Egzemplarze: [
        {
            Sygnatura: "S0001"
        }
    ]
})

db.ksiazki.insert({
    _id: getNextSequenceValue("ksiazki_id"),
    ISBN: '83-246-0653-X',
    Tytul: "SQL Server 2005. Programowanie. Od podstaw",
    Autor: "Robert Vieira",
    Rok_Wydania: 2007,
    Cena: 97,
    Egzemplarze: [
        {
            Sygnatura: "S0002"
        },
        {
            Sygnatura: "S0003"
        }
    ]
})

db.czytelnicy.insert({
    PESEL: "55101011111",
    Nazwisko: "Kowalski",
    Miasto: "Wroclaw",
    Data_Urodzenia: new Date("1955-10-10"),
    Ostatnie_Wypozyczenie: new Date("2020-02-01"),
    wypozyczenia: [
        {   
            sygnatura_egzemplarza: "S0002",
            Data: new Date("2020-02-01"),
            Liczba_Dni: 30
        },
        {   
            sygnatura_egzemplarza: "S0001",
            Data: new Date("2019-12-01"),
            Liczba_Dni: 30
        }
    ]
})

db.czytelnicy.insert({
    PESEL: "60101033333",
    Nazwisko: "Maliniak",
    Miasto: "Wroclaw",
    Data_Urodzenia: new Date("1960-10-10"),
    Ostatnie_Wypozyczenie: new Date("2020-03-01"),
    wypozyczenia: [
        {   
            sygnatura_egzemplarza: "S0001",
            Data: new Date("2020-03-01"),
            Liczba_Dni: 60
        },
        {   
            sygnatura_egzemplarza: "S0003",
            Data: new Date("2020-01-15"),
            Liczba_Dni: 30
        }
    ]
})


// Znajdź czytelnika, który wypożyczył chociaż jedną książkę na 30 dni
db.czytelnicy.find( {"wypozyczenia.Liczba_Dni": 30}).pretty();

// Znajdź czytelników, którzy urodzili się przed 1960 rokiem
db.czytelnicy.find( {Data_Urodzenia: {$lt: new Date("1960-01-01")}}).pretty();


// Znajdź ile jest egzemplarzy danej ksiazki
// grupowanie po tytule, dla każdego tytułu liczę ile ma egzemplarzy
db.ksiazki.aggregate([{
    $group : {
        _id : "$Tytul",
        ilosc_egzemplarzy : {$sum : {$size: "$Egzemplarze"}}}
}])


// Znajdź ile osób wypożyczyło daną książkę
db.ksiazki.aggregate([
    // Join
    {
        $lookup:{
            from: "czytelnicy",
            localField: "Egzemplarze.Sygnatura",
            foreignField: "wypozyczenia.sygnatura_egzemplarza",
            as: "Czytelnicy"
        }
    },
    {
        $group : {
            _id : "$Tytul",
            ile_wypozyczen : {$sum : {$size: "$Czytelnicy"}}
        }
    }
]).pretty();

// Zmien cenę książki
db.ksiazki.update({Tytul: "Microsoft Access. Podrecznik administratora"}, {$set: {Cena: 59}});

// Dodaj egzemplarz ksiazki
db.ksiazki.update(
    { Tytul: "Microsoft Access. Podrecznik administratora" },
    { $push: { Egzemplarze: { Sygnatura: "S0004" } } });

// Usun czytelnika
db.czytelnicy.remove({PESEL: "60101033333"})
