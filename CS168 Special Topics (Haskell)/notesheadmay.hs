headMay :: [a] -> Maybe a
headMay [] = Nothing
headMay (h:_) = Just h

myName = "Chris"

newName1 =
  case headMay myName of
    Nothing -> Nothing
    Just c -> Just (c : "arl")
    
newName2 = fmap (: "arl") (headMay myName)

newName3 = (:"arl") <$> headMay myName


traal (x:xs) = x : x : traal xs
traal [] = []

traalCase xs =
  case xs of
       [] -> []
       (x:xs) -> x : x : traalCase xs



