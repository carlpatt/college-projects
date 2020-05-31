type Year = Int

type Day = Int

data Date = Date Year Month Day
  deriving (Eq, Show, Ord)

data DayOfWeek = Mon | Tue | Wed | Thu | Fri | Sat | Sun
  deriving (Show, Eq, Ord, Enum, Bounded)

data Month = Jan | Feb | Mar | Apr | May | Jun | Jul | Aug | Sep | Oct | Nov | Dec
  deriving (Show, Eq, Ord, Enum, Bounded)

isLeapYear :: Year -> Bool
isLeapYear y
  | mod y 4 == 0 && mod y 400 == 0 = True
  | mod y 4 == 0 && mod y 100 == 0 = False
  | mod y 4 == 0 = True
  | not (mod y 4 == 0) = False

daysPerMonth :: Year -> Month -> Int
daysPerMonth y m
  | elem m l1 = 31
  | elem m l2 = 30
  | isLeapYear y && m == Feb = 29
  | otherwise = 28
  where l1 = [Jan, Mar, May, Jul, Aug, Oct, Dec]
        l2 = [Sep, Apr, Jun, Nov]

smartDate :: Year -> Month -> Day -> Maybe Date
smartDate y m d
  | d /= daysPerMonth y m = Nothing
  | otherwise = Just (Date y m d)

tomorrow :: Date -> Date
tomorrow (Date y m d) 
  | newYear = (Date (succ y) Jan 1)
  | nextDay = (Date y m (succ d))
  | nextMonth = (Date y (succ m) 1)
  where newYear = m == Dec && d == 31
        nextDay = d < daysPerMonth y m
        nextMonth = d == daysPerMonth y m

