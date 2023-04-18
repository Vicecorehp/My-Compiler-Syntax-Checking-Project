# compiler_syntax
1. It's a git test
2. It's just one of my assignment
3. Ignore my bad code style...

# regulation
## A.1.2 High-level Definitions 
>Program(A) → ExtDefList(B)
<br>
ExtDefList(B) → ExtDef(C) ExtDefList(B) | ɛ
<br>
ExtDef(C) → Specifier(D) FunDec(E) Compst(F)

## A.1.3 Specifiers 
>Specifier(D) → TYPE

## A.1.4 Declarators 
>VarDec(G) → ID
<br>
FunDec(E) → ID LP RP

## A.1.5 Statements 
>Compst(F) → LC DefList(H) StmtList(I) RC 
<br>
StmtList(I) → Stmt(J) StmtList(I) | ɛ
<br>
Stmt(J) → Exp(K) SEMI | RETURN Exp(K) SEMI 

## A.1.6 Local Definitions 
>DefList(H) → Def(L) DefList(H) | ɛ
<br>
Def(L) → Specifier(D) DecList(M) SEMI
<br>
DecList(M) → Dec(N)
<br>
Dec(N) → VarDec(G) ASSIGNOP Exp(K) 

## A.1.7 Expressions 
>Exp(K) → LP Exp(K) RP | NOT Exp(K) | INT | ID
