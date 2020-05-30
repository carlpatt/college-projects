atEvenIndices [] = []
atEvenIndices [x] = [x]
atEvenIndices (x:_:xs) = x : atEvenIndices xs

