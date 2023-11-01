 --https://stackoverflow.com/questions/18723381/rounding-to-specific-number-of-digits-in-haskell
 -- helper rounding function
truncate' :: Double -> Int -> Double
truncate' x n = (fromIntegral (floor (x * t))) / t
    where t = 10^n


vieta :: Double -> Int -> Double
vieta x y
 | y == 0 = x
 | otherwise = x * vieta (sqrt (0.5 + (0.5 * x))) (y - 1)

main = do
 print (truncate' (1 / (vieta (sqrt (0.5 + (0.5 * sqrt 0.5))) 13 / (2 * sqrt 2))) 8)