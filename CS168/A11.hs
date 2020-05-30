{-# LANGUAGE OverloadedStrings #-}

import Data.Monoid ((<>))
import Network.HTTP.Types.Status
import Network.HTTP.Types.Header
import Network.Wai as Wai
import System.Random (randomIO)
import Text.Blaze.Html.Renderer.Utf8 (renderHtml)
import Text.Blaze.Html5 as H hiding (main)
import Text.Blaze.Html5.Attributes as A
import qualified Data.ByteString.Char8 as BS
import qualified Data.Text as T
import qualified Network.Wai.Handler.Warp as Warp

myPage :: Html
myPage = docTypeHtml $ do
  h1 "My home page"
  p $ do
    "Hello and welcome to my tiny website"
  p $ do
    "click on the link below to see a tiny factoid about me"  
  p $ do
    a ! href "/about" $ "About me"

aboutPage :: Html
aboutPage = docTypeHtml $ do
  h1 "About me"
  p $ do
    "One interesting fact about me..."
  p $ do
    "is that I am a Powerlifter"
  p $ do
    a ! href "/" $ "Click here to go back to the homepage"

errorPage :: Html
errorPage = docTypeHtml $ do
  h1 "Page not available"
  p $ do
    "Error 404 page not available"
  p $ do
    a ! href "/" $ "Click here to go back to the homepage"
  p $ do
    a ! href "/about" $ "Or click here to go to my about me"


app :: Wai.Application
app req respond =
  case fmap T.unpack $ Wai.pathInfo req of
    [] -> do 
            respond $ responseLBS ok200 [("Content-Type","text/html")]
              $ renderHtml $ myPage 
    ["about"] -> do
                  respond $ responseLBS ok200 [("Content-Type","text/html")]
                    $ renderHtml $ aboutPage
    _ -> do 
          respond $ responseLBS status404 [("Content-Type","text/html")]
            $ renderHtml $ errorPage 


{-
app :: Wai.Application
app req respond = do
  BS.putStrLn $ Wai.requestMethod req <> " " <> Wai.rawPathInfo req
  respond $ responseLBS ok200 [("Content-Type","text/html")]
    $ renderHtml $ aboutPage
-}

startServer :: IO ()
startServer = do
  putStrLn "Listening..."
  Warp.runEnv 3000 app

main :: IO ()
main = startServer
