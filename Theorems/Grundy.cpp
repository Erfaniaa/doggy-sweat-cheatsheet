Grundy numbers. For a two-player, normal-play (last to move wins) game on a graph (V, E): G(x) = mex({G(y) : (x, y) ∈ E}), where mex(S) = min{n > 0 : n 6∈ S}. x is losing iff G(x) = 0. Sums of games. 
Player chooses a game and makes a move in it. Grundy number of a position is xor of grundy numbers of positions in summed games. 
Player chooses a non-empty subset of games (possibly, all) and makes moves in all of them. A position is losing iff each game is in a losing position.
Player chooses a proper subset of games (not empty and not all), and makes moves in all chosen ones. A position is losing iff grundy numbers of all games are equal.
Player must move in all games, and loses if can’t move in some game. A position is losing if any of the games is in a losing position.
Mis`ere Nim. A position with pile sizes a1, a2, . . . , an > 1, not all equal to 1, is losing iff a1 ⊕ a2 ⊕ · · · ⊕ an = 0 (like in normal nim.) A position with n piles of size 1 is losing iff n is odd.
