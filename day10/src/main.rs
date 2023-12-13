use std::fs;
fn find_s(map: &mut Vec<Vec<char>>) -> (usize, usize) {
    for (i, row) in map.iter().enumerate() {
        for (j, item) in row.iter().enumerate() {
            if *item == 'S' {
                map[i][j] = '|';
                return (i, j);
            }
        }
    }
    (0, 0)
}
fn find_loop(
    map: &Vec<Vec<char>>,
    visited: &mut Vec<Vec<bool>>,
    path: &mut Vec<(usize, usize)>,
    loc: (usize, usize),
) -> bool {
    let (x, y) = loc;
    if map[x][y] == 'E' || map[x][y] == '.' {
        return false;
    }
    visited[x][y] = true;
    let go_to = get_direction(map[x][y]);

    for d in go_to {
        let next = (
            ((loc.0 as i32) + d.0) as usize,
            ((loc.1 as i32) + d.1) as usize,
        );
        if !visited[next.0][next.1] && find_loop(&map, visited, path, next) {
            path.push(next);
            return true;
        }
    }
    return true;
}

fn get_direction(pipe: char) -> Vec<(i32, i32)> {
    match pipe {
        '|' => vec![(-1, 0), (1, 0)],
        '-' => vec![(0, -1), (0, 1)],
        'L' => vec![(0, 1), (-1, 0)],
        'J' => vec![(0, -1), (-1, 0)],
        '7' => vec![(0, -1), (1, 0)],
        'F' => vec![(1, 0), (0, 1)],
        _ => panic!("get_direction impossible {}", pipe),
    }
}

fn part1(map: &mut Vec<Vec<char>>) -> Vec<(usize, usize)> {
    let mut path: Vec<(usize, usize)> = vec![];
    let mut visited: Vec<Vec<bool>> = vec![vec![false; map[0].len()]; map.len()];
    let start = find_s(map);

    path.push(start);
    find_loop(&map, &mut visited, &mut path, start);
    //for p in &path {
    //    println!("{:?}", p);
    //}
    return path;
}
fn part2(path: &Vec<(usize, usize)>) -> i32 {
    let mut res = 0;

    for i in 1..path.len(){
        let (leftx, lefty) = path[i - 1];
        let (rightx, righty) = path[i];
        res += leftx as i32 * righty as i32 - lefty as i32 * rightx as i32;
    }
    res
}
fn main() {
    let file_contents = fs::read_to_string("input").unwrap();
    let mut map: Vec<Vec<char>> = file_contents
        .lines()
        .map(|line| line.chars().collect())
        .collect();

    let mut path = part1(&mut map);
    let path_len = path.len();
    println!("res1 {}", path_len / 2);

    path.push(path[0].clone());
    let area = part2(&path);
    println!("res2 {}", (area.abs() - path_len as i32)/ 2 + 1);
}
