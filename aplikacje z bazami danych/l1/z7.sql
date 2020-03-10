USE AdventureWorks2017;

ALTER TABLE [Sales].[Customer]
DROP CONSTRAINT [CK_CreditCardNumber];
ALTER TABLE [Sales].[Customer]
DROP COLUMN CreditCardNumber;

--ALTER TABLE [Sales].[Customer] ADD CreditCardNumber VARCHAR(20) NOT NULL DEFAULT '0000-0000-0000-0000'

ALTER TABLE [Sales].[Customer]  
    ADD CreditCardNumber VARCHAR(20)
    CONSTRAINT CK_CreditCardNumber DEFAULT '0000-0000-0000-0000' NOT NULL

--ALTER TABLE [Sales].[Customer]  
--    ADD CreditCardNumber VARCHAR(20) NOT NULL DEFAULT '0000-0000-0000-0000' 
--    CONSTRAINT CK_CreditCardNumber CHECK(CreditCardNumber is not NULL)

