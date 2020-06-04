:- module(hw, [cost/2, sort_units/2, buyable/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

cost1(active_unit(Name,Star),Cost):- 
    unit(Name,C1,_), 
    Cost is 3**(Star-1) * C1.
    
cost(List,Cost):-
    maplist(cost1,List, Rss),
    sum_list(Rss,Res),
    Cost is Res.
%2    
less(X,Y):- unit(X,A,_), unit(Y,B,_), A<B.
sort_units( List, SortedList) :-
    swap( List, List1 ), ! ,
    sort_units( List1, SortedList) .
sort_units(List, List).

swap([X,Y|Rest], [Y,X|Rest]):-less(X,Y), ! .
swap([Z|Rest],[Z|Rest1]) :- swap(Rest, Rest1 ).

%3
append([],L,L).
append([H|T],L2,[H|L3]) :- append(T,L2,L3).

buyable([],M,[],M).
buyable([A|B],M,L,R):- unit(A,X,_), M >= X, buyable(B,M-X,L1,R1), R is R1, append([A],L1,L).
buyable([_|B],M,L,R):- buyable(B,M,L,R).
