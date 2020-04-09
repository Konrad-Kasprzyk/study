# Generated by Django 2.0.7 on 2019-12-11 14:55

import datetime
from django.db import migrations, models
from django.utils.timezone import utc


class Migration(migrations.Migration):

    dependencies = [
        ('kalendarz', '0005_auto_20191211_1453'),
    ]

    operations = [
        migrations.AlterField(
            model_name='wydarzenie',
            name='data_wydarzenia',
            field=models.DateField(default=datetime.datetime(2019, 12, 11, 14, 55, 30, 6812, tzinfo=utc)),
        ),
        migrations.AlterField(
            model_name='wydarzenie',
            name='godz_rozpoczecia',
            field=models.TimeField(default=datetime.datetime(2019, 12, 11, 14, 55, 30, 6835, tzinfo=utc)),
        ),
        migrations.AlterField(
            model_name='wydarzenie',
            name='godz_zakonczenia',
            field=models.TimeField(default=datetime.datetime(2019, 12, 11, 14, 55, 30, 6851, tzinfo=utc)),
        ),
    ]
