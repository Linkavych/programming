// Generate the nth fibonacci numbers
use std::io;

fn main() {
    println!("Enter a number.");

    let mut n = String::new();

    io::stdin()
        .read_line(&mut n)
        .expect("Failed to read line.");

    let n: u32 = n.trim().parse().expect("Please type a number.");

    println!("Number: {}", fibonacci(n));
}

fn fibonacci(n: u32) -> u32 {
    if n == 0 {
        return 0;
    } else if n == 1 {
        return 1;
    } else if n == 2 {
        return 1;
    } else {
        return fibonacci(n-1) + fibonacci(n-2);
    }
}
