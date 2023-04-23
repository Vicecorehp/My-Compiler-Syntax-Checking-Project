# Compiler Syntax Checking Project
1. It's a git test, which means I'm totally a green hand.
2. It's just one of my assignment, and it may not satisfy you.
3. Ignore my bad code style...
4. Most of the work done in Visual Studio Code

# Usage
## 1. Linux or UNIX
Step 1: `git clone 'https://github.com/Vicecorehp/compiler_syntax.git'`<br>
Step 2: `cd compiler_syntax && make && ./target`<br>
Step 3: `<input your testing code>`<br>
*tip*: In the last Step, remember pressing `Ctrl+D` to finish inputting.

## 2. Windows with Visual Studio (VS)
Step 1: Create a No-file ConsoleApplication from the VS template<br>
Step 2: import the `*.h` and `*.cpp` files in VS<br>
Step 3: Click Run Button and a terminal Window will pop up<br>
Step 4: `<input your testing code>` <br>
*tip*: In the last Step, remember pressing `Ctrl+Z` to finish inputting.

## 3. Windows without Visual Studio (VS)
Step 1: Change directory to your current workspace in `cmd` or `powershell`<br>
Step 2: Write a batch script(`compiler.bat`): `g++ main.cpp Syntax.h Syntax.cpp Word_info.h -o target`<br>
Step 3: run your customed `compiler.bat` file by running `.\compiler.bat` and keep waiting while compiling<br>
Step 4: After Step 3, input `.\target` to begin Syntax Checking<br>
Step 5: `<input your testing code>` <br>
*tip*: In the last Step, remember pressing `Ctrl+Z` to finish inputting.

# Something Else
Some bugs still exist<br>
example: `double free or corruption (out)`<br>
if you have any idea to solve it, please tell me.

# Regulation
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
