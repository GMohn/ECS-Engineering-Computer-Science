{-|


                            Online Haskell Compiler.
                Code, Compile, Run and Debug Haskell program online.
Write your code in this editor and press "Run" button to execute it.

-}


fib :: Int -> Int
fib n
    | n < 2     = n                 
    | otherwise = fib (n - 1) + fib (n - 2)  

main :: IO ()
main = do
    
    print [fib n | n <- [1..20]]                 