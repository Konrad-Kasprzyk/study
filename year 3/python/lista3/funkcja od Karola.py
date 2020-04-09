import random

def foo(text, max_length, n):
    text = list(filter(lambda worda: len(worda) <= max_length, text.split(' ')))
    to_del = random.sample(text, len(text) - n)
 #   x = ' '.join([word for i, word in enumerate(text) if word not in to_del])
    x = ' '.join([word for word in text if word not in to_del])

    return x


print(foo("Ola ma kota i psasdasdasd", 4, 3))

x = [cos for cos in enumerate([1,2,3,4]) if cos not in [2,3]]
print(x)

y = [cos+3 for cos in [1,2,3] if cos not in [2,3]]
print(y)
