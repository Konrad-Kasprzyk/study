USE AdventureWorks2017

select m.Name, COUNT(ProductID) 
from [Production].[ProductModel] m JOIN [Production].[Product] p ON p.ProductModelID = m.ProductModelID
GROUP BY m.Name HAVING COUNT(ProductID)>1