fact2 :: Integer -> Maybe Integer
fact2 n
  | n < 0 = Nothing
  | n == 0 = Just 1
  | otherwise = fmap (n *) (fact2 (n-1))
