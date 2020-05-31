isSquare :: Integral n => n -> Bool
isSquare x = ((^2) . round . sqrt . fromIntegral) x == x
