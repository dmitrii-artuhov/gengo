# Gengo
> Gengo. Pet programming language build for fun.


## Features (pre-release 0.1.0)
- Supports arithmetic operations in  console
- Correct order of binary and unary operations
- Print the structure of AST (Token representation)
- Auto int/float casting


## Snippets
Basic operations (`+`, `-`, `*`, `/`):

```shell
gengo > 1 + 2 * 4
(INT:1, PLUS, (INT:2, MULT, INT:4))
9
```
Unary operations:
```shell
gengo > ---1 + 100
((MINUS, (MINUS, (MINUS, INT:1))), PLUS, INT:100)
99
```
Correct order of operations:
```shell
gengo > (1 + 2) * 4
12
gengo > 1 + 2 * 4
9
gengo > 10 / 2 + 4
9
```

Types casting:
```asm
gengo > 2 * 4.5 - 1
((INT:2, MULT, FLOAT:4.5), MINUS, INT:1)
8.000000
```
