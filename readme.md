# Gengo
> Gengo. Pet programming language build for fun.


## Language Grammar
Language Entity | Ruleset
------------ | -------------
statements	 | expr NEWLINE (expr NEWLINE)*
expr		 | (KEYWORD:TYPE)? IDENTIFIER EQ expr
&nbsp; 		 | comp-expr
comp-expr	 | arith-expr ((AND\|OR\|EQEQ\|NE\|GT\|GTE\|LT\|LTE) arith-expr)*
arith-expr	 | term ((PLUS\|MINUS) term)*
term		 | factor ((MUL\|DIV) factor)*
factor		 | INT\|FLOAT\|IDENTIFIER
&nbsp;		 | (PLUS\|MINUS) factor
&nbsp;		 | LPAREN comp-expr RPAREN
&nbsp;		 | NOT comp-expr
&nbsp;		 | if-expr
&nbsp;		 | for-expr
if-expr		 | KEYWORD:if LPAREN expr RPAREN LBRACE statements RBRACE
&nbsp;		 | (if-else-expr\|else-expr)?
if-else-expr | KEYWORD:elif LPAREN expr RPAREN LBRACE statements RBRACE
&nbsp;		 | (if-else-expr\|else-expr)?
else-expr	 | KEYWORD:otherwise LBRACE statements RBRACE
for-expr	 | KEYWORD:loop LPAREN (expr)? NEWLINE expr NEWLINE (expr)? RPAREN LBRACE statements RBRACE

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
