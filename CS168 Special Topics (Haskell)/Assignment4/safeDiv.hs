safeDiv :: Float -> Float -> Maybe Float
safeDiv x y
  | x == 0 || y == 0 = Nothing
  | otherwise = Just $ x/y

formula :: Float -> Float -> Maybe Float
-- formula a b = (+) <$> (safeDiv (b**2) a) <*> (safeDiv (a**2) (b+a))
formula a b = fmap (+) (safeDiv (b**2) a) <*> (safeDiv (a**2) (b+a))
