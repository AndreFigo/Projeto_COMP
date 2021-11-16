@.str.0 = constant [2 x i8] c"\0A\00"
@.str.1 = constant [2 x i8] c"\0A\00"
@.str.2 = constant [2 x i8] c"\0A\00"
@.str.3 = constant [2 x i8] c"\0A\00"
@.str.4 = constant [2 x i8] c"\0A\00"
@.str.5 = constant [2 x i8] c"\0A\00"
@.str.6 = constant [2 x i8] c"\0A\00"
@.str.7 = constant [2 x i8] c"\0A\00"
@.str.int = constant [3 x i8] c"%d\00"
@.str.double = constant [6 x i8] c"%.16e\00"
@.str.string = constant [3 x i8] c"%s\00"
@.str.true = constant [5 x i8] c"true\00"
@.str.false = constant [6 x i8] c"false\00"

declare i32 @printf(i8*, ...)
declare i32 @atoi(i8*)

%StringArray = type { i32, i8** }

define i32 @main(i32 %size, i8** %args){
	%1 = sub i32 %size, 1
	%2 = insertvalue %StringArray undef, i32 %1, 0
	%3 = getelementptr i8*, i8** %args, i32 1
	%4 = insertvalue %StringArray %2, i8** %3, 1
	call void @main.entry(%StringArray %4)
	ret i32 0
}
define void @main.entry(%StringArray %uncommon_name){
	%d = alloca double
	store double 0.0, double* %d
	%.1 = call double @fun_double.()
	store double %.1, double* %d

	%.2 = load double, double* %d
	%format.3 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.3, double %.2)
	%.4 = getelementptr [2 x i8], [2 x i8]* @.str.0, i32 0, i32 0
	%format.5 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.5, i8* %.4)
	%.6 = call i32 @fun_int.()
	%.7 = sitofp i32 %.6 to double
	store double %.7, double* %d

	%.8 = load double, double* %d
	%format.9 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.9, double %.8)
	%.10 = getelementptr [2 x i8], [2 x i8]* @.str.1, i32 0, i32 0
	%format.11 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.11, i8* %.10)
	%.12 = call double @fun_double_from_int.()
	store double %.12, double* %d

	%.13 = load double, double* %d
	%format.14 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.14, double %.13)
	%.15 = getelementptr [2 x i8], [2 x i8]* @.str.2, i32 0, i32 0
	%format.16 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.16, i8* %.15)
	%.17 = call double @fun_double_from_int_fun.()
	store double %.17, double* %d

	%.18 = load double, double* %d
	%format.19 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.19, double %.18)
	%.20 = getelementptr [2 x i8], [2 x i8]* @.str.3, i32 0, i32 0
	%format.21 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.21, i8* %.20)
	%.22 = call double @fun_double_from_int_var.()
	store double %.22, double* %d

	%.23 = load double, double* %d
	%format.24 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.24, double %.23)
	%.25 = getelementptr [2 x i8], [2 x i8]* @.str.4, i32 0, i32 0
	%format.26 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.26, i8* %.25)
	%.27 = call double @fun_double_from_args.s(%StringArray %uncommon_name)
	store double %.27, double* %d

	%.28 = load double, double* %d
	%format.29 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.29, double %.28)
	%.30 = getelementptr [2 x i8], [2 x i8]* @.str.5, i32 0, i32 0
	%format.31 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.31, i8* %.30)
	%.32 = call double @fun_double_from_unary_plus.s(%StringArray %uncommon_name)
	store double %.32, double* %d

	%.33 = load double, double* %d
	%format.34 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.34, double %.33)
	%.35 = getelementptr [2 x i8], [2 x i8]* @.str.6, i32 0, i32 0
	%format.36 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.36, i8* %.35)
	%.37 = fadd double 0.0, 1.3
	%format.38 = getelementptr [6 x i8], [6 x i8]* @.str.double , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.38, double %.37)
	%.39 = getelementptr [2 x i8], [2 x i8]* @.str.7, i32 0, i32 0
	%format.40 = getelementptr [3 x i8], [3 x i8]* @.str.string , i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %format.40, i8* %.39)
	ret void
}
define double @fun_double.(){
	%.41 = fadd double 0.0, 1.1
	ret double %.41
	ret double 0.0
}
define i32 @fun_int.(){
	%.42 = add i32 0, 1
	ret i32 %.42
	ret i32 0
}
define double @fun_double_from_int.(){
	%.43 = add i32 0, 2
	%.44 = sitofp i32 %.43 to double
	ret double %.44
	ret double 0.0
}
define double @fun_double_from_int_fun.(){
	%.45 = call i32 @fun_int.()
	%.46 = sitofp i32 %.45 to double
	ret double %.46
	ret double 0.0
}
define double @fun_double_from_int_var.(){
	%d = alloca double
	store double 0.0, double* %d
	%.47 = add i32 0, 0
	%.48 = sitofp i32 %.47 to double
	store double %.48, double* %d

	%.49 = load double, double* %d
	%.50 = call i32 @fun_int.()
	%.51 = sitofp i32 %.50 to double
	%.52 = fadd double %.49, %.51
	%.53 = call double @fun_double.()
	%.54 = fadd double %.52, %.53
	ret double %.54
	ret double 0.0
}
define double @fun_double_from_args.s(%StringArray %str_arr){
	%.55 = extractvalue %StringArray %str_arr, 0
	%.56 = sitofp i32 %.55 to double
	ret double %.56
	ret double 0.0
}
define double @fun_double_from_unary_plus.s(%StringArray %str_arr){
	%.57 = add i32 0, 1
	%.58 = sitofp i32 %.57 to double
	ret double %.58
	ret double 0.0
}
