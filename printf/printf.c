#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

typedef struct s_flags {

    bool zero;
    bool negitive;
    bool positive;
    bool space;
    bool hashtag;
    bool blank;
    
}s_flags;

typedef struct s_length {

    int fieldwidth;
    int precision;

}s_length;

typedef struct s_vector_number {
    int *p_integer;
    unsigned int *p_unsigned_integer;
    int number_size;
    int array_size;
}s_vector_number;


int print_char(char c);
int print_int_array(int *number_array, int array_size);
int print_integers(long long int number);
int convert_char_to_num(const char *string);
void if_negative_make_zero(s_length *length, int number_size);
int finding_number_double(double number);
bool checking_all_zeros(double a_double, int last_digit, int this_number, int starting_point);
int my_printf(const char *string, ...);
void flag_checker(const char *string, char conversion, s_flags *flags);
int perameters(const char *string, int *characters_printed, va_list *vector_list);
int percent_d(s_flags *flags, s_length *length, int integer);
int field_precision_integer (s_length *length, s_flags *flags, s_vector_number *a_integer, char type);
int precision_integer(s_length *length, s_vector_number *a_integer, char type);
int field_integer(s_length *length, s_flags *flags, s_vector_number *a_integer, char type);
int percent_0_u(char type, s_flags *flags, s_length *length, unsigned int integer);
void precent_o(unsigned int integer, s_vector_number *a_integer, s_flags *flags);
int percent_x_X(char type, s_flags *flags, s_length *length, unsigned int integer);
int percent_c(char c);
int percent_s(char *string);
int percent_p(void *pointer);
int permament_rounding(double a_float, int last_digit, char check_percent);
int print_float(double a_float, char check_percent, int precision, int place_decimal, int last_digit);
int percent_f(char check_percent, s_length *length, s_flags *flags, double number);
int percent_e(char check_percent, s_length *length, s_flags *flags, double a_float);
int percent_g(char check_percent, s_length *length, s_flags *flags, double a_float);
//int test_double();
//double rounding(double number);


//i threw all my general funcitons that im using on top of the stack because these are functions that are going to 
//convert integers/floats/char to other data types. along with print_variables that will be used to print data types 
//too.
int print_char(char c) {
    return write(1,&c,1);
}

//this need a integer to be sent to work.
int print_integers(long long int number) {
    int size = 0;
    int temp = number;
    //printf("test %d\n", temp);
    if(number == 0) {
        //printf("hi");
        print_char('0');
        return 1;
    }

    for(temp; temp != 0; temp = temp/10) {
        size++;
    }

    int *array = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++) {
        //printf("%d\n", number % 10);
        if(number % 10 >= 0) {
            array[i] = (number % 10) + 48;
        } else {
            
            array[i] = (-number % 10) + 48;
        }
        
        //printf("%d %d\n", (number % 10) + 48, size);
        number = number/10;
    }
    for(int i = size - 1; i >= 0; i--) {
        print_char(array[i]);
    }

    free(array);
    return size;
}

int print_int_array(int *number_array, int array_size) {
    //printf("%d %d\n", array_size, number_array[0]);
    for(int i = 0; i < array_size; i++){
        //printf("hi");
        print_char(number_array[i]);
    }

    return array_size;
}

int convert_char_to_num(const char *string) {
    int number = 0;
    for(int i = 0; string[i] >= '0' && string[i] <= '9'; i++) {
        //printf("%c", string[i]);

        if(i == 0) {
            number = string[i] - '0';
        }else {
            number = number * 10;
            number = number + string[i] - '0';
        }
    }
    //printf("fieldwidth == %d\n", number);
    return number;
}

void if_negative_make_zero(s_length *length, int number_size) {
    if(length->fieldwidth - number_size < 0) {
        length->fieldwidth = 0;
    }else{
        length->fieldwidth = length->fieldwidth - number_size;
    }
    if(length->precision - number_size < 0){
            length->precision = 0;
    }else{
        length->precision = length->precision - number_size;
    }
}

int finding_number_double(double number) {
    //printf("the number that came back == %f", number);
    for(int i = 0; i < 10; i++) {
        //printf("number - i == %f\n", number - i);
        if(number - i == 0) {
            //printf("number returned == %d\n", i);
            return i;
        }
    }

    return 0;
}

bool checking_all_zeros(double a_float, int last_digit, int this_number, int starting_point){
    
    //printf("\n%f %d %d %d\n", a_double, last_digit, this_number, starting_point);     
    
    for(int k = starting_point; k <= last_digit; k++) {

        //printf("this number == %d\n", this_number);
        if(this_number > 0) {
            return false;
        }
        a_float = a_float * 10;
        this_number = (int)a_float;
    }

    return true;
}

