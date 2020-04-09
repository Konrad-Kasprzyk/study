-- Zadanie 1 --
-- duzo info: https://sqlchris.wordpress.com/2017/06/25/poziomy-izolacji-transakcji-sql-server/
-- Odczyt brudnych danych --
DROP TABLE IF EXISTS Magazyn
GO
 
CREATE TABLE Magazyn (ID INT PRIMARY KEY, Produkt VARCHAR(50), LiczbaSztuk INT)
INSERT INTO Magazyn VALUES(1, 'piłka', 13)
INSERT INTO Magazyn VALUES(2, 'kij', 3)
INSERT INTO Magazyn VALUES(3, 'bramka', 4)
INSERT INTO Magazyn VALUES(4, 'rower', 6)
INSERT INTO Magazyn VALUES(5, 'ochraniacze', 1)
GO
 
/*
Sposób działania: odpalamy w dwóch okienkach SSMS, pierwszą transakcję wykonujemy normalnie, po czym
jednocześnie włączamy drugą. Oczekiwanym wynikiem byłoby wyświetlenie 12 piłek i 3 rowerów w drugiej
transakcji, gdyż została ona wykonana jednocześnie z pierwszą, jednak przez to, że musimy czekać do
momentu wykonania pierwszej transakcji (i rollbacku), drugie zapytanie wyświetli niezmienione dane.
*/
 
-- Transakcja 1 --
BEGIN TRAN
UPDATE Magazyn SET LiczbaSztuk = 99 WHERE ID = 1
UPDATE Magazyn SET LiczbaSztuk = 99  WHERE ID = 4
-- czekamy na przyjęcie pieniędzy od klienta, stąd delay
WAITFOR DELAY '00:00:08'
SELECT * FROM Magazyn -- dane zmieniaja sie, ale rollback je cofa
ROLLBACK TRANSACTION
 
-- Transakcja 2 --
set transaction isolation level read uncommitted; -- występują brudne odczyty
set transaction isolation level read committed;  -- nie ma brudnych odczytów
SELECT * FROM Magazyn
 
-- Niepowtarzalość odczytów --
DROP TABLE IF EXISTS Ludzie
GO
 
CREATE TABLE Ludzie (Imie VARCHAR(20), Nazwisko VARCHAR(20), Wiek INT)
INSERT INTO Ludzie VALUES('Tomasz', 'Gąbka', 15)
INSERT INTO Ludzie VALUES('Arnold', 'Masło', 33)
INSERT INTO Ludzie VALUES('Arek', 'Nowak', 23)
INSERT INTO Ludzie VALUES('Michał', 'Kowalski', 13)
INSERT INTO Ludzie VALUES('Oskar', 'Nowacki', 20)
INSERT INTO Ludzie VALUES('Luke', 'Smith', 22)
GO
 
/*
Sposób działania jak przy odczycie brudnych danych, tutaj dochodzi do sytuacji, w której dane są
zmieniane w drugiej transakcji, przez co dwa odczyty danych w pierwszej transakcji zwracają inne
wyniki.
*/
 
-- Transakcja 1 --
set transaction isolation level read committed;  -- występuje niepowtarzalość odczytów
set transaction isolation level repeatable read; -- tutaj nie
BEGIN TRAN
SELECT * FROM Ludzie
WAITFOR DELAY '00:00:08'
SELECT * FROM Ludzie
ROLLBACK
GO
 
-- Transakcja 2 --
BEGIN TRAN
UPDATE Ludzie SET Wiek = 50 WHERE Imie = 'Tomasz' OR Imie = 'Oskar'
COMMIT
GO
 
-- Odczyty fantomów ``
DROP TABLE IF EXISTS Samochody
GO
 
CREATE TABLE Samochody (Model VARCHAR(20), Marka VARCHAR(20))
INSERT INTO Samochody VALUES('Opel', 'Astra')
INSERT INTO Samochody VALUES('Opel', 'Meriva')
INSERT INTO Samochody VALUES('Skoda', 'Fabia')
INSERT INTO Samochody VALUES('Skoda', 'Superb')
INSERT INTO Samochody VALUES('Skoda', 'Felicia')
GO

SELECT * FROM Samochody
 
/*
Sposób działania jak wyżej, jednak przy odczytach zmienia się liczba odczytywanych danych
spowodowana działaniem INSERT lub DELETE.
*/
 
-- Transakcja 1 --
set transaction isolation level repeatable read; -- występuje odczyt fantomów
set transaction isolation level serializable; -- tutaj nie
BEGIN TRAN
SELECT * FROM Samochody WHERE Model = 'Opel'
WAITFOR DELAY '00:00:08'
SELECT * FROM Samochody WHERE Model = 'Opel'
ROLLBACK
 
-- Transakcja 2 --
BEGIN TRAN
INSERT INTO Samochody VALUES('Opel', 'Cascada')
-- DELETE FROM Samochody WHERE Model = 'Opel' and Marka = 'Astra' -- to powinien też być odczyt fantomów, ale repeatable read przed tym chroni
COMMIT
GO
 
 