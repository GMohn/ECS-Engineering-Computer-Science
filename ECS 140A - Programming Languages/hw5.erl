% hw 5 ecs 140a

-module(hw5).
-export([print_hello/0,is_leap/1,prime/1,factors/1,gcd/2,lcm/2,dist/4,averages/0,count_occ/2,exponent/2]).

%MIDTERM problem 1
exponent(X, Y) when is_integer(X), is_integer(Y), Y >= 0 ->
    exponent(X, Y, 1).

exponent(_, 0, Acc) ->
    Acc;
exponent(X, Y, Acc) when Y rem 2 =:= 1 ->
    exponent(X, Y - 1, Acc * X);
exponent(X, Y, Acc) ->
    exponent(X * X, Y div 2, Acc).


% PROBLEM 1 verify if the given year is a leap year or not.
% year must be divisible by 4 except for end of century years which must be divisble by 400
is_leap(Year) when Year >= 0,Year rem 4 =:= 0, Year rem 100 > 0 -> true;
is_leap(Year) when Year >= 0, Year rem 400 =:= 0 -> true;
is_leap(_) -> false.

% PROBLEM 2 determine prime factors of a given positive integer
prime(N,M) when N == M -> true;
prime(N,M) when N rem M == 0 -> false;
prime(N,M) -> prime(N,M+1).

prime(N) when N < 2 -> false;
% quotient becomes 1
prime(N) when N rem 1 == 0 -> prime(N,2).

factors(N,M,L) when N == M -> [M|L];
factors(N,M,L) when N < M -> L;
% divide quotient by the smallest prime number smallest prime number should divide the number exactly.
factors(N,M,L) when N rem M == 0 -> factors(N div M,M,[M|L]);
factors(N,M,L) -> factors(N,M+1,L).

factors(N) -> factors(N,2,[]).


% PROBLEM 3 determine the LCM of two positive Ints. Use Euclid's algo.
% First the Greatest Common Factor of the two numbers is determined from Euclid's algorithm. 
gcd(A,B) when A == 0; B == 0 -> 0;
gcd(A,B) when A == B -> A;
gcd(A,B) when A > B -> gcd(A-B, B);
gcd(A,B) -> gcd(A, B-A).

% Then the product of the two numbers divided by the Greatest Common Factor results in the Least Common Factor.
lcm(A,B) -> (A*B) div gcd(A, B).

% PROBLEM 4 determine the Euclidean distance between two points in a 2-D plane 
% Distance formula is sqrt((x_1-x_2)^2+(y_1-y_2)^2)
dist(X1,Y1,X2,Y2)->
    math:sqrt(math:pow((X1-X2),2)+math:pow((Y1-Y2),2)).

% count occurences of list 
count_occ(_, []) -> 0;
count_occ(X, [X|XS]) -> 1 + count_occ(X, XS);
count_occ(X, [_|XS]) -> count_occ(X, XS).

% PROBLEM 5 
% determine mean median and mode of a given series of 10 positive integers.
averages()->
    List1 = [1,2,2,3,4,5,6,7,2,9],
    lists:sort(List1),
    io:fwrite("Mean: "),
    lists:sum(List1) / 10.
    % median
    %io:fwrite("Median: ").
    %lists:nth(5,List1),
    % mode NOT FINISHED
    %count_occ(2,List1).
    


print_hello()->
    io:fwrite("Hello everybody!\nThis is so cool! hehe haha\n").