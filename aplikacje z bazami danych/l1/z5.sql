USE AdventureWorks2017;

-- Nie da sie polaczyc CustomerID z imieniem i nazwiskiem z Person.Person, a moja tabela Customer nie posiada imion i nazwisk klientow.
--SELECT * FROM [Person].[BusinessEntityContact] b JOIN [Sales].[Customer] c ON b.PersonID = c.PersonID
--JOIN [Person].[Person] p ON p.rowguid=b.rowguid
--JOIN [Person].[Person] p ON p.rowguid=c.rowguid
--JOIN [Person].[Person] p ON p.BusinessEntityID=b.BusinessEntityID

WITH CustomerDiscount(CustomerID, NumberOfProducts, UnitDiscount) AS
(
	SELECT sh.CustomerID, OrderQty, UnitPriceDiscount FROM [Sales].[Customer] c JOIN [Sales].[SalesOrderHeader] sh ON c.CustomerID = sh.CustomerID
	JOIN [Sales].[SalesOrderDetail] sd on sh.SalesOrderID = sd.SalesOrderID 
)
SELECT CustomerID, SUM(NumberOfProducts * UnitDiscount)  FROM CustomerDiscount WHERE UnitDiscount > 0 GROUP BY CustomerID
