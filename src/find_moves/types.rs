#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, PartialOrd)]
pub enum Piece {
    EmptySquare = 0,
    WhiteKing = 1,
    WhiteQueen = 2,
    WhiteRook = 3,
    WhiteBishop = 4,
    WhiteKnight = 5,
    WhitePawn = 6,
    BlackKing = 7,
    BlackQueen = 8,
    BlackRook = 9,
    BlackBishop = 10,
    BlackKnight = 11,
    BlackPawn = 12,
}

#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum PieceType {
    NoPiece = 0,
    King = 1,
    Queen = 2,
    Rook= 3,
    Bishop = 4,
    Knight = 5,
    Pawn = 6,
}


#[repr(C)]
#[derive(Debug, Clone, Copy)]
pub struct Board {
    pub board: [Piece; 64],
    pub white_turn: bool,
}

#[repr(u8)]
#[derive(Debug, Clone, Copy)]
pub enum Colour {
    White = 1,
    Black = 0,
    Empty = 255,
}


/*IDEA: TYPE FOR PIECE COLOURS
pub struct Colour {
    pub colour: bool
}
*/

impl Piece {
    pub fn is_colour(&self, colour: Colour) -> bool {
        match colour {
            Colour::Empty => {
                *self == Piece::EmptySquare 
            },
            Colour::White => {
                Piece::WhiteKing <= *self  && *self <= Piece::WhitePawn
            },
            Colour::Black => {
                Piece::BlackKing <= *self && *self <= Piece::BlackPawn
            }
        }
    }

    pub fn is_piece(&self, piece_type: PieceType) -> bool {
        if piece_type == PieceType::NoPiece {
            return *self == Piece::EmptySquare;
        };
        // Now we know there is a piece
        match &self.is_colour(Colour::White) {
            true => {
                return *self as u8 == piece_type as u8
            },
            false => {
                return *self as u8 == (piece_type as u8) + 6
            }
        }
    }

    pub fn get_piece(&self) -> PieceType {
        use self::PieceType::*;
        use self::Piece::*;
        match &self {
            EmptySquare => { NoPiece },
            WhiteKing | BlackKing => { King },
            WhiteQueen | BlackQueen => { Queen },
            WhiteRook | BlackRook => { Rook },
            WhiteBishop | BlackBishop => { Bishop },
            WhiteKnight | BlackKnight => { Knight },
            WhitePawn | BlackPawn => { Pawn },
        }
    }
}

impl Board {
    pub fn current_colour(&self) -> Colour {
        match &self.white_turn {
            true => { Colour::White },
            false => { Colour::Black },
        }
    }
}

