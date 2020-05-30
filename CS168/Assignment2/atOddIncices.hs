atOddIndices [] = []
atOddIndices [x] = []
atOddIndices (x:b:xs) = b : atOddIndices xs

