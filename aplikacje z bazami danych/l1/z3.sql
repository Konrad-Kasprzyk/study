USE AdventureWorks2017;

WITH SalesPersonHelp(TerritoryID, SalesPersonNumber) AS
(
	SELECT TerritoryID, COUNT(BusinessEntityID) FROM [Sales].[SalesPerson]
	GROUP BY TerritoryID
),
CityCustomers(City, CustomersNumber) AS
(
	SELECT City, COUNT(BusinessEntityID) FROM Person.BusinessEntityAddress bus
	INNER JOIN Person.Address addr ON  bus.AddressID=addr.AddressID
	GROUP BY City
)
SELECT distinct c.City, CustomersNumber, SalesPersonNumber FROM CityCustomers c INNER JOIN Person.Address addr ON c.City=addr.City
INNER JOIN [Person].[StateProvince] prov ON addr.StateProvinceID=prov.StateProvinceID
INNER JOIN SalesPersonHelp s ON prov.TerritoryID=s.TerritoryID
ORDER BY c.City