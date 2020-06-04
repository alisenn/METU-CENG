--ghc 7.10
import Data.List
import Data.Maybe (mapMaybe)
import Expression
import Parser
import Data.List
import Data.Typeable

a = [[1,2,3],[4,5,6]] 
gridMap :: (a -> b) -> [[a]] -> [[b]]
gridMap = map . map
ilksoru = gridMap (+1) a

mapIf p f = map (\x -> if p x then f x else x)
gridMapIf :: (a -> Bool) -> (a -> a) -> [[a]] -> [[a]] 

gridMapIf cond f c = [ mapIf (cond) (f) xs | xs <- c ]
dd= gridMapIf (<3) (+1) a

--Exxxxxxxxxxxxxxxxxxxxxxpreeeeeeeeeeessssssssssssionllllllaaaaaaaarrrrrrrrrrrrrrrrrrrrrrr
--evalExpr :: [(String, Int)]-> ExprV -> Int 
example1 = (Leaf (Variable "a"))

evaluateTree :: (ExprV,Bool) -> (ExprV,Bool)
evaluateTree  ((Leaf (Constant (a))),bool) = ((Leaf (Constant (a))),bool)
evaluateTree  ((Leaf (Variable (a))),bool) = ((Leaf (Variable (a))),True)
--if true then stop because it is a variable not a string *this is pattern matching
evaluateTree  (all@(BinaryOperation p (Leaf (Variable (a)))(Leaf (Variable (b)))),bool) = (all,True)
evaluateTree  (all@(BinaryOperation p (Leaf (Variable (a)))(Leaf (Constant (b)))),bool) = (all,True)
evaluateTree  (all@(BinaryOperation p (Leaf (Constant (a)))(Leaf (Variable (b)))),bool) = (all,True)

evaluateTree  (all@(UnaryOperation p (Leaf (Variable (a)))),bool) = (all,True)

--do the arithmetic
evaluateTree (BinaryOperation op (Leaf (Constant a)) (Leaf (Constant b)),bool)
                            | op==Plus=(Leaf (Constant(a+b)),bool)
                            | op==Times=(Leaf (Constant(a*b)),bool)

evaluateTree (UnaryOperation Minus (Leaf (Constant a)),bool)=((Leaf (Constant(-a))),bool)
--evaluateTree (UnaryOperation Minus (a),bool)=(UnaryOperation Minus (fst (evaluateTree(a,bool))),bool) 
                                                          
evaluateTree (BinaryOperation op (a) (b),True) =evaluateTree (BinaryOperation op (a) (b),True)
evaluateTree (BinaryOperation op (a) (b),bool) 
                                                | ((snd result1)==True || (snd result2)==True ) = (( BinaryOperation op (fst (result1)) (fst (result2)),True)) --binarylerden herhangi biri variabe ise true set et ki dursun
                                                | otherwise = (evaluateTree( BinaryOperation op (fst (result1)) (fst (result2)),bool)) --degilse normal devam
                                                where result1 = (evaluateTree( a,bool))
                                                      result2 = (evaluateTree( b,bool))
------------------unaryy-------------------
evaluateTree (UnaryOperation op (a) ,bool) --ustekinin aynisi unary olarak
                                        | (snd result1)==True = (UnaryOperation op (fst (result1)),bool)
                                        | otherwise = (evaluateTree( UnaryOperation op (fst (result1)), bool ))
                                        where result1 = (evaluateTree( a,bool)) 
------------------unaryy-------------------

searchAndUpdate ::  [(String,Int)]->String->ExprV 
searchAndUpdate []  string =  (Leaf (Variable (string))) --basecase
searchAndUpdate (x:xs)  string | fst (x) == string = (Leaf (Constant (snd (x)))) --if variable found change it with constant
                               | otherwise = searchAndUpdate xs string
                               
--apply all to the tree
traverseAndUpdateTree :: [(String,Int)] -> ExprV-> ExprV --
traverseAndUpdateTree list (Leaf (Variable (a)))= searchAndUpdate list a 
traverseAndUpdateTree list (Leaf (Constant (a)))= (Leaf (Constant (a))) 
traverseAndUpdateTree list (BinaryOperation p left right) =BinaryOperation p (traverseAndUpdateTree list left) (traverseAndUpdateTree list right) 
traverseAndUpdateTree list (UnaryOperation p child) =UnaryOperation p (traverseAndUpdateTree list child) 
--
--if constant add to the result list
checkEvaluatedTree :: [(String, Int)]-> ExprV ->String->[(String, Int)] 
checkEvaluatedTree list (Leaf (Constant (value))) string = list++[(string,value)] 
checkEvaluatedTree list _ _= list
--main function that collects all helper functions together
updateAndEvaluateTree :: [(String, ExprV)] ->[(String,Int)]-> [(ExprV)]
updateAndEvaluateTree [] _= [] 
updateAndEvaluateTree (x:xs) list = [(evaluatedTree)]++updateAndEvaluateTree xs uptadetList 
                                    where uptadetList=checkEvaluatedTree list evaluatedTree (fst(x)) 
                                          evaluatedTree=evaluatedTree
                                           where 
                                                 evaluatedTree=fst (evaluateTree(traverseAndUpdateTree list (snd (x)) ,False))

