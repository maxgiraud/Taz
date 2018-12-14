
import math

def autoframe(length):
    x = math.ceil(math.sqrt(length))
    while (length%x) != 0 and x > 1:
        x-=1
    y = length//x
    return (int(x),int(y))

