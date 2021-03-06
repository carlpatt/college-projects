{-# LANGUAGE OverloadedStrings #-}
import Control.Monad (join, unless, forM_)
import Control.Monad.Reader
import Control.Monad.Writer
import Data.Char (isDigit, isUpper, isPunctuation)
import Data.Maybe (fromMaybe)
import Data.Monoid ((<>))
import Network.HTTP.Types.Header (Header, hContentType)
import Network.HTTP.Types.Status (ok200)
import Network.HTTP.Types.URI (Query, decodePath)
import Text.Blaze.Html.Renderer.Utf8 (renderHtml)
import Text.Blaze.Html5 as H hiding (main)
import Text.Blaze.Html5.Attributes as A
import qualified Data.ByteString.Char8 as BS
import qualified Data.Text as T
import qualified Data.Text.Encoding as TE
import qualified Network.Wai as Wai
import qualified Network.Wai.Handler.Warp as Warp

setPassForm :: Html
setPassForm = do
  -- TODO: create your password form here. Name the inputs
  -- password1 and password2.
  h3 "Set a new password"
  H.form ! method "POST" $ do
  p $ input ! type_ "password" ! name "password1" ! placeholder "Password"
  p $ input ! type_ "password" ! name "password2" ! placeholder "Re-enter Password"
  p $ input ! type_ "submit" ! value "Submit"
  

heads :: [Header]
heads = [(hContentType, "text/html")]

app :: Wai.Application
app req respond = do
  case Wai.requestMethod req of
    "POST" -> do
      body <- Wai.requestBody req
      let (_, query) = decodePath $ "?" <> body
          passwordOrError = runQuery query checkPass
      respond $ Wai.responseLBS ok200 heads $ renderHtml $
        case passwordOrError of
          Left errs -> do
            h3 "There were errors"
            ul $ forM_ errs $ \e -> do
              li $ toHtml e
            -- Makes testing easier
            p $ do 
              a ! href "/" $ "Back to form"
          Right s -> do
            h3 "Password successfully changed"
            -- Makes testing easier
            p $ do 
              a ! href "/" $ "Back to form"
           -- code $ toHtml s   -- TEMPORARY: reveals password!
    _ ->
      respond $ Wai.responseLBS ok200 heads $ renderHtml setPassForm

checkPass :: Valid T.Text
checkPass = do
  p1 <- textField "password1"
  p2 <- textField "password2"
  when (p1 /= p2) $ emit "Passwords do not match"
  goodPass p1

-- TODO: your task is to do the proper validations in `goodPass`. You
-- can either use `expect` as I did in `validPhone` and `validEmail`,
-- or you can directly use tools like `when`, `unless`, and `emit`. (As
-- given, this accepts any password of any length.)

goodPass :: T.Text -> Valid T.Text
goodPass p = do
  expect (\c -> T.length c >= 8) "Password too short" p
  expect (\c -> T.any isUpper c) "Password is missing an uppercase letter" p
  expect (\c -> T.any isPunctuation c) "Password is missing a symbol" p
  expect (\c -> T.any isDigit c) "Password is missing a number" p
  return p
-- Main program:

startServer :: IO ()
startServer = do
  putStrLn "Listening..."
  Warp.runEnv 3000 app

main :: IO ()
main = startServer

-- Given code from notes: probably don't need to change anything below.

type Valid a = WriterT [T.Text] (Reader Query) a

runQuery :: Query -> Valid a -> Either [T.Text] a
runQuery q m =
  case runReader (runWriterT m) q of
    (a, []) -> Right a         -- Success
    (_, errs) -> Left errs     -- Failure

field :: BS.ByteString -> Valid (Maybe BS.ByteString)
field name = do
  query <- ask
  return $ join $ lookup name query

emit :: T.Text -> Valid ()
emit err = tell [err]
 
textField :: BS.ByteString -> Valid T.Text
textField name =
  T.strip . TE.decodeUtf8 . fromMaybe "" <$> field name

expect :: (a -> Bool) -> T.Text -> a -> Valid a
expect prop err a = do
  unless (prop a) $ emit err
  return a
