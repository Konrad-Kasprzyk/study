import pytest

errMsg = "Argument must be int"

def isPrime(x):
    if not isinstance(x, int):
        raise ValueError("Argument must be int")
    if x<2:
        return False
    for i in range(2, x):
        if x % i == 0:
            return False
    return True

@pytest.mark.parametrize('test_input,expected', [(1, False), (2, True), (3, True), (4, False), (13, True), (42, False), (43, True)])
def test_good_output(test_input, expected): 
    assert isPrime(test_input) == expected
    
@pytest.mark.parametrize('test_input', [1.42, 12.1, "abc", 'a', [1, 2, 3]])
def test_exception_thrown(test_input): 
    with pytest.raises(ValueError, match=errMsg):
        isPrime(test_input)