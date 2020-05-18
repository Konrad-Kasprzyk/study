from interface import implements
from . import ShopInterface
from Dostawa_Infrastructure.Repositories.PackageRepository import PackageRepository
from Dostawa_Domain.Model.Package.Package import Package


class ShopInterface(implements(ShopInterface)):

    def __init__(self):
        self.packageRepository = PackageRepository()

    def GetPackageInfo(self, package_code):
        package = self.packageRepository.Find(package_code)
        if not package:
            return None
        products = package.GetPackageProducts()
        packageInfo = {"City": package.City,
                       "PostalCode": package.PostalCode,
                       "StreetAddress": package.StreetAddress,
                       "DeclaredValue": package.DeclaredValue,
                       "ClientId": package.ClientId,
                       "AcceptDate": package.AcceptDate,
                       "DeliveryDate": package.DeliveryDate,
                       "DeliveryType": package.DeliveryType,
                       "Status": package.GetStatus().Name,
                       "PackedProducts": products}
        return packageInfo

    def NewDelivery(self, city, postalCode, streetAddress, client_id, delivery_method, value, items):
        try:
            package = Package(City=city, PostalCode= postalCode, StreetAddress=streetAddress,
                              ClientId=client_id, DeliveryType=delivery_method, DeclaredValue=value)
        except ValueError as err:
            print("NewDelivery error:", err)
            return
        try:
            for item in items:
                package.AddDeliveryProduct(product_name=item.name, quantity=item.quantity)
        except TypeError as err:
            print("NewDelivery error, no items to deliver:", err)
            return
        except AttributeError as err:
            print("NewDelivery error, bad items to deliver format:", err)
            return
        except ValueError as err:
            print("NewDelivery error:", err)
            return
        self.packageRepository.Insert(package)

    def GetPackageStatus(self, package_code):
        package = self.packageRepository.Find(package_code)
        if not package:
            return None
        return package.GetStatus().Name
