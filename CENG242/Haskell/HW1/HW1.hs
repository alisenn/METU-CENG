module HW1 (
    form,
    constGrid,
    flatten,
    access,
    slice,
    vcat,
    hcat,
    without,
    matches2d
) where

-- do not modify the module declaration above!
-- this will ensure that you cannot load (compile)
-- the module without implementing all of the functions.

-- If you have functions you do not want to implement,
-- leave them as undefined or make them have another
-- default value. If you fully remove any of their definitions,
-- that will be a compilation error during evaluation,
-- and you will be eligible for (yay!) a 5 point deduction
-- (that's bad for your grade). Runtime errors in your code 
-- (rather than compilation errors) are acceptable and will simply
-- result in you getting zero from the specific test case causing
-- an error.
import Data.Map (fromListWith, toList)
-------------------------
-- Fellowship of the Grid (25, 5, 5, 5 points)
import Data.List
--Form okey.
form :: [a] -> (Int, Int) -> [[a]] 
form [] _ = []
form xs (a,b) =
    let (ys, zs) = splitAt b xs
    in  ys : form zs (a,b)

--chunkOf fonksiyonunun implementasyonunun aynısı


--Constgrid okey.
constGrid :: a -> (Int, Int) -> [[a]]
constGrid cons (a,b) =take a ( repeat (replicate b cons))


--Flatten is okey
flatten :: [[a]] -> [a]
flatten xss = foldr (++) [] xss

--access is okey.
access :: [[a]] -> (Int, Int) -> a
access list (a,b) = list!!a !!b

----------------------------
-- The Two Signatures (10, 5, 5, 10 points)
--once row'ları slice et
--bir variable'a at
--variable'ın icini ayrı ayrı [1..n] ve !! kullanarak slice et.
--slice grid (i1,i2) (j1,j2) = (drop i1 $ take i2 grid) rowu doru slice ediyor.
--map (drop 1) $ (take 3) $ slice grid (1,3) (0,3)
--slice grid (i1,i2) (j1,j2) = map (drop j1) $ (take j2) $ (drop i1 $ take i2 grid)
--slice is okey.
slice :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
slice grid (i1,i2) (j1,j2) = map (drop j1) $ map (take j2) $ (drop i1 $ take i2 grid)
--vcat is okey
vcat :: [[a]] -> [[a]] -> [[a]]
vcat a b = a ++ b
--hcat is okey
hcat :: [[a]] -> [[a]] -> [[a]]
hcat a b = zipWith (++) a b

--without grid (i1,i2) (j1,j2) = map (takedrop j1 (j2-j1)) $ takedrop i1 (i2 - i1) grid
takedrop :: Int -> Int -> [a] -> [a]
takedrop _ _ [] = []
takedrop n m l  = take n l ++ (drop (n + m) l)

without :: [[a]] -> (Int, Int) -> (Int, Int) -> [[a]]
without grid (i1,i2) (j1,j2) = map (takedrop j1 (j2-j1)) $ takedrop i1 (i2 - i1) grid
----------------------------
-- Return of the Non-trivial (30 points, 15 subject to runtime constraints)



listSearchinList pattern [] i result = []
listSearchinList pattern all@(y:ys) i result 
            | (length all) <(length pattern) = result
            |(take (length pattern) (y:ys)) == pattern = listSearchinList pattern ys (i+1) (result++[i]) 
            | otherwise = listSearchinList pattern ys (i+1) result
            
match gridRowList patterRowList patternIndex gridIndex = map (\x -> ( ( gridIndex- patternIndex) ,x)) $ listSearchinList patterRowList gridRowList 0 []

mainMatchPattern grid [] j i result =result

mainMatchPattern grid all@(y:ys) j i result 
            | (length all) == 1 = result
            |otherwise = mainMatchPattern grid ys (j+1) i ((match grid y j i)++result)

mainMatchGrid [] allPattern j i result = result
mainMatchGrid all@(x:xs) allPattern j i result 
            | (length all) == 1 = result
            |otherwise = mainMatchGrid xs allPattern j (i+1) ((mainMatchPattern x allPattern j i [])++result)


--frequency xs l = filter ((==l).snd) (toList (fromListWith (+) [(x, 1) | x <- xs]))

tuplee (x,y)=x

matches2d :: Eq a => [[a]] -> [[a]] -> [(Int, Int)]
matches2d a b = if (length (b!!0)) > (length (a!!0) ) then []
				--else map tuplee (frequency (mainMatchGrid a b 0 0 []) ((length b)-1))
				else mainMatchGrid a b 0 0 []
				


--matches2d a b = if (length (b!!0)) > (length (a!!0) ) then []
--				else map tuplee (frequency (mainMatchGrid a b 0 0 []) ((length b)-1))
----------------------------

--If the pattern is larger than the grid, the result will be empty. I think is okey.
-- a = form [1..20] (1,3) b = form [1..21] (1,6) matches2d a b

-- What is undefined? Just a value that will cause an error
-- when evaluated, from the GHC implementation:
-- undefined = error "Prelude.undefined"
-- But it allows your module to be compiled
-- since the function definitions will exist.
