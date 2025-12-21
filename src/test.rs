use std::io::{self, Write};

#[no_mangle]
pub extern "C" fn greet() {
    print!("Hello, world!");
    io::stdout().flush().unwrap();
}
