# Zmień dane przesyłane w json. Przesyłasz obiekty a nie stringi. Np weź z daty napis a nie datetime przesyłasz

from unittest import TestCase
from unittest.mock import MagicMock
from Dostawa_Application.ShopService import ShopService
from Dostawa_Infrastructure.Repositories.PackageRepository import PackageRepository

class ShopServiceTests(TestCase):

    def test_cos(self):
        p = PackageRepository()
        p.FindAll = MagicMock()
        cos = p.FindAll()
        p.FindAll.assert_called_once()

    def test_cos2(self):
        p = PackageRepository()
        p = MagicMock()
        cos = p.FindAll()
        p.FindAll.assert_called_once()

