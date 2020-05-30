data Seed = Seed { unSeed :: Int }
  deriving (Eq, Show)

type Gen s a = s -> (a, s)

rand :: Gen Seed Int
rand (Seed s) = (s', Seed s')
  where
    s' = (s * 16807) `mod` 0x7FFFFFFF

---------------[ Coin flips ]---------------

data CoinFlip = Heads | Tails
  deriving (Eq, Show, Bounded, Enum)

coinFromInt :: Int -> CoinFlip
coinFromInt i 
  | odd i = Tails
  | otherwise = Heads

flipCoin :: Gen Seed CoinFlip
flipCoin s0 = 
  case rand s0 of
    (x, Seed s1) -> (coinFromInt x, Seed s1)


---------------[ Iterating ]---------------

iterGen :: Gen s a -> Int -> Gen s [a]
iterGen gen 0 s0 = ([], s0)
iterGen gen n s0 = (m : ms, s2)
  where
    (m, s1) = gen s0
    (ms, s2) = iterGen gen (n-1) s1
    

---------------[ Rainbows ]---------------

data Color = Red | Orange | Yellow | Green | Blue
  deriving (Eq, Show, Enum, Bounded)

colorFromInt :: Int -> Color
colorFromInt i = toEnum (mod i 5) :: Color

genColor :: Gen Seed Color
genColor s0 = 
  case rand s0 of
    (x, Seed s) -> (colorFromInt x, Seed s)

---------------[ Functor ]---------------

fmapGen :: (a -> b) -> Gen s a -> Gen s b
fmapGen f gen s0 = (f m, s1)
  where
    (m, s1) = gen s0

---------------[ Miscellaneous ]---------------

-- Nothing more to do, but leave these definitions
-- here for testing.

randMod :: Int -> Gen Seed Int
randMod k = fmapGen (`mod` k) rand

diceRoll :: Gen Seed Int
diceRoll = fmapGen succ (randMod 6)

alphabetic :: Gen Seed Char
alphabetic = fmapGen (['a'..'z'] !!) (randMod 26)

always :: a -> Gen s a
always a s = (a,s)

makeGen :: (s -> s) -> Gen s s
makeGen f s = (s, f s)

successive :: Enum s => Gen s s
successive = makeGen succ

