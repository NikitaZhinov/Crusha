func sum(int a, int b, int c) -> int {
	return a + b + c;
}

func
diff
(int a,
			int b)
->
int
{
	return a
	-
b
;
}

func main() -> int {
	int a = 1;
	int b = 2;

	int c = sum(a, b, 10);
	int d = diff(a, b);

	return c * d - 10;
}
