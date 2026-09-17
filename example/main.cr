func sum(let a: Int, let b: Int, let c: Int) -> Int {
	return a + b * c;
}

func diff(let a: Int, let b: Int) -> Int {
	return a - b;
}

func main() -> Int {
	let a: Int = new Int(1);
	let b: Int = 2.5;

	let c: Int = sum(a, b, 10);
	let d = diff(a, b);

	return c * d - 10;
}
