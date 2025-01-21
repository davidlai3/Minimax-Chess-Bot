#ifndef ENGINE_H
#define ENGINE_H 

#include <vector>
#include "Game.h"

class Engine{

    public:

        Engine( const int& depth, const Piece::Color engine_color, Game* current_game_ptr  );
        
        void update_game( const Game& latest_player_move );
        std::string best_engine_move();
        
    private: 

        int piece_value[7] = { 0, 1, 3, 3, 5, 9, 10000 };
        int depth;
        Piece::Color engine_color;
        Piece::Color player_color;
        Game game;
        std::vector<Game> move_history;

        int heuristic();
        std::pair<std::string, int> minimax( const int& curr_depth, const bool& maximizing_player );
        std::vector<std::string> all_legal_moves( ull moves, int src_row, int src_col );

};



#endif
