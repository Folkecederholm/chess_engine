use types::{Board, Colour};

/*use types::Colour;*/
fn can_move_to_square(board: &Board, index: isize, turn_colour: Colour) -> bool { // Doesn't look for checking, will filter out later
    if index < 0 || index > 63 {
        return false;
    }
    let res = board.board.get(index as usize);
    match res {
        Some(n) => { !n.is_colour(turn_colour) },
        None => { false }
    }
}

fn pawn_can_move_to_square(board: &Board, index: isize, turn_colour: Colour, capture: bool) -> bool {
    if index < 0 || index > 63 {
        return false;
    }
    let res = board.board.get(index as usize);
    match res {
        Some(n) => {
            match capture {
                true => { !n.is_colour(turn_colour) && !n.is_colour(Colour::Empty) },
                false => { n.is_colour(Colour::Empty) }
            }
        },
        None => false
    }
}

fn does_not_stop(board: &Board, index: usize, _turn_colour: Colour) -> bool {
    let res = board.board.get(index);
    match res {
        Some(n) => { n.is_colour(Colour::Empty) },
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

fn slide_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>, pattern: (isize, isize)) {
    let mut k = index as isize % 8;
    let mut i = index as isize / 8;
    loop {
        k += pattern.0;
        i += pattern.1;
        // use std::io::{self, Write};
        // print!("x:{} y:{}\n", pattern.0, pattern.1);
        // print!("k:{} i:{}\n\n", k, i);
        // io::stdout().flush().unwrap();
        if k < 0 || i < 0 || k > 7 || i > 7 {
            break;
        }
        let new_index = (k + 8 * i) as usize;
        if can_move_to_square(board, new_index as isize, turn_colour) {
            let alg = get_algebraic(index, new_index, None);
            string.extend_from_slice(&alg);
            if !does_not_stop(board, new_index, turn_colour) {
                break;
            }
        } else {
            break;
        }
    }
}

/** Now the different piece moves start **/


pub fn pawn_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    let move_dist: isize = match turn_colour {
        Colour::Black => { -8 },
        Colour::White => { 8 },
        _ => { unreachable!() },
    };
    // Check for moves the pawns can make
    let dest_index = index as isize + move_dist as isize;
    //if can_move_to_square(board, dest_index, turn_colour) {
    if pawn_can_move_to_square(board, dest_index, turn_colour, false) {
        let alg = get_algebraic(index, dest_index as usize, None);
        string.extend_from_slice(&alg);

        /*
        // Prepare for if check
        let dest_index = index as isize + 2 * move_dist as isize;
        if can_move_to_square(board, dest_index, turn_colour) {
            let alg = get_algebraic(index, dest_index as usize, None);
            string.extend_from_slice(&alg);
        }
        */
    }
}

pub fn knight_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    let moves: [(isize, isize); 8] = [(1,2),(2,1),(-1,2),(2,-1),(1,-2),(-2,1),(-1,-2),(-2,-1)];
    for (dx, dy) in moves {
        let dest_index = (index as isize + dx + 8*dy)as usize;
        if can_move_to_square(board, dest_index as isize, turn_colour) {
            if is_wrap_around(index, dest_index, 3) {
                continue;
            }
            let alg = get_algebraic(index, dest_index, None);
            string.extend_from_slice(&alg);
        }
    }
}

pub fn rook_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    slide_move(board, index, turn_colour, string, (1,0));
    slide_move(board, index, turn_colour, string, (-1,0));
    slide_move(board, index, turn_colour, string, (0,1));
    slide_move(board, index, turn_colour, string, (0,-1));
}

pub fn bishop_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    slide_move(board, index, turn_colour, string, (1,1));
    slide_move(board, index, turn_colour, string, (1,-1));
    slide_move(board, index, turn_colour, string, (-1,1));
    slide_move(board, index, turn_colour, string, (-1,-1));
}

// I promise I will fix this with a more general function later, OK?
pub fn king_move(board: &Board, index: usize, turn_colour: Colour, string: &mut Vec<u8>) {
    let moves: [(isize, isize); 8] = [(1,0),(0,1),(-1,0),(0,-1),(1,-1),(-1,1),(1,1),(-1,-1)];
    for (dx, dy) in moves {
        let dest_index = (index as isize + dx + 8*dy)as usize;
        if can_move_to_square(board, dest_index as isize, turn_colour) {
            // Extremely janky; will fix
            if is_wrap_around(index, dest_index, 1) && is_wrap_around(index, dest_index, 2) {
                continue;
            }
            let alg = get_algebraic(index, dest_index, None);
            string.extend_from_slice(&alg);
        }
    }
}
