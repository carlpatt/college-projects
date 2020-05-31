slice i k xs
  | k <= 1 = []
  | otherwise = drop i (take k xs)
  
