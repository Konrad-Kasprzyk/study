import pytest
from store import Cart, Store, ProductAlreadyExists, ProductNotFound
import json

@pytest.fixture(scope='module')
def storeFix():
    with open("test_offer.json", encoding='utf-8') as r:
        return Store(json.load(r))

@pytest.mark.parametrize('name, desc, price', 
[('prod1','testing sample description 1', '1.22'),
 ('prod2','testing sample description 2', '2.33'),
 ('prod3','testing sample description 3', '9.99'),
 ('prod4','testing sample description 4', '42.42'),
 ('prod5','testing sample description 5', '1.00')])
def test_store_add(name, desc, price, storeFix):
    storeFix.add_to_offer(name, desc, price)
    assert (name in storeFix.offer)
    assert storeFix.offer[name]['description'] == desc
    assert storeFix.offer[name]['price'] == price

@pytest.mark.parametrize('name, desc, price', 
[('prod1','testing sample description 1', '42.42'),
 ('prod2','testing sample description 2', '11.08'),
 ('prod3','testing sample description 3', '9.99'),
 ('prod4','testing sample description 4', '1.02'),
 ('prod5','testing sample description 5', '0.01')])
def test_store_add_duplicate(name, desc, price, storeFix):
    with pytest.raises(ProductAlreadyExists):
        storeFix.add_to_offer(name, desc, price)


@pytest.mark.parametrize('name', [('prod1'), ('prod2'), ('prod3'), ('prod4'), ('prod5')])
def test_store_del(name, storeFix):
    storeFix.delete_from_offer(name)
    assert (name not in storeFix.offer)

@pytest.mark.parametrize('name', [('prod1'), ('prod2'), ('prod3'), ('prod4'), ('prod5')])
def test_store_del_notfound(name, storeFix):
    with pytest.raises(ProductNotFound):
        storeFix.delete_from_offer(name)

@pytest.mark.parametrize('name, desc, price', 
[('jersey dress','testing sample description 1', '81.33'),
 ('denim shorts','testing sample description 2', '23.56'),
 ('denim skirt','testing sample description 3', '9.99'),
 ('sneakers','testing sample description 4', '1.00'),
 ('t-shirt','testing sample description 5', '0.45')])
def test_store_update(name, desc, price, storeFix):
    storeFix.update(name, desc, price)
    assert storeFix.offer[name]['description'] == f'{desc}'
    assert storeFix.offer[name]['price'] == f'{price}'

@pytest.mark.parametrize('name, desc, price', 
[('prod1','testing sample description 1', '42.42'),
 ('prod2','testing sample description 2', '11.08'),
 ('prod3','testing sample description 3', '9.99'),
 ('prod4','testing sample description 4', '1.02'),
 ('prod5','testing sample description 5', '0.01')])
def test_store_update_notfound(name, desc, price, storeFix):
    with pytest.raises(ProductNotFound):
        storeFix.update(name, desc, price)


#Cart
@pytest.fixture(scope='module')
def cart():
    with open("test_offer.json", encoding='utf-8') as r:
        return Cart(Store(json.load(r)))


def test_cart_add(cart):
    cart.add('jersey dress')
    assert len(cart.products) == 1
    cart.add("denim shorts")
    assert len(cart.products) == 2
    assert "denim shorts" in cart.products
    assert "jersey dress" in cart.products
    with pytest.raises(ProductNotFound):
        cart.add("bad product")

def test_cart_delete(cart):
    assert 2 == len(cart.products)
    cart.delete("jersey dress")
    assert 1 == len(cart.products)
    assert "denim shorts" in cart.products

def test_cart_quanity(cart):
    cart.add('jersey dress')
    cart.set_quantity('jersey dress', 3)
    assert 3 == cart.products['jersey dress']
    with pytest.raises(ProductNotFound):
        cart.set_quantity("bad product", 10)

def test_cart_total(cart):
    cart.delete('denim shorts')
    cart.set_quantity('jersey dress', 3)
    assert 39.99 * 3 == cart.get_total()
    cart.add("sneakers")
    cart.add("t-shirt")
    assert 39.99 * 3 + 29.99 + 4.99 == cart.get_total()
    
def test_cart_show(cart, capsys):
    cart.delete('jersey dress')
    cart.delete('sneakers')
    cart.delete('t-shirt')
    cart.show()
    captured = capsys.readouterr()
    assert 'Your shopping cart is empty.' in captured.out
    cart.add('jersey dress')
    cart.set_quantity('jersey dress', 3)
    cart.show()
    captured = capsys.readouterr()
    assert "jersey dress      39.99           3"  in captured.out
    assert "TOTAL: 119.97" in captured.out