// Program to convert a temperature from farenheit to celsius
use std::io;

fn main() {
    println!("Enter a temperature in farenheit.");

    let mut temp = String::new();
    io::stdin()
        .read_line(&mut temp)
        .expect("Failed to read line.");

    let conv: f32 = temp.trim().parse().expect("Please type a number.");

    convert(conv);
}

fn convert(temp: f32) {
    let celsius: f32 = (temp - 32.0) * 0.556;

    println!("The temperature in Celsius is {celsius}.");
}
