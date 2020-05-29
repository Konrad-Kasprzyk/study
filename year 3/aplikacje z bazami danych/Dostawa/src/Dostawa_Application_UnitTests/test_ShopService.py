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

    def test_NewDeliveryInvalidAddressParametersRaiseException(self):
        shopService = ShopService()

        with self.assertRaises(ValueError):
            shopService.NewDelivery("", "50-043", "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery(42, "50-043", "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "", "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", 50, "Ruska 38", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", "", 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery("Wrocław", "50-043", 38, 2, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

    def test_NewDeliveryInvalidClientIdRaiseException(self):
        shopService = ShopService()

        with self.assertRaises(ValueError):
            shopService.NewDelivery("", "50-043", "Ruska 38", -4, "Ekonomiczny", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery(42, "50-043", "Ruska 38", "2", "Ekonomiczny", 100, {"Pan Tadeusz": 2})

    def test_NewDeliveryInvalidDeliveryTypeRaiseException(self):
        shopService = ShopService()

        with self.assertRaises(ValueError):
            shopService.NewDelivery("", "50-043", "Ruska 38", 2, "", 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery(42, "50-043", "Ruska 38", 2, 13, 100, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery(42, "50-043", "Ruska 38", 2, "non existing delivery type name", 100, {"Pan Tadeusz": 2})

    def test_NewDeliveryInvalidDeclaredValueRaiseException(self):
        shopService = ShopService()

        with self.assertRaises(ValueError):
            shopService.NewDelivery("", "50-043", "Ruska 38", 2, "", -13, {"Pan Tadeusz": 2})

        with self.assertRaises(ValueError):
            shopService.NewDelivery(42, "50-043", "Ruska 38", 2, 13, "100", {"Pan Tadeusz": 2})


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


    def test_NewDeliveryCreateSampleDeliveries(self):
        shopService = ShopService()
        deliveryMethods = shopService.GetAllDeliveryMethods()

        with patch.object(PackageRepository, 'Insert'):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, deliveryMethods[0].Name, 200, {"Pan Tadeusz": 2})
            PackageRepository.Insert.assert_called_once()

        with patch.object(PackageRepository, 'Insert'):
            shopService.NewDelivery("Wrocław", "51-152", "Piłsudskiego 7", 2, deliveryMethods[1].Name, 0,
                                    {"Pan Tadeusz": 1, "Chłopcy z placu broni": 5})
            PackageRepository.Insert.assert_called_once()

        with patch.object(PackageRepository, 'Insert'):
            shopService.NewDelivery("Wrocław", "50-043", "Ruska 38", 2, deliveryMethods[-1].Name, 100, {"Pan Tadeusz": 1})
            PackageRepository.Insert.assert_called_once()