int main() {
    int check = 0;
    void *pointer = &check;
    printf("%g\n", 8934.923456);
    //test_double();
    //printf("%lld\n", pointer);
    //printf("%#llX\n", pointer);
    check = printf("one == %.4a two == %.4a three == %.4a four == %.4a five == %.4a six == %.4a\n", -2.0, 4.0, 6.0, 8.0, 10.0, 12.0);
    printf("%.0d\n", check);
    check = my_printf("abc%dadcbe%#+ 4.5dabdc%-4dabcd%1.3da%-1.1daoctal%5.7uahexical%-#9Xabc%c12a%s123abcab%gomg finally == %a\n", 0, -98, 987, 87, 876, 12345, 11111, 'a', "hi", 8934.923456, 100.0);
    printf("%.0d\n", check);
    check = my_printf("final results for pointer = %p\n", pointer);
    printf("%lld\n", sizeof(int64_t));
    return 0;
}
//thing i need to work on lets get %d with flags working here hoping it works with other parameters later.
int my_printf(const char *string, ...) {

    va_list vector_list;
    int characters_printed  = 0;
    va_start(vector_list, string);

    for(int i = 0; string[i] != '\0'; i++) {
        if(string[i] == '%') {
        i = i + perameters(&string[i], &characters_printed, &vector_list);
            
        } else {
            characters_printed = print_char(string[i]) + characters_printed;
            //printf("chars read == %d\n", characters_printed);
        }
    }

    va_end(vector_list);
    
    return characters_printed;
}

//i made this function because it seemed important to identify all flags being uses cus how flags behave with each 
//other some cancel.
//or change order things run for example with precision and fieldlength precision only prints out zeros for its length 
//and not fieldlength
// length also negiative effects order of what gets printed out first fieldlength or precisionlength.
void flag_checker(const char *string, char conversion, s_flags *flags) {//all this function does it check to see if all 
                                                                        //characters to activate flags are there.
                                                                        
    //printf("end of conversion letter == %c, start of string == %c\n", conversion, string[0]);
    for(int i = 0; string[i] != conversion; i++) {
        //printf("string[i] == %c\n", string[i]);
        if(string[i] == '#') {
            flags->hashtag = true;
        }
        if(string[i] == '0') {
            flags->zero = true;
        }
        if(string[i] == '-') {
            flags->negitive = true;
        }
        if(string[i] == '+') {
            flags->positive = true;
        }
        if(string[i] == ' ') {
            flags->space = true;
        }
        if(string[i] == '.' && string[i + 1] == '0') {
            flags->blank = true;
        }
    }
    //printf("neg == %d hashtag == %d pos == %d space == %d zero == %d\n", flags->negitive, flags->hashtag, 
    //flags->positive, flags->space, flags->zero);
}

