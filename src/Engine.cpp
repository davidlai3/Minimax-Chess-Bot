#include "Engine.h"
#include <utility>
#include <climits>
// #define si std::pair<std::string, int>

Engine::Engine( const int& depth, const Piece::Color& engine_color, Game* current_game_ptr  ){
    this->depth = depth;

    if( engine_color == Piece::WHITE ){
        this->engine_color = engine_color;
        this->player_color = Piece::BLACK;
    }else{
        this->engine_color = engine_color;
        this->player_color = Piece::WHITE;
    }

    this->game = (*current_game_ptr);

}

int Engine::heuristic(){

    int score = 0;

    for( int row=0; row < 8; row ++ ){
        for( int col=0; col < 8; col ++ ){

            int piece_index = game.board[row][col]->get_type();


            if( game.board[row][col]->get_color() == engine_color ){
                score += piece_value[ piece_index ];
            }else{
                score -= piece_value[ piece_index ];
            }

        }
    }

    return score;

}

void Engine::update_game( const std::string& latest_player_move ){
    Game.player_move(latest_player_move);
}

std::string Engine::best_engine_move(){

    std::pair<std::string, int> result = minimax(depth, true);
    return result.first;

}

std::pair<std::string, int> Engine::minimax( const int& curr_depth, const bool& maximizing_player ){


    Game::State check_engine_win = game.check_endstate(player_color);
    Game::State check_player_win = game.check_endstate(engine_color);

    Piece::Color curr_player_color = (maximizing_player) ? engine_color : player_color; 


    // Check base cases
    if( check_engine_win == Game::CHECKMATE ){
        return INT_MAX; 
    }
    if( check_player_win == Game::CHECKMATE ){
        return INT_MIN;
    }
    if( check_engine_win == Game::STALEMATE ){
        return 0;
    }
    if( curr_depth == 0 ){
        return heuristic();
    }


    std::vector< std::string > legal_moves;
    for( int row=0; row < 8; row++ ){
        for( int col=0; col < 8; col++ ){

            if( game.board[row][col]->get_color() == curr_player_color ){

                ull piece_moves_ull = game.board[row][col]->get_legal_moves();
                std::vector<std::string> piece_moves_vec = all_legal_moves( piece_moves_ull, row, col );
                legal_moves.insert( legal_moves.end(), piece_moves_vec.begin(), piece_moves_vec.end() ); 

            }

        }
    }


    // if( maximizing_player ){
        
    //     for( const std::string& move : legal_moves ){

    //         Game.player_move(move);

    //         // Game.unmove_move(move)

    //     }



    // }else{



    // }




}