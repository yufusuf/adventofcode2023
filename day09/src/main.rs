use std::fs;

fn main() {
    let file_content = fs::read_to_string("sample").unwrap();
    let histories: Vec<Vec<i64>> = file_content
        .lines()
        .map(|line| {
            line.split_ascii_whitespace()
                .map(|num| num.parse::<i64>().unwrap())
                .collect()
        })
        .collect();
    let res: i64 = histories.iter().map(|arr| {
        let mut temp = arr.clone();
        let mut lasts: Vec<i64> = vec![];
        while temp.iter().any(|x| *x != 0) {
            lasts.push(*temp.last().unwrap());
            temp = temp
                .iter()
                .zip(temp.iter().skip(1))
                .map(|(first, second)| second - first)
                .collect();
        }
        lasts.iter().fold(0, |acc, x| acc + x)
    }).sum();
    println!("res1: {}", res);

    let res: i64 = histories.iter().map(|arr| {
        let mut temp = arr.clone();
        let mut lasts: Vec<i64> = vec![];
        while temp.iter().rev().any(|x| *x != 0) {
            lasts.push(*temp.first().unwrap());
            temp = temp
                .iter()
                .zip(temp.iter().skip(1))
                .map(|(first, second)| second - first)
                .collect();
        }
        // println!("{:?}", lasts);
        lasts.iter().rev().fold(0, |acc, x| x - acc)
    }).sum();
    println!("res2: {}", res);
}
