from Dostawa_Infrastructure.Repositories import PackageRepository


DELIVERY_SUCCESS_STATUS = "Dostarczone"
DELIVERY_FAILURE_STATUS = "Problem z Dostawa"
DELIVERY_STARTING_STATUS = "Przyjete"

class Status:

    def __init__(self, DeliveryStep = -1, Name = None):
        if DeliveryStep < 0 or not Name:
            self._DeliveryStep = 0
            self._Name = DELIVERY_STARTING_STATUS
        else:
            self._DeliveryStep = DeliveryStep
            self._Name = Name

    @property
    def DeliveryStep(self):
        return self._DeliveryStep

    @property
    def Name(self):
        return self._Name

    @Name.setter
    def Name(self, value):
        repo = PackageRepository()
        for repo_status in repo.FindAllPackageStatuses():
            if repo_status.Name == value:
                self._Name = value
                self.DeliveryStep = repo_status.DeliveryStep
                return
        raise ValueError("Status name not found in available statuses")