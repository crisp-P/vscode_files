#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>

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
    int number_size;
    int array_size;
}s_vector_number;

int print_char(char c);
int print_int_array(int *number_array, int array_size);
int print_integers(long long int number);
int convert_char_to_num(const char *string);
void if_negative_make_zero(s_length *length, int number_size);
int my_printf(const char *string, ...);
void flag_checker(const char *string, char conversion, s_flags *flags);
int perameters(const char *string, int *characters_printed, va_list *vector_list);
int percent_d(s_flags *flags, s_length *length, int integer);
int field_precision_integer (s_length *length, s_flags *flags, s_vector_number *a_integer);
int precision_integer(s_length *length, s_vector_number *a_integer);
int field_integer(s_length *length, s_flags *flags, s_vector_number *a_integer);
int percent_0_u(char type, s_flags *flags, s_length *length, unsigned int integer);
void precent_o(s_vector_number *a_integer, s_flags *flags);
int percent_x_X(char type, s_flags *flags, s_length *length, unsigned int integer);
int percent_c(char c);
int percent_s(char *string);
int percent_p(void *pointer);


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

int main(int ac, char **av) {
    void *pointer;
    int check = printf("%p\n", (void*)pointer);
    printf("%llu\n", pointer);
    printf("%lld\n", pointer);
    printf("%#llX\n", pointer);
    printf("%d\n",check);
    check = my_printf("abc%dadcbe%#+ 4.5dabdc%-4dabcd%1.3da%-1.1daoctal%5.7uahexical%-#9Xabc%c12a%s123\n", 0, -98, 987, 87, 876, 12345, 11111, 'a', "hi");
    printf("%.0d\n", check);
    check = my_printf("final results for pointer = %p\n", pointer);
    printf("%d\n", check);
    return 0;
}
//thing i need to work on lets get %d with flags working here hoping it works with other parameters later.
int my_printf(const char *string, ...) {

    va_list vector_list;
    int delete_later = 0;
    int argments_passed = 0;
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
            flags->blank == true;
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
        if(string[i] >= 'A' && string[i] <= 'Z' || string[i] >= 'a' && string[i] <= 'z') {
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
    if(string[i] == 's'){
        *characters_printed = *characters_printed + percent_s(va_arg(*vector_list, char*));
    }
    if(string[i] == 'p'){
        *characters_printed = *characters_printed + percent_p(va_arg(*vector_list, void*));
    }
    if(string[i] == '%') {
        print_char(string['%']);
        *characters_printed++;
        return i;
    }

    return i;
}

//this is %d.
int percent_d(s_flags *flags, s_length *length, int integer) {
    int return_size = 0;
    int power_ten = 1;
    s_vector_number a_integer  = {a_integer.p_integer = &integer,
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
        
        return_size = return_size + field_precision_integer(length, flags, &a_integer);

    }else if(length->precision > 0) {
    
        return_size = return_size + precision_integer(length, &a_integer);

    }else if(length->fieldwidth > 0){

        return_size = return_size + field_integer(length, flags, &a_integer);

    }else {
        return_size = return_size + print_integers(*a_integer.p_integer);
    }
    //print_integers(integer);
    //printf("return number == %d\n", return_size);
    return return_size;
}

//idk how to type field&precision for percent d soo this is the name i gave it.
int field_precision_integer (s_length *length, s_flags *flags, s_vector_number *a_integer) {
    int return_size = 0;
    
    if(flags->negitive == true) {
        //i might make this a seperate function later for now ill keep it in here.
        for(length->precision; length->precision >= 0; length->precision--, length->fieldwidth--) {
            //printf("precision == %d number size == %d\n", length->precision, number_size);
            if(length->precision > a_integer->number_size && length->precision > a_integer->array_size){
                print_char('0');
                return_size++;
            }else if(a_integer->array_size == 0){
                return_size  = print_integers(*a_integer->p_integer) + return_size;
                if_negative_make_zero(length, a_integer->number_size);
            }else{
                return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
                if_negative_make_zero(length , a_integer->array_size);
            }
        }

        for(length->fieldwidth; length->fieldwidth >= 0; length->fieldwidth--) {
            print_char(' ');
            return_size++;
        }
    }else{

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
                return_size = print_integers(*a_integer->p_integer) + return_size;
                if_negative_make_zero(length , a_integer->number_size);
            }else {
                return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
                if_negative_make_zero(length , a_integer->array_size);
            }
        }
    }

    return return_size;
}

