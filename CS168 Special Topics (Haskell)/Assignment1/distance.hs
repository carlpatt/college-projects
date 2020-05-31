square x = x*x

manhattan (x, y) (a, b) = abs(x - a) + abs(y - b)

euclidean (x, y) (a, b) = sqrt(square (x - a) + square (y - b))

chebyshev (x, y) (a, b) = abs(a - x) `max` abs(b - y)


