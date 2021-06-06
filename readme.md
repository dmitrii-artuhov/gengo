# Gengo
> Gengo. Pet programming language build for fun.


## Features (release 1.0.0)
- Console usage
- Reading from files
- Functions
- Arrays (with built-in functions: `size`, `push`, `pop`)
- Strings (with built-in functions: `length`)
- 64-bit Integers and Floats (`int`, `float`)
- General built-in functions: `print`
- Error messages

## Examples
Concatenate array of strings:
```sh
array arr = ["1", "2", "3", "4", "5"];

function concat(a: array) -> string {
	int sz = size(a);
	string res = "";

	loop(int i = 0; i < sz; i = i + 1) {
		res = res + a[i];
	};

	return res;
};

print(arr);
print(concat(arr));
```
```sh
[1, 2, 3, 4, 5]
12345
```

'Hello World!' program:
```sh
string str = "Hello World!";
print(str);
print(length(str));
```
```sh
Hello World!
12
```


Factorial of a number:
```sh
function factorial(a: int) -> int {
	if(a == 0) {
		return 1;	
	}
	otherwise {
		return a * factorial(a - 1); 
	};
};

print(factorial(10));
```
```sh
3628800
```






## Language Grammar
Language Entity | Ruleset
------------ | -------------
statements	 | expr NEWLINE (expr NEWLINE)*
statement	 | expr
&nbsp;		 | KEYWORD:return expr
expr		 | (KEYWORD:TYPE)? IDENTIFIER EQ expr
&nbsp; 		 | comp-expr
comp-expr	 | arith-expr ((AND\|OR\|EQEQ\|NE\|GT\|GTE\|LT\|LTE) arith-expr)*
arith-expr	 | term ((PLUS\|MINUS) term)*
term		 | factor ((MUL\|DIV) factor)*
factor		 | INT\|FLOAT\|STRING\|IDENTIFIER
&nbsp;		 | IDENTIFIER LPAREN (expr (COMMA expr)*)? RPAREN
&nbsp;		 | IDENTIFIER LSQUARE expr RSQUARE (LSQUARE expr RSQUARE)* (EQ expr)?
&nbsp;	     | (PLUS\|MINUS) factor
&nbsp;		 | LPAREN comp-expr RPAREN
&nbsp;		 | NOT comp-expr
&nbsp;		 | array-expr
&nbsp;		 | if-expr
&nbsp;		 | for-expr
&nbsp;		 | func-def
func-def	 | KEYWORD:function IDENTIFIER LPAREN (IDENTIFIER COLON KEYWORD:TYPE
&nbsp;		 | (COMMA IDENTIFIER COLON KEYWORD:TYPE)*)? RPAREN ARROW KEYWORD:TYPE
&nbsp;		 | LBRACE statements RBRACE
if-expr		 | KEYWORD:if LPAREN expr RPAREN LBRACE statements RBRACE
&nbsp;		 | (if-else-expr\|else-expr)?
if-else-expr | KEYWORD:elif LPAREN expr RPAREN LBRACE statements RBRACE
&nbsp;		 | (if-else-expr\|else-expr)?
else-expr	 | KEYWORD:otherwise LBRACE statements RBRACE
for-expr	 | KEYWORD:loop LPAREN (expr)? NEWLINE expr NEWLINE (expr)? RPAREN LBRACE statements RBRACE
array-expr	 | LSQUARE (expr (COMMA expr)*)? RSQUARE


## Features (pre-release 0.6.0)
- Strings
- Built-in Functions (`print`, `size`)

## Snippets (strings, built-in functions)
Strings:
```sh
gengo > string s = "Hello World!";
Hello World!
```

New built-in functions:
```sh
string s1 = "What does ";
string s2 = "'Gengo' ";
string s3 = "mean?";
```
```sh
gengo > print(s1 + s2 + s3);
What does 'Gengo' mean?
```

```sh
string name = "Dmitrii Art"
```
```sh
gengo > print(size(name));
11
```

0.5.0 (alpha) Pre-release functionality

## Features (pre-release 0.5.0)
- Functions
- Recursion support

## Snippets (functions)
Function declaration:
```sh
function add(a: int, b: int) -> int {
	return a + b;
};
```

```sh
function sum(a: int) -> int {
	if (a == 0) {
		return 0;
	}
	otherwise {
		return a + sum(a - 1);
	};
};
```

Function call:
```sh
gengo > add(10, 15 - 1);
24
```

```sh
gengo > sum(3);
6
```


## Features (pre-release 0.4.0)
- For loops (with correct scope management)

## Snippets (loops)
For-loop:

```sh
gengo > int a = 1;
1
gengo > loop(int i = 0; i < 10; i = i + 1){ a = a * 2; };
gengo > a;
gengo > 1024
```


## Features (pre-release 0.3.0)
- Comparison expressions
- Conditions (with correct scope management)

## Snippets (comparisons, conditions)
Simple comparisons:

```sh
gengo > 1 > 0;
1
gengo > 100 != 99 + 1 - 1;
1
```

Variables included
```sh
gengo > int a = 10; int b = 11;
11 - returns `b` (last statement) as a result of operation
gengo > a <= b;
1
```

Conditions (returns last statement result):
```sh
gengo > int a = 10;
10
gengo > if (a == 10) { a = 11; } elif (a == 11) { a = 12; } otherwise { a = 10; };
11
gengo > if (a == 10) { a = 11; } elif (a == 11) { a = 12; } otherwise { a = 10; };
12
gengo > if (a == 10) { a = 11; } elif (a == 11) { a = 12; } otherwise { a = 10; };
10
gengo > a;
10
```


## Features (pre-release 0.2.0)
- Initializing and using variables
- Error messages

## Snippets (variables)
Initialization and assigning (supported types - `int`, `float`):

```sh
gengo > int a = 10
10
gengo > a = a - 11
-1
```

```sh
gengo > float b = 10
10.000000
gengo > b / 3
3.333333
```

Initialization and assigning 'queue':
```sh
gengo > int t = int c = 10
10
gengo > t
10
gengo > c
10
```

```sh
gengo > int d = float b = 10
10 - returns `d` as a result of operation
gengo > d
10
gengo > b
10.000000
```

Errors printing:
```sh
gengo > int a = 10
10
gengo > a = a + b
Calls trace:
File <console input>
Run Time Error:'b' is not defined
```


## Features (pre-release 0.1.0)
- Supports arithmetic operations in  console
- Correct order of binary and unary operations
- Print the structure of AST (Token representation)
- Auto int/float casting


## Snippets (arithmetic operations)
Basic operations (`+`, `-`, `*`, `/`):

```sh
gengo > 1 + 2 * 4
(INT:1, PLUS, (INT:2, MULT, INT:4))
9
```
Unary operations:
```sh
gengo > ---1 + 100
((MINUS, (MINUS, (MINUS, INT:1))), PLUS, INT:100)
99
```
Correct order of operations:
```sh
gengo > (1 + 2) * 4
12
gengo > 1 + 2 * 4
9
gengo > 10 / 2 + 4
9
```

Types casting:
```sh
gengo > 2 * 4.5 - 1
((INT:2, MULT, FLOAT:4.5), MINUS, INT:1)
8.000000
```
