doubleMe x = x * 2

doubleUs x y = doubleMe x + doubleMe y

doubleSmallerNum x = if x > 100 then x else x*2

factorial :: (Integral a) => a -> a
factorial 0 = 1
factorial n = n * factorial(n-1)



