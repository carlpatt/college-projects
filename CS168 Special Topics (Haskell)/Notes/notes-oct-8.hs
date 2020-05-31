data BoundedStack a = BoundedStack { capacity :: Int, elements :: [a] }
  deriving Show
  
new :: Int -> BoundedStack a
new c = BoundedStack c []


push :: a -> BoundedStack a -> Maybe (BoundedStack a)
push x (BoundedStack cap elts)
  | length elts == cap = Nothing
  | otherwise = Just (BoundedStack cap (x : elts))
  
pop :: BoundedStack a -> Maybe ( BoundedStack a)
pop (BoundedStack cap []) = Nothing
pop ( BoundedStack cap (_:xs)) = Just (BoundedStack cap xs)

top :: BoundedStack a -> Maybe a
top (BoundedStack _ []) = Nothing
top (BoundedStack _ (x:_)) = Just x

instance Functor BoundedStack where
  fmap f (BoundedStack cap elts) = BoundedStack cap (fmap f elts)

