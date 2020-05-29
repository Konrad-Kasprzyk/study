from Dostawa_Infrastructure.Repositories.FakePackageRepository \
    import FakePackageRepository as PackageRepository
from Dostawa_Infrastructure.Repositories.FakeDeliveryTypeRepository \
    import FakeDeliveryTypeRepository as DeliveryTypeRepository
from Dostawa_Domain.Model.Package.Package import Package


class ShopService():

    def __init__(self):
        self.packageRepository = PackageRepository()
        self.deliveryTypeRepository = DeliveryTypeRepository()

    """
        Raises ValueError When: argument is missing,
                                delivery_method not found in available delivery methods,
                                items are not in format ['name':str: quantity:int],
                                items are duplicated
    """
    def NewDelivery(self, city: str, postalCode: str, streetAddress: str, client_id: int,
                    delivery_method: str, value: int, items: {str: int}):
        if not city or not isinstance(city, str) \
                or not postalCode or not isinstance(postalCode, str)\
                or not streetAddress or not isinstance(streetAddress, str) \
                or not isinstance(client_id, int) or client_id<0\
                or not delivery_method or not isinstance(delivery_method, str) \
                or not isinstance(value, int) or value<0\
                or not items or not isinstance(items, dict):
            raise ValueError("Invalid parameters type")
        package = Package(City=city, PostalCode= postalCode, StreetAddress=streetAddress,
                            ClientId=client_id, DeliveryType=delivery_method, DeclaredValue=value)
        for item, quantity in items.items():
            package.AddDeliveryProduct(product_name=item, quantity=quantity)
        self.packageRepository.Insert(package)

    def GetPackageStatus(self, package_code):
        package = self.packageRepository.Find(package_code)
        if not package:
            return None
        return package.GetStatus().Name

    def GetAllDeliveryMethods(self):
        return self.deliveryTypeRepository.FindAll()
