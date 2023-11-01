
asterisk_pat :: Int -> Int -> IO ()
asterisk_pat depth space
  | depth <= 0 = return ()
  | otherwise = do
      putStr (replicate_spaces space)
      putStr (replicate_stars depth)
      putStrLn ""
      asterisk_pat (depth - 1) (space + 1)

replicate_spaces :: Int -> String
replicate_spaces n = replicate n ' '

replicate_stars :: Int -> String
replicate_stars n = replicate n '*'

main :: IO ()
main = asterisk_pat 5 0