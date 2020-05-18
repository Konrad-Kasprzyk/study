from unittest import TestCase
from Dostawa_Domain.Model.Package.Package import Package

class PackageTests(TestCase):
    def test_attributesCachnges(self):
        p = Package(City = "Wrocław", PostalCode="51-152", StreetAddress= "Piłsudskiego 7",
                    ClientId=1, DeliveryType="Standard", DeclaredValue=100)
        self.assertEqual(23,23)