int precision_integer(s_length *length, s_vector_number *a_integer) {
    int return_size = 0;
    
    for(length->precision;length->precision > a_integer->number_size && length->fieldwidth > a_integer->array_size; length->precision--) {
        print_char('0');
        return_size++;
    }
    if(a_integer->array_size == 0){
    
        return_size = return_size + print_integers(*a_integer->p_integer);

    }else{
        return_size = return_size + print_int_array(a_integer->p_integer, a_integer->array_size);
    }

    return return_size;
}

int field_integer(s_length *length, s_flags *flags, s_vector_number *a_integer) {
    int return_size = 0;
    
    if(flags->negitive == true) {//number size just find how many digits it takes to make the  number;
        if(a_integer->array_size == 0){
        
            return_size = return_size + print_integers(*a_integer->p_integer);
        
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

int percent_0_u(char type, s_flags *flags, s_length *length, unsigned int integer){
    int return_size = 0;
    //int power_ten = 1;
     int test = (int)integer;
    int number_size = 0;
    s_vector_number a_integer  = {a_integer.p_integer = &integer,
                                  a_integer.array_size = 0,
                                  a_integer.number_size = 0
    };
    //printf("hi");

    if(flags->blank == true && integer == 0) {
        //printf("hi");
        return return_size;
    }

    if(type == 'o') {
        precent_o(&a_integer, flags);
    }else if(type == 'u'){
        unsigned int temp = integer;
        for(a_integer.number_size = 0; temp > 0; a_integer.number_size++){
            temp = temp / 10;
        }
    }

    //printf("%d %d\n", *a_integer.p_integer, a_integer.number_size);
    if(length->fieldwidth > 0 && length->precision > 0){
        
        return_size = return_size + field_precision_integer(length, flags, &a_integer);

    }else if(length->precision > 0) {
    
        return_size = return_size + precision_integer(length, &a_integer);

    }else if(length->fieldwidth > 0){

        return_size = return_size + field_integer(length, flags, &a_integer);

    }else {
        if(type == 'o') {
            return_size = return_size + print_int_array(a_integer.p_integer, a_integer.array_size);
        }else if(type == 'u') {
            return_size = return_size + print_integers(test);
        }
    }
    if(type == 'o') {
        free(a_integer.p_integer);
    }
    return return_size;
}

void precent_o(s_vector_number *a_integer, s_flags *flags) {

    unsigned temp = *a_integer->p_integer;
    unsigned int converted_to_octal = 0;
    unsigned int octal = 8;

    for(a_integer->array_size; temp > 0; a_integer->array_size++) {
        temp = temp / 8;
    }

    if(flags->hashtag == true) {
        a_integer->array_size++;
        //a_integer->number_size++;
    }

    int *array = malloc(sizeof(int) * a_integer->array_size);

    for(int i = a_integer->array_size - 1; *a_integer->p_integer > 0; i--) {
        if(flags->hashtag == true) {
            array[0] = '0';
            flags->hashtag = false;
        }
        array[i] = (*a_integer->p_integer % 8) + '0';
        *a_integer->p_integer = *a_integer->p_integer / 8;
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
    unsigned int hex = 16;
    unsigned int temp = integer;
    unsigned int number_size = 0;
    unsigned int *hex_print;
    int return_size = 0;

    s_vector_number a_integer  = {a_integer.p_integer = NULL,
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

    hex_print = malloc(sizeof(unsigned int) * a_integer.array_size);


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
        
        return_size = return_size + field_precision_integer(length, flags, &a_integer);

    }else if(length->precision > 0) {
    
        return_size = return_size + precision_integer(length, &a_integer);

    }else if(length->fieldwidth > 0){

        return_size = return_size + field_integer(length, flags, &a_integer);

    }else {
        return_size = return_size + print_int_array(a_integer.p_integer, a_integer.array_size);
    }
    // print_integers(integer);
    // printf("return number == %d\n", return_size);

    free(hex_print);
    return 0;
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

//soo this was a rushed job also it only accounts for 64 bit computers sooooooooooo ye. if this ran on linux it prob wouldnt work soooo ye. need fix later
int percent_p(void *pointer) {
    int hex = 16;
    long long int temp = (long long int)pointer;//these typecasts are just janky way to convert this to a integer idk if i even need to do that tho.
    long long int pointer_int = (long long int)pointer;
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
    for(int i = 15; i >= 0; i--){
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