square x = x * x

powerSlow x n
  | n < 0 = error "Negative exponent"
  | n == 0 = 1
  | otherwise = x * powerSlow x (n-1)

powerFast x n
  | n < 0 = error "Negative Exponent"
  | n == 0 = 1
  | even n = square (powerFast x (n `div` 2))
  | otherwise = x * powerFast x (n-1)
  
