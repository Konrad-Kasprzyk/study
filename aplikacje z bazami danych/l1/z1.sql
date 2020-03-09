USE AdventureWorks2017

select distinct City from Sales.SalesOrderHeader s, Person.Address a where s.ShipToAddressID = a.AddressID and s.DueDate < GETDATE() order by City