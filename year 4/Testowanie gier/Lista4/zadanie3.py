import pytest
from store import Cart, Store, ProductAlreadyExists, ProductNotFound
import json, sys

#Cart
@pytest.fixture(scope='module')
def cart():
    with open("test_offer.json", encoding='utf-8') as r:
        return Cart(Store(json.load(r)))

@pytest.mark.sampleMark
def test_cart_add(cart):
    cart.add('jersey dress')
    assert len(cart.products) == 1
    cart.add("denim shorts")
    assert len(cart.products) == 2
    assert "denim shorts" in cart.products
    assert "jersey dress" in cart.products
    with pytest.raises(ProductNotFound):
        cart.add("bad product")

@pytest.mark.sampleMark
def test_cart_delete(cart):
    assert 2 == len(cart.products)
    cart.delete("jersey dress")
    assert 1 == len(cart.products)
    assert "denim shorts" in cart.products

@pytest.mark.skipif(sys.version_info.major != 3,
                    reason="requires Python3")
def test_cart_quanity(cart):
    cart.add('jersey dress')
    cart.set_quantity('jersey dress', 3)
    assert 3 == cart.products['jersey dress']
    with pytest.raises(ProductNotFound):
        cart.set_quantity("bad product", 10)

@pytest.mark.skipif(sys.version_info.major != 2,
                    reason="requires Python2")
def test_cart_total(cart):
    cart.delete('denim shorts')
    cart.set_quantity('jersey dress', 3)
    assert 39.99 * 3 == cart.get_total()
    cart.add("sneakers")
    cart.add("t-shirt")
    assert 39.99 * 3 + 29.99 + 4.99 == cart.get_total()
    
@pytest.mark.skip
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