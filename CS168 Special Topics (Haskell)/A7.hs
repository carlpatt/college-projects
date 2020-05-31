---------------------------------
------ Numeric operators   ------

data UnaryOp
  = Sqrt    -- square root
  | Neg     -- negate
  | Abs     -- absolute value
  deriving (Eq, Show)

runUnaryOp :: UnaryOp -> Double -> Double
runUnaryOp Abs = abs
runUnaryOp Neg = (0-)

----Added Sqrt-------
runUnaryOp Sqrt = sqrt


data BinaryOp
  = Add     -- add
  | Sub     -- subtract
  | Mul     -- multiply
  | Div     -- divide
  | Pow     -- power (exponent)
  deriving (Eq, Show)

runBinaryOp :: BinaryOp -> Double -> Double -> Double
runBinaryOp Add = (+)
runBinaryOp Pow = (**)

------My solution-----
runBinaryOp Sub = (-)
runBinaryOp Mul = (*)
runBinaryOp Div = (/)


------------------------------
------ Expression trees ------


data Arith
  = Num Double
  | Var String
  | UnaryOp UnaryOp Arith
  | BinaryOp BinaryOp Arith Arith
  deriving (Eq, Show)

type Environment = [(String, Double)]

evaluate :: Environment -> Arith -> Either String Double

evaluate env (UnaryOp op t) =
  runUnaryOp op <$> evaluate env t

evaluate env (BinaryOp op t1 t2) =
  runBinaryOp op <$> evaluate env t1 <*> evaluate env t2

evaluate env (Num val) = Right val

evaluate env (Var name) = 
  case lookup name env of
    Nothing -> Left name
    Just val -> Right val


------------------------------
------ A stack machine  ------


data Instruction
  = Push Double
  | Load String
  | Bop BinaryOp
  | Abso
  deriving (Eq, Show)

data ExecutionError
  = StackUnderflow Instruction
  | MissingVar String
  deriving (Eq, Show)

type Stack = [Double]

-- Stack machine executor takes an environment, an initial stack, and a
-- list of instructions. It returns a resulting stack, or else an
-- error.
execute :: Environment -> Stack -> [Instruction] ->
          Either ExecutionError Stack

-- If there are no instructions left to execute, just return the stack:
execute _ stack [] = Right stack

-- A push instruction adds a value to the stack, and continues with
-- subsequent instructions:
execute env stack (Push val : prog) =
  execute env (val : stack) prog

-- A binary operator pattern-matches to find two values on the top of
-- the stack, and then applies the operator, pushes the result, and
-- continues with subsequent instructions:
execute env (y:x:stack) (Bop op : prog) =
  execute env (runBinaryOp op x y : stack) prog

-- TODO: There are still three clauses for you to complete:

------ My Solution-------------
  
execute env (x : stack) (Abso : prog) = 
  execute env (runUnaryOp Abs x : stack) prog

---------------------------
------ A compiler!   ------

-- There are no more tasks for you to complete in the rest of this
-- file.

compile :: Arith -> [Instruction]
compile (Num x) = [Push x]
compile (Var name) = [Load name]
compile (UnaryOp Sqrt t) = compile (BinaryOp Pow t (Num 0.5))
compile (UnaryOp Neg t) = compile (BinaryOp Sub (Num 0) t)
compile (UnaryOp Abs t) = compile t ++ [Abso]
compile (BinaryOp op t1 t2) = compile t1 ++ compile t2 ++ [Bop op]


---------------------------------------------
------ Sample programs and expressions ------

-- You don't need to do anything in this section, but please leave
-- these definitions here. They are used in some of the tests.

egCircle :: Arith
egCircle =
  BinaryOp Mul (Num pi) (BinaryOp Pow (Var "r") (Num 2))


egEuclid :: Arith
egEuclid =
  UnaryOp Sqrt
    (BinaryOp Add
       (BinaryOp Pow (Var "x") (Num 2))
       (BinaryOp Pow (Var "y") (Num 2)))

egQuadratic :: Arith
egQuadratic =
  BinaryOp Div
    (BinaryOp Add
       (UnaryOp Neg (Var "b"))
       (UnaryOp Sqrt
          (BinaryOp Sub
             (BinaryOp Pow (Var "b") (Num 2))
             (BinaryOp Mul
                (Num 4)
                (BinaryOp Mul (Var "a") (Var "c"))))))
    (BinaryOp Mul (Num 2) (Var "a"))

egManhattan :: Arith
egManhattan =
  BinaryOp Add
    (UnaryOp Abs (BinaryOp Sub (Var "x1") (Var "x2")))
    (UnaryOp Abs (BinaryOp Sub (Var "y1") (Var "y2")))


stEuclid :: [Instruction]
stEuclid =
  [Load "x", Push 2, Bop Pow,
   Load "y", Push 2, Bop Pow,
   Bop Add, Push 0.5, Bop Pow]
