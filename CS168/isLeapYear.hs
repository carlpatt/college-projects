module LeapYear
(isLeapYear) where


isLeapYear :: Int -> Bool
isLeapYear y  
  | mod y 4 == 0 && mod y 400 == 0 = True
  | mod y 4 == 0 && mod y 100 == 0 = False
  | mod y 4 == 0 = True
  | not (mod y 4 == 0) = False
  

