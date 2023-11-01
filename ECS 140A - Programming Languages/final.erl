% final ecs 140a

-module(final).
-import(math,[pow/2]).
-export([print_hello/0,kth_digit/2,find_e/2,fact/1,derivative/2]).


% Question 4 kth digit
kth_digit(K, N) ->
  if
    K >= 4 ->
      0;
    K == 1 -> 
      N rem 10;
    true ->
      kth_digit(K-1, N div 10)
    end.

% Question 5  roots of quad eqn using newton raphson method 
% x_(n+1) = x_n - f(x_n)/f'(x_n)
derivative( F, Dx ) ->
        fun( X ) ->
                ( F( X + Dx ) - F ( X ) ) / Dx
        end.

% Question 6 display e
find_e(N, X) -> 
    case N of
        1 -> 1;
        _ -> pow(X, N-1) / fact(N-1) + find_e(N-1, X) % series
    end.

fact(N) -> 
  case N of
        0 -> 1;
        1 -> 1;
        _ -> N * fact(N - 1)
  end.
print_hello()->
    io:fwrite("Hello everybody!\nThis is so cool! hehe haha\n").