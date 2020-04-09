USE Test

drop function if exists l2z1
go
create function l2z1(@days int) returns table
return
	(SELECT czyt.PESEL, COUNT(wyp.Wypozyczenie_ID) AS LiczbaEgzemplarzy
	FROM	
		[dbo].Czytelnik AS czyt,
		[dbo].Wypozyczenie AS wyp
	WHERE
		czyt.Czytelnik_ID = wyp.Czytelnik_ID AND
		wyp.Liczba_Dni > @days
	GROUP BY czyt.PESEL)

go
select * from l2z1(2)
