fact n
   | n < 0 = error "Negative argument"
   | n == 0 = 1
   | otherwise = n * fact(n-1)

