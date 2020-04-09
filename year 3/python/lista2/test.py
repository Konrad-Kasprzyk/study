try:
    raise Exception("dzielenie przez zero")
    print("ok")

except Exception as x:
    print(x.args[0])