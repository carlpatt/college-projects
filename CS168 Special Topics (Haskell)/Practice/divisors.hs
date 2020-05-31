-- Find # of divisors of a given number
divisors :: Integral a => a -> Int
divisors x = length [l | l <- [1..x], x `mod` l ==0]
