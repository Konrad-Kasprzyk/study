-- Zadanie 2 --
-- Tabelka główna z zadania do normalizacji --
DROP TABLE IF EXISTS Wizyty
GO
 
CREATE TABLE Wizyty(
    [ID]                    INT PRIMARY KEY,
    [Pacjent]               VARCHAR(50),
    [Adres Pacjenta]        VARCHAR(100),
    [Data i miejsce wizyty] VARCHAR(100),
    [Kwota]                 MONEY,
    [Lekarz]                VARCHAR(50),
    [Powód wizyty]         VARCHAR(100))
 
INSERT INTO Wizyty VALUES
(1, 'Jan Kot', 'ul. Dolna 6, 44-444 Bór', '2029-02-01 12:30, pok. 12', 300, 'Oleg Wyrwiząb', 'Dentystyczny: założenie protezy w (...)'),
(2, 'Maria Mysz', 'ul. Górna 9, 55-555 Las', '2030-01-04 11:45, pok. 7', 150, 'Ewa Ciarka', 'Dermatologiczny: oględziny znamiona (...)')
GO
 
SELECT * FROM Wizyty
GO
 
-- Tabelka w 1NF --
DROP TABLE IF EXISTS Wizyty1NF
GO
 
CREATE TABLE Wizyty1NF(
    [ID]                    INT PRIMARY KEY,
    [Pacjent]               VARCHAR(50),
    [Adres]                 VARCHAR(50),
    [Kod pocztowy]          VARCHAR(10),
    [Miasto]                VARCHAR(30),
    [Data wizyty]           SMALLDATETIME,
    [Miejsce wizyty (pok)]  INT,
    [Kwota]                 MONEY,
    [Lekarz]                VARCHAR(50),
    [Typ wizyty]            VARCHAR(30),
    [Powód wizyty]         VARCHAR(100))
 
INSERT INTO Wizyty1NF VALUES
(1, 'Jan Kot',    'ul. Dolna 6', '44-444', 'Bór', '2029-02-01 12:30', 12, 300, 'Oleg Wyrwiząb', 'Dentystyczny',    'Założenie protezy w (...)'),
(2, 'Maria Mysz', 'ul. Górna 9', '55-555', 'Las', '2030-01-04 11:45', 7,  150, 'Ewa Ciarka',   'Dermatologiczny', 'Oględziny znamiona (...)')
GO
 
SELECT * FROM Wizyty1NF
GO
 
-- Tabelki w 2NF
DROP TABLE IF EXISTS Pacjenci
GO
 
CREATE TABLE Pacjenci(
    [ID]                    INT PRIMARY KEY,
    [Pacjent]               VARCHAR(50),
    [Adres]                 VARCHAR(50),
    [Kod pocztowy]          VARCHAR(10),
    [Miasto]                VARCHAR(30))
 
INSERT INTO Pacjenci VALUES
(1, 'Jan Kot',    'ul. Dolna 6', '44-444', 'Bór'),
(2, 'Maria Mysz', 'ul. Górna 9', '55-555', 'Las')
GO
 
SELECT * FROM Pacjenci
GO
 
DROP TABLE IF EXISTS Wizyty2NF 
GO
 
CREATE TABLE Wizyty2NF(
    [ID Pacjenta]           INT,
    [Data wizyty]           SMALLDATETIME,
    [Miejsce wizyty (pok)]  INT,
    [Kwota]                 MONEY,
    [Lekarz]                VARCHAR(50),
    [Typ wizyty]            VARCHAR(30),
    [Powód wizyty]         VARCHAR(100))
 
INSERT INTO Wizyty2NF VALUES
(1, '2029-02-01 12:30', 12, 300, 'Oleg Wyrwiząb', 'Dentystyczny',    'Założenie protezy w (...)'),
(2, '2030-01-04 11:45', 7,  150, 'Ewa Ciarka',    'Dermatologiczny', 'Oględziny znamiona (...)')
GO
 
SELECT * FROM Wizyty2NF
GO
 
SELECT * FROM Pacjenci JOIN Wizyty2NF ON Pacjenci.ID = Wizyty2NF.[ID Pacjenta]
GO
 
-- Tabelki 3NF
DROP TABLE IF EXISTS Miasta
GO
 
CREATE TABLE Miasta(
		[Miasto]                VARCHAR(30),
		[Kod pocztowy]          VARCHAR(10))

DROP TABLE IF EXISTS Pacjenci3NF
GO
 
CREATE TABLE Pacjenci3NF(
    [ID]                    INT PRIMARY KEY,
    [Pacjent]               VARCHAR(50),
    [Adres]                 VARCHAR(50),
    [Miasto]                VARCHAR(30))
 
INSERT INTO Miasta VALUES
('Bór','44-444'),
('Las', '55-555')
GO

INSERT INTO Pacjenci3NF VALUES
(1, 'Jan Kot',    'ul. Dolna 6', 'Bór'),
(2, 'Maria Mysz', 'ul. Górna 9', 'Las')
GO

SELECT * FROM Pacjenci3NF
SELECT * FROM Miasta
SELECT * FROM Wizyty2NF
GO
 
SELECT * FROM Pacjenci3NF JOIN Miasta ON Pacjenci3NF.Miasto = Miasta.Miasto
JOIN Wizyty2NF ON Pacjenci3NF.ID = Wizyty2NF.[ID Pacjenta]
GO