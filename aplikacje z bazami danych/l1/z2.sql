USE AdventureWorks2017

select m.ProductModelID, COUNT(ProductID) 
from [Production].[ProductModel] m JOIN [Production].[Product] p ON p.ProductModelID = m.ProductModelID
GROUP BY m.ProductModelID HAVING COUNT(m.ProductModelID)>1