# Gengo
> Gengo. Pet programming language build for fun.


## Language Grammar
Language Entity | Ruleset
------------ | -------------
expr    | (KEYWORD:TYPE)? IDENTIFIER EQ expr
&nbsp; 	| term ((PLUS\|MINUS) term)*
term    | factor ((MUL\|DIV) factor)*
factor  | INT\|FLOAT\|IDENTIFIER
&nbsp;	| (PLUS\|MINUS) factor
&nbsp;	| LPAREN expr RPAREN

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
gengo > int a = 10
10
gengo > a = a + b
Calls trace:
File <console input>
Run Time Error:'b' is not defined

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
