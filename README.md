# compiler_syntax
1. It's a git test
2. It's just one of my assignment
3. Ignore my bad code style...

# regulation
## A.1.2 High-level Definitions 
>Program(A) → ExtDefList(B)<br>
ExtDefList(B) → ExtDef(C) ExtDefList(B) | ɛ<br>
ExtDef(C) → Specifier(D) FunDec(E) Compst(F)

## A.1.3 Specifiers 
>Specifier(D) → TYPE

## A.1.4 Declarators 
>VarDec(G) → ID<br>
FunDec(E) → ID LP RP

## A.1.5 Statements 
>Compst(F) → LC DefList(H) StmtList(I) RC<br>
StmtList(I) → Stmt(J) StmtList(I) | ɛ<br>
Stmt(J) → Exp(K) SEMI | RETURN Exp(K) SEMI 

## A.1.6 Local Definitions 
>DefList(H) → Def(L) DefList(H) | ɛ<br>
Def(L) → Specifier(D) DecList(M) SEMI<br>
DecList(M) → Dec(N)<br>
Dec(N) → VarDec(G) ASSIGNOP Exp(K) 

## A.1.7 Expressions 
>Exp(K) → LP Exp(K) RP | NOT Exp(K) | INT | ID

# Simplified 
>1.2.1 A → B<br>
1.2.2 B → C B | ɛ<br>
1.2.3 C → D E F

>1.3.1 D → TYPE

>1.4.1 G → ID<br>
1.4.2 E → ID LP RP

>1.5.1 F → LC H I RC<br>
1.5.2 I → J I | ɛ<br>
1.5.3 J → K SEMI | RETURN K SEMI 

>1.6.1 H → L H | ɛ<br>
1.6.2 L → D M SEMI<br>
1.6.3 M → N<br>
1.6.4 N → G ASSIGNOP K 

>1.7.1 K → LP K RP | NOT K | INT | ID
