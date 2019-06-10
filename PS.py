import sys

while True:
    input_ = sys.stdin.readline()
    if input_ == '':
        break
    print(sum(map(int, input_.split())))
