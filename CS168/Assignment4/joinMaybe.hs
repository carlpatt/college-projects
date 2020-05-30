joinMaybe :: Maybe (Maybe a) -> Maybe a
joinMaybe (Nothing) = Nothing
joinMaybe (Just Nothing) = Nothing
joinMaybe (Just(Just(a))) = Just(a)

