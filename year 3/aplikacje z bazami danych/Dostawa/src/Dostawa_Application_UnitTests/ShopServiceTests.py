from unittest import TestCase
from unittest.mock import patch
from Dostawa_Application.ShopService import ShopService
from Dostawa_Infrastructure.Repositories.FakePackageRepository \
    import FakePackageRepository as PackageRepository
from Dostawa_ObjectMothers.PackageObjectMother import PackageObjectMother


class ShopServiceTests(TestCase):

    def test_GetPackageStatusReturnsProperStatus(self):
        package = PackageObjectMother.CreatePackageManyPickupNoReturn()
        status = package.GetStatus()
        with patch.object(PackageRepository, 'Find', return_value=package):
            shopService = ShopService()
            assert shopService.GetPackageStatus(package.PackageCode) == status.Name

    def test_NewDeliveryInvalidCityParameterRaiseException(self):
        shopService = ShopService()

        with self.assertRaises(ValueError):
            shopService.NewDelivery("", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery(42, "50-043", "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

    def test_NewDeliveryInvalidItemsParameterRaiseException(self):
        shopService = ShopService()

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": "2"})

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, {2: 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, "")

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, None)

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, "Pan Tadeusz")

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, 2)


    # Testy na pozostałe złe imputy i testy na poprawne nowe zamówienie
