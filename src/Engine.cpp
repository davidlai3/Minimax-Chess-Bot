#include "../include/Engine.h"
#include <utility>
#include <climits>
#include <sstream>
#include <iostream>
// #define si std::pair<std::string, int>

Engine::Engine( const int& depth, const Piece::Color engine_color, Game* current_game_ptr  ){
    this->depth = depth;


    if( engine_color == Piece::WHITE ){
        this->engine_color = engine_color;
        this->player_color = Piece::BLACK;
    }else{
        this->engine_color = engine_color;
        this->player_color = Piece::WHITE;
    }

    this->game = (*current_game_ptr);
    move_history = { game };

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

void Engine::update_game( const Game& most_recent_game ){
    game = most_recent_game;
}

std::string Engine::best_engine_move(){
    std::pair<std::string, int> result = minimax(depth, true);
    return result.first;

}

std::vector<std::string> Engine::all_legal_moves( ull moves, int src_row, int src_col ){
    std::vector< std::string > result;

    for( int i = 0; i < 64; i++ ){
        if ( moves & 1<<i ){
            std::pair<int,int> coord = Utils::UNMSK( i );

            // concatenate via string stream
            std::stringstream move;
            move << (char) ('a' + src_col) <<  (char) ('8' - src_row) << (char)('a' + coord.second) << (char) ('8' - coord.first);
            result.push_back( move.str() );

        }

    }    
    return result;

}

std::pair<std::string, int> Engine::minimax( const int& curr_depth, const bool& maximizing_player ){


    Game::State check_engine_win = game.check_endstate(player_color);
    Game::State check_player_win = game.check_endstate(engine_color);

    Piece::Color curr_player_color = (maximizing_player) ? engine_color : player_color; 


    // Check base cases
    if( check_engine_win == Game::CHECKMATE ){
    std::cout << "Caught2" << std::endl;
        return {"", INT_MAX}; 
    }
    if( check_player_win == Game::CHECKMATE ){
    std::cout << "Caught3" << std::endl;
        return {"", INT_MIN};
    }
    if( check_engine_win == Game::STALEMATE ){
    std::cout << "Caught4" << std::endl;
        return {"", 0};
    }
    if( curr_depth == 0 ){
    std::cout << "Caught5" << std::endl;
        return {"", heuristic()};
    }


    std::vector< std::string > legal_moves;

    for( int row=0; row < 8; row++ ){
        for( int col=0; col < 8; col++ ){

            if( game.board[row][col]->get_color() == curr_player_color ){

                ull piece_moves_ull = game.board[row][col]->get_legal_moves( game.board );
                std::vector<std::string> piece_moves_vec = all_legal_moves( piece_moves_ull, row, col );
                legal_moves.insert( legal_moves.end(), piece_moves_vec.begin(), piece_moves_vec.end() ); 

            }

        }
    }

    std::pair<std::string, int> ret_val;


    if( maximizing_player ){

        ret_val.second = INT_MIN;
        
        for( const std::string& move : legal_moves ){

            // make the move
            game.player_move(move);

            // store in move history for future reference
            move_history.push_back( game );



            std::cout << "Maximizing Player" << std::endl;
            game.print_board();



            std::pair<std::string, int> result = minimax(curr_depth-1, !maximizing_player);
            if( result.second > ret_val.second ){
                ret_val.first = move;
                ret_val.second = result.second;
            }
            
            // unmove the move
            move_history.pop_back();
            game = move_history.back();

        }



    }else{

        ret_val.second = INT_MAX;

        for( const std::string& move : legal_moves ){
            

            // make move
            game.player_move( move );
            // store move history
            move_history.push_back(game);


            std::cout << "Minimizing Player" << std::endl;
            game.print_board();


            std::pair<std::string, int> result = minimax( curr_depth-1, !maximizing_player);
            if( result.second < ret_val.second ){
                ret_val.first = move;
                ret_val.second = result.second;
            }

            move_history.pop_back();
            game = move_history.back();

        }

    }


    return ret_val;



}