onlyconst (Leaf (Constant a)) = a
--expression1 = BinaryOperation Plus (BinaryOperation Plus (UnaryOperation Minus (BinaryOperation Plus (Leaf (Constant 3)) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Constant 7))))) (BinaryOperation Times (Leaf (Variable "b")) (Leaf (Variable "b")))) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Variable "var")))
--expression1list =   [("b", 10), ("var", 1)]
--withoutvar = traverseAndUpdateTree expression1list expression1
--fstoftuple = evaluateTree (withoutvar,False)
--res = onlyconst $ fst fstoftuple
evalExpr :: [(String, Int)] -> ExprV -> Int
evalExpr expression1list expression1 = onlyconst $ fst fsttuple 
                            where fsttuple = evaluateTree (withoutvar,False)
                                    where withoutvar = traverseAndUpdateTree expression1list expression1
                                    
a11 = [("x", -2), ("y", 0), ("z", 1)]
b11 = BinaryOperation Plus (BinaryOperation Plus (BinaryOperation Times (BinaryOperation Times (Leaf (Variable "x")) (Leaf (Variable "y"))) (Leaf (Variable "z"))) (BinaryOperation Times (Leaf (Variable "x")) (Leaf (Variable "x")))) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Variable "z")))

a22 = UnaryOperation Minus (BinaryOperation Plus (Leaf (Constant 3)) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Constant 7))))
a33 = BinaryOperation Plus (BinaryOperation Plus (UnaryOperation Minus (BinaryOperation Plus (Leaf (Constant 3)) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Constant 7))))) (BinaryOperation Times (Leaf (Variable "b")) (Leaf (Variable "b")))) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Variable "var")))
b33 = [("b", 10), ("var", 1)]

--evalExpr [] a22
--------------------------------------sadece variable donn----------44444-------
--addToList list (x:xs) 
  --                  | x == Leaf(Variable a) = a:list
  --                  | otherwise = addToList list xs


--treeToList :: (Ord a) => Tree a -> [a]   
putToList :: ExprV ->[String] -> [String] --
putToList (Leaf (Variable (a))) list = a:list
putToList (Leaf (Constant (a))) list = list
putToList (BinaryOperation p left right) list = (putToList left list) ++ (putToList right list) 
putToList (UnaryOperation p child) list = (putToList child list) 
--
rmdups :: (Ord a) => [a] -> [a]
rmdups = map head . group . sort

getVars :: ExprV -> [String] 
getVars ex = rmdups $ putToList ex []
--------------------------------------sadece variable donn-----------44444------
b1212 = BinaryOperation Plus (BinaryOperation Plus (BinaryOperation Times (Leaf (Constant 3)) (Leaf (Constant 17))) (BinaryOperation Times (UnaryOperation Minus (Leaf (Variable "a"))) (Leaf (Variable "x")))) (Leaf (Variable "ceng242"))
aw=BinaryOperation Plus (BinaryOperation Times (Leaf (Variable "myVar")) (Leaf (Variable "a"))) (BinaryOperation Times (BinaryOperation Times (UnaryOperation Minus (Leaf (Variable "y"))) (Leaf (Variable "y"))) (Leaf (Variable "z")))

--searchAndCount ::  ExprV -> String -> Int -> Int
--searchAndCount (Leaf (Variable (a))) var count 
--                                    | var == a = searchAndCount (Leaf (Variable (a))) var (count+1) -- parantessiz error verir tamamdır eyv
--                                    | otherwise = searchAndCount (Leaf (Variable (a))) var (count) --kanka ben annemi pazara goturim yarım ya da 1 saate gelirim s                      en de oyun oyna isterse  tamam knk ben bakarım o sırada bb tmmdır grousuz C@
--searchAndCount (Leaf (Constant (a))) var count = 0
--searchAndCount (BinaryOperation p left right) var count = (searchAndCount left var count) (searchAndCount right var count) 
--searchAndCount (UnaryOperation p child) var count = (putToList child var count) 
--  tamam kank
takeDerivative :: ExprV ->String->ExprV
takeDerivative  (Leaf (Constant (a))) string= (Leaf (Constant (0)))

takeDerivative  (Leaf (Variable (a))) string | a==string= (Leaf (Constant (1)))
                                            | otherwise= (Leaf (Constant (0)))
takeDerivative (BinaryOperation Plus left right) string= BinaryOperation  Plus (takeDerivative left string) (takeDerivative right string)
takeDerivative (BinaryOperation Times left right) string=BinaryOperation  Plus (BinaryOperation Times (takeDerivative left string) right ) (BinaryOperation Times left (takeDerivative right string) )
takeDerivative (UnaryOperation op child) string=UnaryOperation op (takeDerivative child string)

evalDeriv::[(String, Int)]->String->ExprV->Int
evalDeriv list string expression = onlyconst $ fst fsttuple 
                            where fsttuple = evaluateTree (withoutvar,False)
                                    where  expression1= takeDerivative expression string 
                                           withoutvar = traverseAndUpdateTree list expression1

rer = BinaryOperation Plus (BinaryOperation Plus (BinaryOperation Plus (Leaf (Constant 3)) (Leaf (Variable "y"))) (Leaf (Variable "z"))) (BinaryOperation Times (Leaf (Constant 5)) (Leaf (Variable "myVar")))

example11=(BinaryOperation Times (BinaryOperation Plus (Leaf (Variable "y")) (Leaf (Constant 5))) (BinaryOperation Times (Leaf (Variable "x")) (Leaf (Variable "x"))))




