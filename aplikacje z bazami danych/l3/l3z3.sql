-- Zadanie 3 --
DROP TABLE IF EXISTS Bufor
DROP TABLE IF EXISTS Historia
DROP TABLE IF EXISTS Parametry
GO
CREATE TABLE Bufor(ID INT IDENTITY PRIMARY KEY, AdresUrl VARCHAR(200), OstatnieWejscie DATETIME)
CREATE TABLE Historia(ID INT IDENTITY PRIMARY KEY, AdresUrl VARCHAR(200), OstatnieWejscie DATETIME)
CREATE TABLE Parametry(nazwa VARCHAR(200), wartosc INT)
GO

INSERT INTO Parametry VALUES('tiny', 5)

GO
CREATE TRIGGER przenies_do_historii ON Bufor INSTEAD OF INSERT
AS
BEGIN
	DECLARE @I_AdresUrl varchar(200), @I_OstatnieWejscie DATETIME;
	SELECT @I_AdresUrl=AdresUrl, @I_OstatnieWejscie=OstatnieWejscie FROM INSERTED;
	IF EXISTS (SELECT 1 FROM Bufor WHERE AdresUrl=@I_AdresUrl)
		UPDATE Bufor SET OstatnieWejscie=@I_OstatnieWejscie WHERE AdresUrl=@I_AdresUrl;
	ELSE
	BEGIN
		DECLARE @Rows INT,  @MaxRows INT;
		SET @Rows = (SELECT COUNT(*) FROM Bufor);
		SET @MaxRows = (SELECT TOP 1 wartosc FROM Parametry);
		IF (@Rows < @MaxRows)
			INSERT INTO Bufor SELECT AdresUrl, OstatnieWejscie FROM INSERTED
		ELSE
		BEGIN
			DECLARE @B_ID INT, @B_AdresUrl varchar(200), @B_OstatnieWejscie DATETIME
			SELECT TOP 1 @B_ID=ID, @B_AdresUrl=AdresUrl, @B_OstatnieWejscie=OstatnieWejscie FROM Bufor ORDER BY OstatnieWejscie
			IF EXISTS (SELECT 1 FROM Historia WHERE AdresUrl=@B_AdresUrl)
				UPDATE Historia SET OstatnieWejscie=@B_OstatnieWejscie WHERE AdresUrl=@B_AdresUrl
			ELSE
				INSERT INTO Historia VALUES(@B_AdresUrl, @B_OstatnieWejscie)
			DELETE FROM Bufor WHERE ID=@B_ID
			INSERT INTO Bufor SELECT AdresUrl, OstatnieWejscie FROM INSERTED
		END
	END
END
		
GO

INSERT INTO Bufor VALUES('uchoroszczy.pl',		'01/04/2012 11:30:00')
INSERT INTO Bufor VALUES('uchoroszczy.pl',		'01/04/2012 11:30:01')
INSERT INTO Bufor VALUES('PZW.pl',				'01/04/2012 11:30')
INSERT INTO Bufor VALUES('AgresywnaMasa.pl',	'01/04/2012 11:30')
INSERT INTO Bufor VALUES('Allegro.pl',			'01/04/2012 11:30')
INSERT INTO Bufor VALUES('zabka.pl',			'01/04/2012 10:30')
INSERT INTO Bufor VALUES('KoronaPoradnik.pl',	'01/04/2012 10:30')
INSERT INTO Bufor VALUES('YouTube.com',			'01/04/1999 11:30')
--INSERT INTO Bufor VALUES('Biedronka.pl',		'01/04/2012 10:30') -- Wyrzuci YouTube.com do historii

SELECT * FROM Bufor
SELECt * FROM Historia
go