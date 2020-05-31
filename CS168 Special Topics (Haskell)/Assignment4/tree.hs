data Tree a
  = Leaf a
  | Branch (Tree a) (Tree a)
  deriving (Show, Eq)

height :: Tree a -> Int
height (Leaf _) = 0
height (Branch l r) = 1 + max (height l) (height r)

treeToList :: Tree a -> [a]
treeToList (Leaf x) = [x]
treeToList (Branch l r) = treeToList l ++ treeToList r

treeMap :: (a -> b) -> Tree a -> Tree b
treeMap f (Leaf x) = Leaf (f x)
treeMap f (Branch l r) = Branch (treeMap f l) (treeMap f r)

data Direction = GoLeft | GoRight
  deriving Show

type Path = [Direction]

followPath :: Tree a -> Path -> Maybe a
followPath (Leaf x) [] = Just x
followPath (Branch l r) (GoLeft xs) = followPath l xs
followPath (Branch l r) (GoRight xs) = followPath r xs
followPath _ _ = Nothing
