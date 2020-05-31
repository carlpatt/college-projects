slice i k xs
  | k <= 1 = []
  | otherwise = drop i (take k xs)
  
dropFirstLast xs = slice 1 (length xs-1) xs
