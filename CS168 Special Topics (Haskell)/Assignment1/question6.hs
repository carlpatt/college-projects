
a /? b = a `mod` b == 0

isPrime 1 = False
isPrime n
  | n < 1 = error "Number Too Small"
  | otherwise = not(elem True (map (n/?) [2..n-1]))


isFirstOfTwinPrime n = isPrime n && isPrime (n + 2)
