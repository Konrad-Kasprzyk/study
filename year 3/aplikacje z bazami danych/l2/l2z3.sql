USE Test

DROP PROCEDURE IF EXISTS exercise3proc
GO

DROP TYPE IF EXISTS Czytelnicy
GO

CREATE TYPE Czytelnicy AS TABLE(czytelnik_id INT)
GO

CREATE PROCEDURE exercise3proc @czytelnicy Czytelnicy READONLY AS
BEGIN
	SELECT 
		input.czytelnik_id, SUM(wyp.Liczba_Dni)
	FROM	
		@czytelnicy AS input,
		[dbo].Czytelnik AS czyt,
		[dbo].Wypozyczenie AS wyp
	WHERE
		czyt.Czytelnik_ID = wyp.Czytelnik_ID AND
		czyt.Czytelnik_ID = input.czytelnik_id
	GROUP BY 
		input.czytelnik_id
END
GO

DECLARE @id_czyt Czytelnicy
INSERT INTO @id_czyt VALUES (1)
INSERT INTO @id_czyt VALUES (2)

EXEC exercise3proc @id_czyt
GO