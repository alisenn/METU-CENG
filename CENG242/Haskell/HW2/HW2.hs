module HW2 (
    parse, -- reexport for easy terminal use
    foldAndPropagateConstants,
    assignCommonSubexprs,
    reducePoly
) where

import Expression
import Parser
import Data.List
import Data.Typeable


-- Do not change the module definition and imports above! Feel free
-- to modify the parser, but please remember that it is just a helper
-- module and is not related to your grade. You should only submit
-- this file. Feel free to import other modules, especially Data.List!


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

evaluateTree (UnaryOperation Minus (Leaf (Constant a)),bool)=(UnaryOperation Minus (Leaf (Constant(-a))),bool)
evaluateTree (UnaryOperation Minus (a),bool)=(UnaryOperation Minus (fst (evaluateTree(a,bool))),bool) 
                                                          
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
updateAndEvaluateTree :: [(String, ExprV)] ->[(String,Int)]-> [(String,ExprV)]
updateAndEvaluateTree [] _= [] 
updateAndEvaluateTree (x:xs) list = [((fst x),evaluatedTree)]++updateAndEvaluateTree xs uptadetList 
                                    where uptadetList=checkEvaluatedTree list evaluatedTree (fst(x)) 
                                          evaluatedTree=evaluatedTree
                                           where 
                                                 evaluatedTree=fst (evaluateTree(traverseAndUpdateTree list (snd (x)) ,False))


foldAndPropagateConstants :: [(String, ExprV)] -> [(String, ExprV)]
foldAndPropagateConstants list = updateAndEvaluateTree list []
foldAndPropagateConstants _ = []



findAllSuitableLeaves:: ExprV->[(ExprV)]
findAllSuitableLeaves (Leaf child)=[]
findAllSuitableLeaves all@(BinaryOperation op (Leaf left) (Leaf right)) = [all]
findAllSuitableLeaves all@(UnaryOperation op (Leaf child)) = [all]
findAllSuitableLeaves (BinaryOperation op (left) (right))=findAllSuitableLeaves(left) ++findAllSuitableLeaves(right)
findAllSuitableLeaves (UnaryOperation op (child) )=findAllSuitableLeaves(child)

findHowManyOfTheLeave ::[(ExprV)]->[(ExprV)]->[((ExprV,Int),String)]
findHowManyOfTheLeave [] _ =[]
findHowManyOfTheLeave (x:xs) wholelist = [findHowManyOfTheLeaveHelper x wholelist ((x,0),"")]++findHowManyOfTheLeave xs wholelist 


findHowManyOfTheLeaveHelper ::(ExprV)->[(ExprV)]->((ExprV,Int),String)->((ExprV,Int),String)
findHowManyOfTheLeaveHelper _ [] result = result
findHowManyOfTheLeaveHelper expression (x:xs) ((tree,count),string)| expression==x =findHowManyOfTheLeaveHelper expression xs ((tree,count+1),string)
                                                          | otherwise =findHowManyOfTheLeaveHelper expression xs ((tree,count),string)

giveNameToLeaves::[((ExprV,Int),String)]->[((ExprV,Int),String)]->Int->([((ExprV,Int),String)],Int)
giveNameToLeaves [] result count =(result,count)
giveNameToLeaves all@(x:xs) result number_counter | ((snd x) == "") && ((snd (fst x))>1) = giveNameToLeaves (drop 1 updated_list) (result++[updated_list!!0]) (number_counter+1)
                                                 | otherwise= giveNameToLeaves xs result number_counter
                                                    where updated_list=(giveNameToLeavesHelper x all (number_counter))
                                                 
                                                 
giveNameToLeavesHelper ::((ExprV,Int),String)->[((ExprV,Int),String)]->Int->[((ExprV,Int),String)]
giveNameToLeavesHelper _ [] _  = []
giveNameToLeavesHelper (a,string1) ((b,string2) :xs) count_number  | a==b = [(b,("&_"++(show count_number)))] ++ giveNameToLeavesHelper (a,string1) xs count_number
                                                                   | otherwise = [(b,string2)]++ giveNameToLeavesHelper (a,string1) xs count_number

findAndChangeAllSuitableLeaves:: ExprV->[((ExprV,Int),String)]->ExprV
findAndChangeAllSuitableLeaves (Leaf child) _=(Leaf child)
findAndChangeAllSuitableLeaves all@(BinaryOperation op (Leaf left) (Leaf right)) list = (findAndChangeAllSuitableLeavesHelper all list)
findAndChangeAllSuitableLeaves all@(UnaryOperation op (Leaf child)) list = (findAndChangeAllSuitableLeavesHelper all list)
findAndChangeAllSuitableLeaves (BinaryOperation op (left) (right)) list=(BinaryOperation op ((findAndChangeAllSuitableLeaves left list)) ((findAndChangeAllSuitableLeaves right list)))
findAndChangeAllSuitableLeaves (UnaryOperation op (child) ) list=(UnaryOperation op ((findAndChangeAllSuitableLeaves child list)) )

findAndChangeAllSuitableLeavesHelper ::ExprV->[((ExprV,Int),String)]->ExprV
findAndChangeAllSuitableLeavesHelper tree [] =tree
findAndChangeAllSuitableLeavesHelper expression (x:xs)  | (fst (fst x) )==expression = (Leaf (Variable (snd x)))
                                                        | otherwise=findAndChangeAllSuitableLeavesHelper expression xs
                                                       
concertToSuitableFormat::[((ExprV,Int),String)]->[(String,ExprV)] 
concertToSuitableFormat []=[]
concertToSuitableFormat (((expression,count),string):xs)=[(string,expression)]++concertToSuitableFormat xs 


--in here for unary op with the op and the valuea assign a var
--for binary op assign two variable with the op
assignCommonSubexprs :: ExprV -> ([(String, ExprV)], ExprV)
assignCommonSubexprs tree= assignCommonSubexprsHelper tree 0 []

assignCommonSubexprsHelper:: ExprV ->Int-> [(String, ExprV)]->([(String, ExprV)], ExprV)
assignCommonSubexprsHelper tree count list | updatedTree==tree=(list,updatedTree)
                                           | otherwise = assignCommonSubexprsHelper updatedTree updatedCount (list++newlist)
                                               where 
                                                (changeTree,updatedCount)= (giveNameToLeaves (findHowManyOfTheLeave (findAllSuitableLeaves tree) (findAllSuitableLeaves tree)) [] count) 
                                                updatedTree=findAndChangeAllSuitableLeaves tree changeTree  
                                                newlist=concertToSuitableFormat changeTree


reducePoly :: ExprV -> ExprV
reducePoly _ = notImpl 

-- an extra dummy variable, so as to not crash the GUI
notImpl :: ExprV
notImpl = Leaf $ Variable "not Implemented"





--(BinaryOperation op (Leaf (Variable a)) (Leaf (Variable b)))
--(BinaryOperation op (Leaf (Variable a)) (Leaf (Constant b)))
--(BinaryOperation op (Leaf (Constant a)) (Leaf (Variable b)))
--(BinaryOperation op (Leaf (Constant a)) (Leaf (Constant b)))
--(UnaryOperation op (Leaf (Constant a)))
--(UnaryOperation op (Leaf (Variable a)))