int perameters(const char *string,int *characters_printed, va_list *vector_list) {
    //these flags are for flags that printf looks for. not all are used for all functions soo even if something like 
    //hashtag is true if the function doesnt look for hashtag nothing will happen.
    s_flags flags = {flags.zero = false,
                     flags.hashtag = false,
                     flags.negitive = false,
                     flags.positive = false,
                     flags.space = false,
                     flags.blank = false
                    };
    //length at this time only uses fieldwidth and precision it may be used to changed conversion type say instead of 
    //passing int you can pass long long int with bool hh check.
    s_length length = {length.fieldwidth = 0,
                       length.precision = 0
                      };
    
    int i = 1;
    
    for(i; string[i] != '\0'; i++) {// this for loop started just checking the letter to confirm what conversion we 
    //doing but i use it atm to find end of conversion with the start being giving for string[0] also using it to 
    //fill out values for length struct.
        if((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z')) {
            break;
        }
        if(string[i] == '%') {
            break;
        }
        if(string[i] >= '1' && string[i] <= '9' && length.fieldwidth == 0) {
            
            length.fieldwidth = convert_char_to_num(&string[i]);
        }
        if(string[i] == '.' && string[i] && string[i + 1] >= '0' && string[i + 1] <= '9' && length.precision == 0) {

            length.precision = convert_char_to_num(&string[i + 1]);
        }
    }

    //printf("fieldwidth == %d precision == %d\n", fieldwidth, precision);

    flag_checker(string, string[i], &flags);
    //all these if statements are to the conversion function we going be calling.
    if(string[i] == 'd' || string[i] == 'i') {
        //printf("test\n");
        *characters_printed = *characters_printed + percent_d(&flags, &length, va_arg(*vector_list, int));
        return i;
    }
    if(string[i] == 'o' || string[i] == 'u') {
        *characters_printed = *characters_printed + percent_0_u(string[i], &flags, &length, va_arg(*vector_list, unsigned int));
        return i;
    }
    if(string[i] == 'x' || string[i] == 'X') {
        *characters_printed = *characters_printed + percent_x_X(string[i], &flags, &length, va_arg(*vector_list, unsigned int));
        return i;
    }
    if(string[i] == 'c') {
        *characters_printed = *characters_printed + percent_c(va_arg(*vector_list, int));
        return i;
    }
    if(string[i] == 's') {
        *characters_printed = *characters_printed + percent_s(va_arg(*vector_list, char*));
    }
    if(string[i] == 'p') {
        *characters_printed = *characters_printed + percent_p(va_arg(*vector_list, void*));
    }
    if(string[i] == '%') {
        print_char('%');
        *characters_printed = *characters_printed + 1;
    }
    if(string[i] == 'f') {
        *characters_printed = *characters_printed + percent_f(string[i] , &length, &flags, va_arg(*vector_list, double));
    }
    if(string[i] == 'e' || string[i] == 'E') {
        *characters_printed = *characters_printed + percent_e(string[i], &length, &flags, va_arg(*vector_list, double));
    }
    if(string[i] == 'g' || string[i] == 'G') {
        *characters_printed = *characters_printed + percent_g(string[i], &length, &flags, va_arg(*vector_list, double));
    }

    return i;
}

//this is %d.
int percent_d(s_flags *flags, s_length *length, int integer) {
    int return_size = 0;
    int power_ten = 1;
    s_vector_number a_integer  = {a_integer.p_integer = &integer,
                                  a_integer.p_unsigned_integer = NULL,
                                  a_integer.array_size = 0,
                                  a_integer.number_size = 0
    };
    //printf("%d\n", number_size);
    if(flags->positive || flags->space || integer < 0) {
        if(integer < 0) {
            putchar('-');
            length->fieldwidth--;
            return_size++;
        }else if(flags->positive == true) {
            print_char('+');
            length->fieldwidth--;
            return_size++;
        }else if(flags->space == true) {
            print_char(' ');
            length->fieldwidth--;
            return_size++;
        }
    }

    if(flags->blank == true && integer == 0) {
        //printf("hi");
        return return_size;
    }

    for(a_integer.number_size = 0; integer /power_ten != 0; a_integer.number_size++){
        power_ten = power_ten * 10;
    }

    if(length->fieldwidth > 0 && length->precision > 0){
        
        return_size = return_size + field_precision_integer(length, flags, &a_integer, '\0');

    }else if(length->precision > 0) {
    
        return_size = return_size + precision_integer(length, &a_integer, '\0');

    }else if(length->fieldwidth > 0){

        return_size = return_size + field_integer(length, flags, &a_integer, '\0');

    }else {
        return_size = return_size + print_integers(*a_integer.p_integer);
    }
    //print_integers(integer);
    //printf("return number == %d\n", return_size);
    return return_size;
}

//idk how to type field&precision for percent d soo this is the name i gave it. i need to ajust all three of these functions to work with multi data types. also note cus of pointer data type limit i either need rewrite how parameters are pass or work around it.
int field_precision_integer (s_length *length, s_flags *flags, s_vector_number *a_integer, char type) {
    int return_size = 0;

    if(flags->negitive == true) {
        //i might make this a seperate function later for now ill keep it in here.
        for(length->precision; length->precision >= 0; length->precision--, length->fieldwidth--) {
            //printf("precision == %d number size == %d\n", length->precision, number_size);
            if(length->precision > a_integer->number_size && length->precision > a_integer->array_size){
                print_char('0');
                return_size++;
            }else if(a_integer->array_size == 0){
                
                if(type == 'u'){
                    return_size  = print_integers(*a_integer->p_unsigned_integer) + return_size;
                    if_negative_make_zero(length, a_integer->number_size);
                }else{
                    return_size  = print_integers(*a_integer->p_integer) + return_size;
                    if_negative_make_zero(length, a_integer->number_size);
                }

                break;

            }else{
                return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
                if_negative_make_zero(length , a_integer->array_size);
                break;
            }
        }

        for(length->fieldwidth; length->fieldwidth > 0; length->fieldwidth--) {
            print_char(' ');
            return_size++;
        }
    }else{
        //printf("hello\n");
        for(length->fieldwidth; length->fieldwidth > length->precision && length->fieldwidth > a_integer->number_size && length->fieldwidth > a_integer->array_size; length->fieldwidth--){
            print_char(' ');
            return_size++;
        }

        for(length->precision; length->precision >= 0 ; length->fieldwidth--, length->precision--) {
            //printf("precision == %d number size == %d\n", length->precision, a_integer->number_size);
            if(length->precision > a_integer->number_size && length->fieldwidth > a_integer->array_size) {
                print_char('0');
                return_size++;
            }else if(a_integer->array_size == 0){
                
                if(type == 'u'){
                    return_size  = print_integers(*a_integer->p_unsigned_integer) + return_size;
                    if_negative_make_zero(length, a_integer->number_size);
                }else{
                    return_size  = print_integers(*a_integer->p_integer) + return_size;
                    if_negative_make_zero(length, a_integer->number_size);
                }

                break;
                
            }else {
                return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
                if_negative_make_zero(length , a_integer->array_size);
                break;
            }
        }
    }

    return return_size;
}

int precision_integer(s_length *length, s_vector_number *a_integer, char type) {
    int return_size = 0;
    
    for(length->precision;length->precision > a_integer->number_size && length->fieldwidth > a_integer->array_size; length->precision--) {
        print_char('0');
        return_size++;
    }
    if(a_integer->array_size == 0){
    
        if(type == 'u') {
            return_size = return_size + print_integers(*a_integer->p_unsigned_integer);
        }else{
            return_size = return_size + print_integers(*a_integer->p_integer);
        }

    }else{
        return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
    }

    return return_size;
}

int field_integer(s_length *length, s_flags *flags, s_vector_number *a_integer, char type) {
    int return_size = 0;
    
    if(flags->negitive == true) {//number size just find how many digits it takes to make the  number;
        if(a_integer->array_size == 0){
        
        if(type == 'u') {
            return_size = return_size + print_integers(*a_integer->p_unsigned_integer);
        }else{
            return_size = return_size + print_integers(*a_integer->p_integer);
        }
        
        }else{
            return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
        }

        if(a_integer->array_size > a_integer->number_size) {
            length->fieldwidth = length->fieldwidth - a_integer->array_size;
        }else{
            length->fieldwidth = length->fieldwidth - a_integer->number_size;
        }
        

        for(length->fieldwidth; length->fieldwidth > 0; length->fieldwidth--) {

            print_char(' ');
            return_size++;

        }
    }else{
        for(length->fieldwidth; length->fieldwidth > a_integer->number_size && length->fieldwidth > a_integer->array_size; length->fieldwidth--) {
            if(flags->zero == true) {
                print_char('0');
                return_size++;
            }else{
                print_char(' ');
                return_size++;
            }
        }
        if(a_integer->array_size == 0){
        
            return_size = return_size + print_integers(*a_integer->p_integer);
        
        }else{
            return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
        }
    }

    return return_size;
}
//note when using pointers data type has to be exact or it returns error.
int percent_0_u(char type, s_flags *flags, s_length *length, unsigned int integer){
    int return_size = 0;
    //int power_ten = 1;
    s_vector_number a_integer  = {a_integer.p_integer = NULL,
                                  a_integer.p_unsigned_integer = NULL,
                                  a_integer.array_size = 0,
                                  a_integer.number_size = 0
    };
    //printf("hi");

    if(flags->blank == true && integer == 0) {
        //printf("hi");
        return return_size;
    }

    if(type == 'o') {
       precent_o(integer, &a_integer, flags);
    }else if(type == 'u'){
        unsigned int temp = integer;
        a_integer.p_unsigned_integer = &integer;
        for(a_integer.number_size = 0; temp > 0; a_integer.number_size++){
            temp = temp / 10;
        }
    }

    //printf("%d %d\n", *a_integer.p_integer, a_integer.number_size);
    if(length->fieldwidth > 0 && length->precision > 0){
        
        return_size = return_size + field_precision_integer(length, flags, &a_integer, type);

    }else if(length->precision > 0) {
    
        return_size = return_size + precision_integer(length, &a_integer, type);

    }else if(length->fieldwidth > 0){

        return_size = return_size + field_integer(length, flags, &a_integer, type);

    }else {
        if(type == 'o') {
            return_size = return_size + print_int_array(a_integer.p_integer, a_integer.array_size);
        }else if(type == 'u') {
            return_size = return_size + print_integers(integer);
        }
    }
    if(type == 'o') {
        free(a_integer.p_integer);
    }
    return return_size;
}

void precent_o(unsigned int integer, s_vector_number *a_integer, s_flags *flags) {

    unsigned temp = integer;
    //unsigned int converted_to_octal = 0;
    unsigned int octal = 8;

    for(a_integer->array_size; temp > 0; a_integer->array_size++) {
        temp = temp / 8;
    }

    if(flags->hashtag == true) {
        a_integer->array_size++;
        //a_integer->number_size++;
    }

    int *array = malloc(sizeof(int) * a_integer->array_size);

    for(int i = a_integer->array_size - 1; integer > 0; i--) {
        if(flags->hashtag == true) {
            array[0] = '0';
            flags->hashtag = false;
        }
        array[i] = (integer % octal) + '0';
        //printf("number saved == %d", *a_integer->p_integer % 8);
        integer = integer / octal;
        //74 - 8 give remainder 2;
        //temp = 9 % 8 = 1
        //74/8 = 9%8 = 1
        //1/8
    }
    a_integer->p_integer = array;
    // for(int i = 0; i < a_integer->array_size; i++){
    //     print_char(a_integer->p_integer[i]);
    // }
    // free(array);
}

int percent_x_X(char type, s_flags *flags, s_length *length, unsigned int integer) {
    int hex = 16;
    unsigned int temp = integer;
    int *hex_print;
    int return_size = 0;

    s_vector_number a_integer  = {a_integer.p_integer = NULL,
                                  a_integer.p_unsigned_integer = NULL,
                                  a_integer.array_size = 0,
                                  a_integer.number_size = 0
    };

    for(a_integer.array_size; temp > 0; a_integer.array_size++) {
        temp = temp / 16;
    }
    if(flags->hashtag == true) {
        //printf("size == %d, %d", a_integer.array_size, a_integer.number_size);
        a_integer.array_size = a_integer.array_size + 2;
    }
    //printf("size == %d, %d end||", a_integer.array_size, a_integer.number_size);

    hex_print = malloc(sizeof(int) * a_integer.array_size);


    for(int i = a_integer.array_size - 1; integer != 0; i--) {
        //printf("hi");
        if(integer % hex > 9 && type == 'x') {
            hex_print[i] = ((integer % hex) - 10) + 'a';
            integer = integer / hex;
            //a_integer.array_size++;                 
        }else if(integer % hex > 9 && type == 'X'){
            hex_print[i] = ((integer % hex) - 10) + 'A';
            integer = integer / hex;
            //a_integer.array_size++; 
        }else{
            hex_print[i] = (integer % hex) + '0';
            integer = integer / hex;
            //a_integer.array_size++;
        }
    }
        if(flags->hashtag == true) {
            hex_print[0] = '0';
            if(type == 'x') {
                hex_print[1] = 'x';
            }else{
                hex_print[1] = 'X';
            }
            //a_integer.array_size += 2;
            flags->hashtag = false;
        }

    //printf("size == %d, %d", a_integer.array_size, a_integer.number_size);
    a_integer.p_integer = hex_print;

    if(length->fieldwidth > 0 && length->precision > 0){
        
        return_size = return_size + field_precision_integer(length, flags, &a_integer, type);

    }else if(length->precision > 0) {
    
        return_size = return_size + precision_integer(length, &a_integer, type);

    }else if(length->fieldwidth > 0){

        return_size = return_size + field_integer(length, flags, &a_integer, type);

    }else {
        return_size = return_size + print_int_array(a_integer.p_integer, a_integer.array_size);
    }
    // print_integers(integer);
    // printf("return number == %d\n", return_size);

    free(hex_print);
    return return_size;
}

//same with this one it works for now. doesnt support multi langs tho. im prob going end up having to rewrite everything.
int percent_c(char c){
    
    write(1,&c,1);
    
    return 1;
}

//this works for now. same it doesnt suport multi langs. im prob going have to rewrite everything. on this one too.
int percent_s(char *string){
    int return_size = 0;

    for(return_size; string[return_size] != '\0'; return_size++) {
        print_char(string[return_size]);
    }

    return return_size;
}

//soo this was a rushed job still janky but it looks better? i think.
//int32_t, uint64_t look into later.
int percent_p(void *pointer) {
    int hex = 16;
    int64_t temp = (int64_t)pointer;//these typecasts are just janky way to convert this to a integer idk if i even need to do that
    int64_t pointer_int = (int64_t)pointer;
    int number_size = 0;
    unsigned int *hex_print;
    int return_size = 0;
    //printf("printing out pointer = %lld\n", temp / 100);
    for(number_size = 0; temp > 0; number_size++){
        temp = temp / 16;
    }
    hex_print = malloc(sizeof(unsigned int) * number_size);
    //printf("number size = %d\n", number_size);
    for(int i = 0; pointer_int > 0; i++) {
    //printf("hi");

        if(pointer_int % hex > 9){
            hex_print[i] = ((pointer_int % hex) - 10) + 'A';
            pointer_int = pointer_int / hex;
        }else{
            hex_print[i] = (pointer_int % hex) + '0';
            pointer_int = pointer_int / hex;
        }
    }
    for(int i = (sizeof(int64_t) * 2) - 1; i >= 0; i--){
        if(i >= number_size) {
            print_char('0');
            return_size++;
        }else{
            print_char(hex_print[i]);
            return_size++;
        }
    }
    free(hex_print);
    return return_size;
}

int permament_rounding(double a_float, int last_digit, char check_percent) {
    int return_number = 0;
    int temp_number = -1;
    int temp_number2 = -2;
    double temp_float = 0.0;
    bool do_we_round = false;

    for(int i = 0; i <= last_digit; i++) {
        temp_number = (int)a_float;

        if(temp_number == 9) {
            do_we_round = true;
            temp_float = a_float;
            for(int j = i; j <= last_digit; j++) {
                temp_float = temp_float * 10;
                
                if((int)temp_float % 10 != 9) {
                    do_we_round = false;
                }
            }
            if(do_we_round){

                if(check_percent == 'f') {
                    return i - 2;
                }else{
                    return i - 1;
                }

            }
        }
        a_float = a_float - temp_number;
        a_float = a_float * 10;
    }

    return -1;
}

int print_float(double a_float, char check_percent, int precision, int place_decimal, int last_digit) {
    
    int this_number = 0;
    int return_size = 0;
    int do_we_round = -1;

    if (check_percent == 'e'){
        a_float = a_float /10;
        do_we_round = permament_rounding(a_float, last_digit, check_percent);
    }else{
        do_we_round = permament_rounding(a_float, last_digit, check_percent);
    }
    //printf("number do_we_round has == %d\n", do_we_round);
    
    //printf("last digit equals == %d\n", last_digit);
    //printf("%f\n", a_float);
    
        for(int i = 0; i <= last_digit; i++) {
        if(i == place_decimal) {
            if(i == 0) {
                print_char('0');
                print_char('.');
                return_size = return_size + 2;
            }else{
                print_char('.');
                return_size++;
            }

        }
        //sooo i tried a few ways to grab the numbers from float but all gave me same problems soo this way most simple way to do it.
        //also i have no idea how to grab anything pass decimal without using precision. to do it.
        a_float = a_float * 10;
        if(i == do_we_round) {
            a_float = round(a_float);
        }
        this_number = (int)a_float;

        if(i >= place_decimal && (check_percent == 'g' || check_percent == 'G')) {
            //printf("%f %d %d %d\n", a_float, last_digit, this_number, j);
            //printf("true == 1 false == 0 === %d\n", checking_all_zeros(a_float, last_digit, this_number, j));
            if(checking_all_zeros(a_float, last_digit, this_number, i)) {
                break;
            }
        }
        
        if(round(a_float) - .0001 > a_float) {//this works but it doesnt cover anything less thing .01 which can be a issue i could do it as low as .001 but still the issue would be there i feel like .001 would be fine for now tho.
            if(i == last_digit) {
                this_number = finding_number_double(round(a_float));
            }
            print_char((this_number + 48));
            //printf("hi\n");
            a_float = a_float - this_number;

        }else{
            this_number = finding_number_double(round(a_float));
            print_char((this_number + 48));
            //printf("bye\n");
            a_float = a_float - this_number;

        }
        return_size++;
    }
    
    return return_size;
}

//another thing that needs to be done is i neeed to make this combatible with percent_g which requires deletion of all trailing 0's soo far my idea is that i use a for loop to see if reminding numbers are zero if so skip printing everything. maybe i use break command or something to break out the for loop. i could also use a while loop with condition of while bool is_number_done -- true and j <= last_digit do a thing if is_number_done still equals true break. this would need to be into a if with condition char c == g or G do a thing.
int percent_f(char check_percent, s_length *length, s_flags *flags, double a_float) {
    int return_size = 0;
    int place_decimal = 0;
    int precision = 6;
    int last_digit = 0;
    int this_number = 10;
    int do_we_round = -1;
    //bool fuck_me = false;// this was a check to see if i need to round the number in case of compilier error not being used atm.

    //printf("flags blank == %d\n", flags->blank);
    if(length->precision > 0 || flags->blank == true){
        //printf("wrong = %d", length->precision - 1);
        precision = length->precision;
    }
    if(a_float < 0) {
        a_float = a_float * -1;
        print_char('-');
        return_size++;
    }
    //printf("%f\n", a_float);
    if(a_float == 1.0){
        print_char('1');
        // i may need to remove the .0 for g.
        if(check_percent == 'g' || check_percent == 'G') {
            print_char('.');
            print_char('0');
            return 3;
        }else{
            print_char('.');

            for(int i = 0; i < 6; i++){
                print_char('0');
            }
            return 8;
        }

    }
    for(place_decimal = 0; a_float > 1; place_decimal++) {
        a_float = a_float / 10;
    }

    if(check_percent == 'g' || check_percent == 'G') {
        last_digit = precision - 1;
    }else{
        last_digit = precision + place_decimal - 1;
    }

    return_size = return_size + print_float(a_float, check_percent, precision, place_decimal, last_digit);
    
    return return_size;
}
//same as f.
int percent_e(char check_percent, s_length *length, s_flags *flags, double a_float) {
    int return_size = 0;
    int precision = 6;
    int expondent_value = 0;
    int this_number = 10;
    int last_digit = 0;
    int do_we_round = -1;

    //printf("testing %f\n", a_float);
    if(length->precision > 0 || flags->blank == true){
        precision = length->precision;
    }
    //this checks for negative and turns it positive.
    if(a_float < 0) {
        a_float = a_float * -1;
        print_char('-');
        return_size++;
    }
    //this is for expondent_value at the end if its less then 1 it multi it by 10 until its between 1 and 9.
    //if its greater then 1 and 9 it divides the number by 10 until it hits a number between 1 and 9.
    
    if(a_float < 1){
        for(expondent_value = 0; a_float < 1; expondent_value--){
            a_float = a_float * 10;
            //printf("test");
        }
    }else{
        for(expondent_value = 0; a_float > 10; expondent_value++){
            a_float = a_float / 10;
        }
    }


    if(check_percent == 'g') {
        last_digit = precision - 1;
    }else{
        last_digit = precision;
    }
   
    //printf("expondent vaulue == %d\n", expondent_value);
    return_size = return_size + print_float( a_float, check_percent, precision, 1, last_digit);

    //all these if statements are used for expondent print out e.g == (number)+e00 or (number)+E00.
    //i want kind of want put this into its own function to seperate them for better readability.
    //printf("and i get == %d\n", expondent_value);
    if(expondent_value > 0) {
        print_char('+');
    }else{
        print_char('-');
        expondent_value = expondent_value * -1;
    }
    
    if(check_percent == 'E' || check_percent == 'G'){
        if(expondent_value < 10 && expondent_value > -10) {
            return_size += print_char('E');
            return_size += print_char('0');
            return_size += print_char(expondent_value + '0');
            
        }else{
            return_size += print_char('E');
            return_size += print_integers(expondent_value);
        }
    }else{
        if(expondent_value < 10 && expondent_value > -10) {
            return_size += print_char('e');
            return_size += print_char('0');
            return_size += print_char(expondent_value + '0');
        }else{
            return_size += print_char('e');
            return_size += print_integers(expondent_value);
        }
    }

    return return_size;
}

int percent_g(char check_percent, s_length *length, s_flags *flags, double a_float){
    int return_size = 0;
    int check_size = 1;
    //printf("%d\n", length->precision );

    if(flags->blank == true) {
        length->precision = 1;
    }else if(length->precision == 0) {
        length->precision = 6;
    }

    for(int i = 0; i < length->precision; i++) {
        check_size = check_size * 10;
    }
    //printf("check size == %d float == %f length is == %d\n", check_size, a_float, length->precision);

    if(check_size > a_float) {
       return_size = percent_f(check_percent, length, flags, a_float);
    }else{
        //printf("in == e");
        return_size = percent_e(check_percent, length, flags, a_float);
    }    
    

    return return_size;
}



/*
things to keep in mind when im rounding one it doesnt need be in the loop its one time check to see if i need to round the number at all conditions for rounding condition one the number one after last printed number needs to be above or at 6 if this isnt case we exit the function and keep moving on 2. we need save spot where we round this will never be a negative number so for defualt the number to check needs to be zero or higher and three while we looping we need round at the exact place soo
*/
// double rounding(double number) {
//     int i = 0;
//     int j = 0;
//     bool round_up = false;
//     for(i = 0; i < 3; i++) {
//         number = number * 10;
//     }
//     for(j = 0; (int)number % 10 == 5; j++) {
//         number = number * 10;
//     }
//     if((int)number % 10 > 5 && j == 0){
//         number++;
//     }else if((int)number % 10 > 5) {
//         round_up = true;
//     }
//     for(i = j + i; i >= 0; i--, j--) {
//         if(j == 0 && round_up == true) {
//             number++;
//         }
//         number = number / 10;
//     }

//     return number;
// }

//////////////////////////////////////////////////////////////////////////////////////////////////back up code for later
//     do_we_round = permament_rounding(a_float, last_digit, 'e');

//     for(int i = 0; i <= last_digit; i++) {
        
//         if(do_we_round == i) {
//             a_float = round(a_float);
//         }

//         //i moved it above so that way checking all zeros works normally
//         this_number = (int)a_float;
//         //this just makes sure we dont have any trailing zeros at end of our output for g.
//         if(i >= 0 && (check_percent == 'g' || check_percent == 'G')) {

//             if(checking_all_zeros(a_float, last_digit, this_number, i)) {
//                 break;
//             }
//         }
//         if(i == 1) {
//             print_char('.');
//             return_size++;
//         }
// //this shit right here used to print out the float and check to see if compilier got any rounding errors its not perfect but it works.
// /////////////////////////////////////////

//         if(round(a_float) - .0001 > a_float) {
//             if(i == last_digit - 1) {
//                 this_number = finding_number_double(round(a_float));
//             }
//             print_char((this_number + 48));
//             a_float = a_float - this_number;
//         }else{
//             this_number = finding_number_double(round(a_float));
//             print_char((this_number + 48));
//             a_float = a_float - this_number;
//         }
//         a_float = a_float * 10;
//         return_size++;
// ////////////////////////////////////////
//     }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // do_we_round = permament_rounding(a_float, last_digit, 'f');
    // //printf("number do_we_round has == %d\n", do_we_round);
    
    // //printf("last digit equals == %d\n", last_digit);
    // //printf("%f\n", a_float);
    // for(int i = 0; i <= last_digit; i++) {
    //     if(i == place_decimal) {
    //         if(i == 0) {
    //             print_char('0');
    //             print_char('.');
    //             return_size = return_size + 2;
    //         }else{
    //             print_char('.');
    //             return_size++;
    //         }

    //     }
    //     //sooo i tried a few ways to grab the numbers from float but all gave me same problems soo this way most simple way to do it.
    //     //also i have no idea how to grab anything pass decimal without using precision. to do it.
    //     a_float = a_float * 10;
    //     if(i == do_we_round) {
    //         a_float = round(a_float);
    //     }
    //     this_number = (int)a_float;

    //     if(i >= place_decimal && (check_percent == 'g' || check_percent == 'G')) {
    //         //printf("%f %d %d %d\n", a_float, last_digit, this_number, j);
    //         //printf("true == 1 false == 0 === %d\n", checking_all_zeros(a_float, last_digit, this_number, j));
    //         if(checking_all_zeros(a_float, last_digit, this_number, i)) {
    //             break;
    //         }
    //     }
        
    //     if(round(a_float) - .0001 > a_float) {//this works but it doesnt cover anything less thing .01 which can be a issue i could do it as low as .001 but still the issue would be there i feel like .001 would be fine for now tho.
    //         if(i == last_digit) {
    //             this_number = finding_number_double(round(a_float));
    //         }
    //         print_char((this_number + 48));
    //         //printf("hi\n");
    //         a_float = a_float - this_number;

    //     }else{
    //         this_number = finding_number_double(round(a_float));
    //         print_char((this_number + 48));
    //         //printf("bye\n");
    //         a_float = a_float - this_number;

    //     }
    //     return_size++;
    // }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // this if statement used if we got condition where perision == 1 it removes the float part of the whole thing i might instead just pass it as a integer or remove it all together and try making it better.
        // if(last_digit == 1) {
        // print_char(round(a_float + 48));
        // return_size++;
        // break;
        // }



/*
    for(int i = 0; i <= last_digit; i++) {
        if(i == place_decimal) {
            if(i == 0) {
                print_char('0');
                print_char('.');
                return_size = return_size + 2;
            }else{
                print_char('.');
                return_size++;
            }
        }
        a_float = a_float * 10;
        if(i == do_we_round) {
            a_float = round(a_float);
        }
        this_number = (int)a_float;

        if(i >= place_decimal && (check_percent == 'g' || check_percent == 'G')) {

            if(checking_all_zeros(a_float, last_digit, this_number, i)) {
                break;
            }
        }
        
        if(round(a_float) - .0001 > a_float) {//this works but it doesnt cover anything less thing .0001 which can be a issue i could do it as low as .001 but still the issue would be there i feel like .001 would be fine for now tho.
            if(i == last_digit) {
                this_number = finding_number_double(round(a_float));
            }
            print_char((this_number + 48));
            //printf("hi\n");
            a_float = a_float - this_number;

        }else{
            this_number = finding_number_double(round(a_float));
            print_char((this_number + 48));
            //printf("bye\n");
            a_float = a_float - this_number;

        }
        return_size++;
    }
    */








// int test_double() {
//     double a_number = 123.123;
//     double another_number;
//     int persion = 6;
//     int i = 0;
//     int j = 0;
//     for(i; a_number > 1; i++) {
//         //printf("%d\n", (long long int)a_number % 10);
//         a_number = a_number / 10;
//         //printf("%f\n", );
//     }
//     printf("%f , %d\n", a_number, i);
//     another_number = a_number;
//     for(j = 0; j < persion; j++) {
//         a_number = a_number * 10;
//         if(j == i){
//             if(j == 0){
//                 print_char('0');
//                 print_char('.');
//             }else{
//                 print_char('.');
//             }

//         }
//         print_char((int)a_number + 48);
//         //printf("%d\n", (int)a_number);
//         a_number = a_number - (int)a_number;
//     }
//     print_char('\n');
//     for(j = 0; j < persion; j++){
//         if(i == 0){
//             print_char('0');
//         }
//         if(j == 1) {
//             print_char('.');
//         }
//         another_number = another_number * 10;
//         print_char((int)another_number + 48);
//         another_number = another_number - (int)another_number;
//     }
//     if(true){
//         print_char('e');
//         if(i < 10){
//             i--;
//             print_char('0');
//             print_char(i+48);
//         }
//     }else if(false){
//         print_char('E');
//         if(i < 10){
//             i--;
//             print_char('0');
//             print_char(i+48);
//         }
//     }
//     print_char('\n');
//     //printf("%f , %d\n", a_number, j);
//     printf("%d\n", sizeof(double));
//     return 0;
// }