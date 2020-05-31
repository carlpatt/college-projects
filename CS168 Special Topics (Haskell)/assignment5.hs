import Data.Maybe (isJust)


data ITree a
  = ILeaf
  | IBranch a (ITree a) (ITree a)
  deriving (Show, Eq)

instance Functor ITree where
  fmap f (ILeaf) = ILeaf
  fmap f (IBranch x l r) = IBranch (f x) (fmap f l) (fmap f r)


flipTree :: ITree a -> ITree a
flipTree (ILeaf) = ILeaf
flipTree (IBranch x l r) = IBranch x (flipTree r) (flipTree l)


preOrderList :: ITree a -> [a]
preOrderList (ILeaf) = []
preOrderList (IBranch x l r) = x : preOrderList l ++ preOrderList r


balancedHeight :: ITree a -> Maybe Int
balancedHeight (ILeaf) = Just 0
balancedHeight (IBranch x l r) =
  case balancedHeight l of
       Nothing -> Nothing
       Just hl -> case balancedHeight r of
                       Nothing -> Nothing
                       Just hr
                           | abs (hl - hr) > 1 -> Nothing
                           | otherwise -> Just $ 1 + (max hl hr)
       
       

isBalanced :: ITree a -> Bool
isBalanced = isJust . balancedHeight


balancedFromList :: [a] -> ITree a
balancedFromList [] = ILeaf
balancedFromList (x:xs) = IBranch x (balancedFromList ys) (balancedFromList zs)
  where
    n = length xs `div` 2
    ys = take n xs
    zs = drop n xs


-- Trees for testing

iterm :: a -> ITree a
iterm x = IBranch x ILeaf ILeaf

t1 :: ITree Int
t1 = IBranch 3 (IBranch 4 ILeaf (IBranch 5 (iterm 7) ILeaf)) (iterm 9)

t2 :: ITree Ordering
t2 = IBranch EQ (IBranch LT (iterm GT) (IBranch LT (iterm EQ) ILeaf)) (iterm GT)

t9 = IBranch 1 (IBranch 2 (iterm 3) (iterm 4)) (IBranch 5 (iterm 6) (iterm 7))
