use std::io::{self, Write};
mod types;
mod find_moves;
mod piece_moves;

use types::Board;
#[no_mangle]
pub extern "C" fn describe_board(board: Board) {
    println!("{:?}",board.board.len());
    for piece in board.board {
        println!("{:?}",piece);
    }
    println!("It's white's turn:{}",board.white_turn);
    io::stdout().flush().unwrap();
}

// use std::ptr;
use std::os::raw::c_char;
use std::ffi::CString;
#[no_mangle]
pub extern "C" fn find_all_moves(board: Board) -> *mut c_char {
    let mut string = find_moves::find_moves(&board);
    // let mut string = Vec::with_capacity(20);
    // string.extend_from_slice(b"Hello, world!");
    // string.push(0);

    let ptr = string.as_mut_ptr() as *mut c_char;
    std::mem::forget(string);
    ptr
}

#[no_mangle]
pub extern "C" fn free_string(string: *mut c_char) {
    if string.is_null() { return; }
    unsafe {
        _ = CString::from_raw(string);
    }
}

#[no_mangle]
pub extern "C" fn test_rust() {
    println!("Hello from Rust!");
    io::stdout().flush().unwrap();

    use types::Piece;
    use types::Colour;
    use types::PieceType;
    let piece = Piece::WhiteRook;
    println!("{}", piece.is_colour(Colour::White));
    println!("{}", piece.is_piece(PieceType::Rook));
}
