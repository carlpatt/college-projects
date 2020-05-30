isPrime :: Integer -> Bool
isPrime x = x > 1 && not (any (x `l`) [3,5..sr])
  where 
    l = \a b -> mod a b == 0
    sr = floor $ sqrt $ fromIntegral x
    -- sr = (floor . sqrt . fromIntegral) x
    
main = do
    let result = isPrime 23423527
    print result

