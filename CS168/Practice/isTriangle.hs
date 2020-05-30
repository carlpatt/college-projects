isTriangle :: Int -> Int -> Int -> Bool
isTriangle a b c = 
  case (a+b) > c of
    False -> False
    True -> case (a+c) > b of
              False -> False
              True -> case (b+c) > a of
                        False -> False
                        True -> True
