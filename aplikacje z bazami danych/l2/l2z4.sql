USE Test

DROP PROCEDURE IF EXISTS test4
GO


CREATE PROCEDURE test4 @tytulArg nvarchar(100) = NULL, @autorArg nvarchar(100) = NULL, @rokArg int = NULL AS
BEGIN
	DECLARE @SQLString nvarchar(500); 
	SET @SQLString =  
     N'SELECT * FROM Ksiazka  
     WHERE 
		Ksiazka.Tytul = @tytul AND
		Ksiazka.Autor = @autor AND
		Ksiazka.Rok_Wydania = @rok';
		
	DECLARE @ParmDefinition nvarchar(500);
	SET @ParmDefinition = N'@tytul nvarchar(100), @autor nvarchar(100), @rok nvarchar(100)';  
	EXECUTE sp_executesql @SQLString, @ParmDefinition, 
                      @tytul = @tytulArg, @autor = @autorArg, @rok = @rokArg;  
END
GO

EXEC test4 N'Microsoft Access. Podr?cznik administratora', N'Helen Feddema', 2006
GO