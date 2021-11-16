@.str.0 = constant [7 x i8] c"\0D\5C\22\0C\09\0A\00"
@.str.1 = constant [22 x i8] c"Number of arguments:\09\00"
@.str.2 = constant [2 x i8] c"\0A\00"
@.str.3 = constant [6 x i8] c"Arg (\00"
@.str.4 = constant [4 x i8] c"): \00"
@.str.5 = constant [2 x i8] c"\0A\00"
@.str.6 = constant [16 x i8] c"No arguments :(\00"
@.str.7 = constant [2 x i8] c"\0A\00"
@.str.int = constant [3 x i8] c"%d\00"
@.str.double = constant [6 x i8] c"%.16e\00"
@.str.string = constant [3 x i8] c"%s\00"
@.str.true = constant [5 x i8] c"true\00"
@.str.false = constant [6 x i8] c"false\00"

declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

%StringArray = type { i32, i8** }

@i = common global i32 0
define i32 @main(i32 %size, i8** %args){
	%1 = sub i32 %size, 1
	%2 = insertvalue %StringArray undef, i32 %1, 0
	%3 = getelementptr i8*, i8** %args, i32 1
	%4 = insertvalue %StringArray %2, i8** %3, 1
	call void @main.entry(%StringArray %4)
	ret i32 0
}
define void @main.entry(%StringArray %args){
	%.1 = getelementptr [7 x i8], [7 x i8]* @.str.0, i32 0, i32 0
	%format.2 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.2, i8* %.1)
	%a = alloca i32
	store i32 0, i32* %a
	%.3 = extractvalue %StringArray %args, 0
	store i32 %.3, i32* %a

	%.4 = getelementptr [22 x i8], [22 x i8]* @.str.1, i32 0, i32 0
	%format.5 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.5, i8* %.4)
	%.6 = load i32, i32* %a
	%format.7 = getelementptr [3 x i8], [3 x i8]* @.str.int , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.7, i32 %.6)
	%.8 = getelementptr [2 x i8], [2 x i8]* @.str.2, i32 0, i32 0
	%format.9 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.9, i8* %.8)
	%.10 = load i32, i32* %a
	%.11 = add i32 0, 0
	%.12 = icmp sgt i32 %.10, %.11
	br i1 %.12, label %if_true.12, label %if_false.12
if_true.12:
	br label %while_cond.13

while_true.13:
	%.14 = getelementptr [6 x i8], [6 x i8]* @.str.3, i32 0, i32 0
	%format.15 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.15, i8* %.14)
	%.16 = load i32, i32* @i
	%format.17 = getelementptr [3 x i8], [3 x i8]* @.str.int , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.17, i32 %.16)
	%.18 = getelementptr [4 x i8], [4 x i8]* @.str.4, i32 0, i32 0
	%format.19 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.19, i8* %.18)
	%.20 = load i32, i32* @i
	%.21 = add i32 0, 1
	%.22 = sub i32 %.20, %.21
	%.23 = extractvalue %StringArray %args, 1
	%.24 = getelementptr i8*, i8** %.23, i32 %.22
	%.25 = load i8*, i8** %.24
	%.26 = call i32 (i8*) @atoi( i8* %.25)
	%format.27 = getelementptr [3 x i8], [3 x i8]* @.str.int , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.27, i32 %.26)
	%.28 = getelementptr [2 x i8], [2 x i8]* @.str.5, i32 0, i32 0
	%format.29 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.29, i8* %.28)
	br label %while_cond.13

while_cond.13:
	%.30 = load i32, i32* %a
	%.31 = add i32 0, 1
	%.32 = add i32 %.30, %.31
	%.33 = load i32, i32* @i
	%.34 = add i32 0, 1
	%.35 = add i32 %.33, %.34
	store i32 %.35, i32* @i

	%.36 = icmp sgt i32 %.32, %.35
	br i1 %.36, label %while_true.13, label %while_end.13

while_end.13:
	br label %if_end.12
if_false.12:
	%.37 = getelementptr [16 x i8], [16 x i8]* @.str.6, i32 0, i32 0
	%format.38 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.38, i8* %.37)
	br label %if_end.12
if_end.12:
	%.39 = getelementptr [2 x i8], [2 x i8]* @.str.7, i32 0, i32 0
	%format.40 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.40, i8* %.39)
	ret void
}
