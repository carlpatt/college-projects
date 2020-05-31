-- catMaybe :: Eq a => [Maybe a] -> [a]
-- catMaybe [] = []
-- catMaybe (x:xs)
--   | x == Nothing = catMaybe xs
--   | otherwise = removeMaybe(x) : catMaybe xs
  
removeMaybe x = 
  case x of
       Just x -> x
       
catMaybe [] = []
catMaybe (Nothing : xs) = catMaybe xs
catMaybe (Just x:xs) = x : catMaybe xs
