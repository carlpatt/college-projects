module A10 where
import Control.Applicative
import Data.Char

data Parser a =
  Parser { runParser :: String -> [(a, String)] }

mapFst :: (a -> b) -> [(a,s)] -> [(b,s)]
mapFst f = map $ \(a, s) -> (f a, s)

instance Functor Parser where
  -- fmap :: (a -> b) -> Parser a -> Parser b
  fmap f p = Parser g
    where g s = mapFst f (runParser p s)

instance Applicative Parser where
  -- pure: a -> Parser a
  pure a = Parser (\s -> [(a,s)])
  -- <*> :: Parser (a -> b) -> Parser a -> Parser b
  pf <*> pa = Parser g
    where g s1 = concatMap h (runParser pf s1)
            where h (f, s2) = mapFst f (runParser pa s2)

instance Monad Parser where
  -- (>>=) :: Parser a -> (a -> Parser b) -> Parser b
  pa >>= fpb = Parser g
    where g s1 = concatMap h (runParser pa s1)
            where h (a,s2) = runParser (fpb a) s2

instance Alternative Parser where
  -- empty :: Parser a
  empty = Parser (\_ -> [])
  -- (<|>) :: Parser a -> Parser a -> Parser a
  p1 <|> p2 = Parser g
    where
      g s1 =
        case runParser p1 s1 of
           [] -> runParser p2 s1   -- p1 failed, so try p2
           results -> results      -- otherwise p1's results are fine

satisfies :: (Char -> Bool) -> Parser Char
satisfies ok = Parser f
  where f [] = []             -- input was empty
        f (c:cs)
          | ok c = [(c,cs)]   -- first char satisfies function
          | otherwise = []    -- first char doesn't satisfy function

char :: Char -> Parser Char
char c = satisfies (== c)

string :: String -> Parser String
string s = loop s >> return s
  where loop "" = return ""
        loop (c:cs) = char c >> loop cs

data Arith
  = Num Double
  | Var String
  | UnaryOp UnaryOp Arith
  | BinaryOp BinaryOp Arith Arith
  deriving (Eq, Show)

data UnaryOp
  = Sqrt    -- square root
  | Neg     -- negate
  | Abs     -- absolute value
  deriving (Eq, Show)

data BinaryOp
  = Add     -- add, +
  | Sub     -- subtract, -
  | Mul     -- multiply, *
  | Div     -- divide, /
  | Pow     -- power (exponent), **
  deriving (Eq, Show)

parseUnaryOp :: Parser UnaryOp
parseUnaryOp =
   (string "sqrt" >> return Sqrt) <|>
   (string "-" >> return Neg) <|>
   (string "abs" >> return Abs)

parseBinaryOp :: Parser BinaryOp
parseBinaryOp =
   (string "+" >> return Add) <|>
   (string "-" >> return Sub) <|>
   (string "**" >> return Pow) <|>
   (string "*" >> return Mul) <|>
   (string "/" >> return Div)

-- TODO: revise this so it supports alphanumeric identifiers
-- (first char must be alphabetic only).
parseVar :: Parser Arith
parseVar =
  Var <$> head (satisfies some) <*> isAlpha (satisfies isAlphaNum)
--  Var <$> some (satisfies (isAlpha . head))

-- TODO: revise this so it supports decimal point and subsequent
-- digits.
parseNum :: Parser Arith
parseNum =
  f <$> optional (char '-') <*> some (satisfies isDigit)
  where
    f Nothing digits = Num (read digits)
    f (Just _) digits = Num (read ('-':digits))
