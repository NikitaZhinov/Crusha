int sum(int a, int b, int c) {
	return a + b + c;
}

int
diff
(int a,
			int b)
{
	return a
	-
b
;
}

int main() {
	int a = 1;
	int b = 2;

	int c = sum(a, b, 10);
	int d = diff(a, b);

	return c * d - 10;
}
