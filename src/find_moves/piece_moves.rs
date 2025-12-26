use types::{Board, Colour};

/*use types::Colour;*/
fn can_move_to_square(board: &Board, index: usize, turn_colour: Colour) -> bool { // Doesn't look for checking, will filter out later
    let res = board.board.get(index);
    match res {
        Some(n) => { !n.is_colour(turn_colour) },
        None => { false }
    }
}

fn is_wrap_around(start: usize, end: usize, manhattan: usize) -> bool {
    let delta_x = (start as isize % 8 - end as isize % 8).abs() as usize;
    let delta_y = (start as isize / 8 - end as isize / 8).abs() as usize;
    // print!("dx:{} dy:{} mh: {} wrap: {}\n", delta_x, delta_y, manhattan, delta_x+delta_y != manhattan);
    // use std::io::{self, Write};
    // io::stdout().flush().unwrap();
    delta_x + delta_y != manhattan
}

fn get_algebraic(start: usize, end: usize, _promote_to: Option<u8>) -> [u8; 5] {
    let alphabet = "abcdefgh".as_bytes();
    let to_return: &mut [u8; 5] = &mut [b' '; 5];
    to_return[0] = alphabet[start % 8];
    to_return[1] = start as u8 / 8 + 1 + 48;
    to_return[2] = alphabet[end % 8];
    to_return[3] = end as u8 / 8 + 1 + 48;
    *to_return
}

/** Now the different piece moves start **/


pub fn pawn_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    // Check for moves the pawns can make
    if can_move_to_square(board, index - 8, turn_colour) {
        let alg = get_algebraic(index, index - 8, None);
        string.extend_from_slice(&alg);
        if can_move_to_square(board, index - 16, turn_colour) {
            let alg = get_algebraic(index, index - 16, None);
            string.extend_from_slice(&alg);
        }
    }
}

pub fn knight_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    let moves: [(isize, isize); 8] = [(1,2),(2,1),(-1,2),(2,-1),(1,-2),(-2,1),(-1,-2),(-2,-1)];
    for (dx, dy) in moves {
        let dest_index = (index as isize + dx + 8*dy)as usize;
        if can_move_to_square(board, dest_index , turn_colour) {
            if is_wrap_around(index, dest_index, 3) {
                continue;
            }
            let alg = get_algebraic(index, dest_index, None);
            string.extend_from_slice(&alg);
        }
    }
}
