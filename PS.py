import hashlib
m=hashlib.sha384()
m.update(input().encode())
print(m.hexdigest())
