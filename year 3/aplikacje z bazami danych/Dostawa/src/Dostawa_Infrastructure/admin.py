from django.contrib import admin
from .models.DeliveryType.DeliveryTypeModel import DeliveryTypeModel
from .models.Package.PickupModel import PickupModel
from .models.Package.ReturnModel import ReturnModel
from .models.Package.PackageModel import PackageModel

# Register your models here.
admin.site.register(DeliveryTypeModel)
admin.site.register(PickupModel)
admin.site.register(PackageModel)
admin.site.register(ReturnModel)

