-- Zadanie 1 --
DROP TABLE IF EXISTS Towary
GO

CREATE TABLE Towary(ID INT PRIMARY KEY, NazwaTowaru VARCHAR(50))
GO

INSERT INTO Towary VALUES(1, 'snickers')
INSERT INTO Towary VALUES(2, 'bounty')
INSERT INTO Towary VALUES(3, 'mars')
GO

DROP TABLE IF EXISTS Kursy
GO

CREATE TABLE Kursy(Waluta VARCHAR(3) PRIMARY KEY, CenaPLN MONEY)
GO

INSERT INTO Kursy VALUES('PLN', 1.00)
INSERT INTO Kursy VALUES('EUR', 4.56)
INSERT INTO Kursy VALUES('NOK', 0.39)
INSERT INTO Kursy VALUES('KWD', 13.20)
INSERT INTO Kursy VALUES('JPY', 0.038)
GO

DROP TABLE IF EXISTS Ceny
GO

CREATE TABLE Ceny(TowarID INT REFERENCES Towary(ID), Waluta VARCHAR(3) REFERENCES Kursy(Waluta), Cena MONEY)
GO
-- jen japonski nie jest obslugiwany, wiec usuwamy ten rekord
-- aktualne wpisy nalezy nadpisac nowa waluta albo stworzyc nowe
-- 1 -> PLN, JPY, EUR, NOK
-- 2 -> PLN, KWD
-- 3 -> PLN, NOK
INSERT INTO Ceny VALUES(1, 'PLN', 1.00)
INSERT INTO Ceny VALUES(2, 'PLN', 2.00)
INSERT INTO Ceny VALUES(3, 'PLN', 1.79)
INSERT INTO Ceny VALUES(1, 'JPY', 78.27)
INSERT INTO Ceny VALUES(1, 'EUR', 1.55)
INSERT INTO Ceny VALUES(1, 'NOK', 10.09)
INSERT INTO Ceny VALUES(2, 'KWD', 0.99)
INSERT INTO Ceny VALUES(3, 'NOK', 4.39)
GO 

ALTER TABLE Ceny NOCHECK CONSTRAINT ALL
DELETE from Kursy WHERE Waluta = 'JPY'
ALTER TABLE Ceny CHECK CONSTRAINT ALL
GO

DECLARE z1towary CURSOR FOR SELECT TowarID, Waluta, Cena FROM Ceny ORDER BY TowarID
DECLARE z1waluty CURSOR FOR SELECT Waluta, CenaPLN FROM Kursy

DECLARE @Ttowarid INT, @Twaluta VARCHAR(3), @Tcena MONEY
DECLARE @Curr_towarid INT, @Curr_cenaPLN MONEY
DECLARE @Wwaluta VARCHAR(3), @Wkurs MONEY
DECLARE @delete BIT

OPEN z1towary
FETCH NEXT FROM z1towary INTO @Ttowarid, @Twaluta, @Tcena
SET @Curr_towarid = @Ttowarid
SET @Curr_cenaPLN = (SELECT Cena from Ceny WHERE TowarID = @Curr_towarid AND Waluta = 'PLN')
WHILE (@@FETCH_STATUS = 0)
BEGIN
	-- PRINT 'O: ID: ' + CAST(@Ttowarid AS CHAR(3)) + ' Waluta: ' + CAST(@Twaluta AS CHAR(3)) + ' Cena: ' + CAST(@Tcena AS CHAR(5))
	OPEN z1waluty
	FETCH NEXT FROM z1waluty INTO @Wwaluta, @Wkurs
	SET @delete = 1
	WHILE (@@FETCH_STATUS = 0)
	BEGIN
		IF (@Twaluta = @Wwaluta)
		BEGIN
			SET @Tcena = @Curr_cenaPLN * @Wkurs
			UPDATE Ceny SET Cena = @Tcena WHERE TowarID = @Ttowarid AND Waluta = @Twaluta
			SET @delete = 0
		END
		FETCH NEXT FROM z1waluty INTO @Wwaluta, @Wkurs
	END
	IF @delete=1
		DELETE FROM Ceny WHERE TowarID = @Ttowarid AND Waluta = @Twaluta
	CLOSE z1waluty
	FETCH NEXT FROM z1towary INTO @Ttowarid, @Twaluta, @Tcena
	IF @Curr_towarid != @Ttowarid
	BEGIN
		SET @Curr_towarid = @Ttowarid
		SET @Curr_cenaPLN = (SELECT Cena from Ceny WHERE TowarID = @Curr_towarid AND Waluta = 'PLN')
	END
END
CLOSE z1towary
DEALLOCATE z1waluty
DEALLOCATE z1towary
GO

SELECT * FROM Ceny ORDER BY TowarID, Waluta DESC
GO