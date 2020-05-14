from interface import Interface


class IPackageRepository(Interface):

    def Insert(self, package):
        pass

    def Find(self, package_code):
        pass

    def FindFilter(self, filter_):
        pass

    def FindAll(self):
        pass

    def Update(self, package):
        pass
