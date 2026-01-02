use Board;

use types::Colour;
fn try_move_piece(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    use piece_moves::*;
    use types::PieceType::*;

    let piece = board.board[index];
    // if piece.is_colour(turn_colour) {
    //     if piece.is_piece(Pawn) {
    //         pawn_move(board, index, turn_colour, string);
    //     }
    // }
    if piece.is_colour(turn_colour) {
        match piece.get_piece() {
            Pawn => { pawn_move(board, index, turn_colour, string); },
            Knight => { knight_move(board, index, turn_colour, string); },
            Rook => { rook_move(board, index, turn_colour, string); },
            Bishop => { bishop_move(board, index, turn_colour, string); },
            Queen => { rook_move(board, index, turn_colour, string); bishop_move(board, index, turn_colour, string); },
            King => { king_move(board, index, turn_colour, string); },
            _ => { },
        }
    }
}



pub fn find_moves(board: &Board) -> Vec<u8> {
    use types::Colour;
    
    let mut string = Vec::with_capacity(20);

    let turn_colour: Colour = board.current_colour().clone();
    // Pawn moves
    for index in 0..board.board.len() {
        try_move_piece(board, index, turn_colour, &mut string);
    }
    // string.extend_from_slice(b"Hi, world!");
    string.push(0);
    string
}
