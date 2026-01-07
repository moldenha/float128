#include "float128.h"
#include <iostream>
#include <random>
#include <iomanip>

using uint128_t = __uint128_t;
using int128_t = __int128_t;

/*
Tensor fail cases:
reciprical (from int128 to float128 could be the culprit)
round
floor
log and exp - inverse did not work - log/exp inverse failed

(all the trig)


 */


double check_num_array[9] = {3.3, 4.6, 4.1, -1.2, 4.1, 0.9, 0.1, -3.0, 10.5};
nt::float128_t check_num_array_f128[9] = {3.3_f128, 4.6_f128, 4.1_f128, -1.2_f128, 4.1_f128, 0.9_f128, 0.1_f128, -3.0_f128, 10.5_f128};
bool are_close(double a, double b, double epsilon) {
    // Check if the absolute difference is less than or equal to epsilon
    return std::abs(a - b) <= epsilon;
}
template<typename FuncStd, typename FuncNT>
void check_functions(FuncStd&& f1, FuncNT&& f2, bool show_working = false){
    for(int i = 0; i < 9; ++i){
        double f_out = f1(check_num_array[i]);
        nt::float128_t f128_out = f2(check_num_array_f128[i]);
        if(std::isnan(f_out) && f128_out.get_bits().is_nan()){
            if(!show_working) continue;
            std::cout << "function worked for "<<check_num_array[i] << " -> (f128) " << f128_out << " == " << " (std) " << f_out << std::endl;
            continue;
        }
        if(std::isnan(f_out) || f128_out.get_bits().is_nan())
            std::cout << "error function failed for "<<check_num_array[i] << " -> (f128) " << f128_out << " != " << " (std) " << f_out << std::endl;
        if(std::isinf(f_out) && f128_out.get_bits().is_inf()){
            if(f_out < 0 && f128_out.get_bits().sign() && !show_working) continue;
            if(f_out > 0 && !f128_out.get_bits().sign() && !show_working) continue;
            else{
                std::cout << "error function failed for "<<check_num_array[i] << " -> (f128) " << f128_out << " != " << " (std) " << f_out << std::endl;
            }
        }
        if(!are_close(double(f128_out), f_out, 1e-4)){
            std::cout << "error function failed for "<<check_num_array[i] << " -> (f128) " << f128_out << " != " << " (std) " << f_out << std::endl;
            continue;
        }
        if(show_working)
            std::cout << "function worked for "<<check_num_array[i] << " -> (f128) " << f128_out << " == " << " (std) " << f_out << std::endl;
    }
}

// #define NT_FLOAT128_HEADER_ONLY__
// #include "pow_ten_lookup.h"
// #undef NT_FLOAT128_HEADER_ONLY__ 








void addition_test(){
    constexpr nt::float128_t f = -1.2352356_f128;
    constexpr nt::float128_t f3 = 23.13356_f128;
    constexpr nt::float128_t nf3 = f + f3;
    std::cout << nf3 << std::endl;
    std::cout << double(-1.2352356) + double(23.13356) << std::endl; 
}

void multiplication_test(){
    constexpr nt::float128_t f = -1.2352356_f128;
    constexpr nt::float128_t f3 = 23.13356_f128;
    constexpr nt::float128_t nf3 = f * f3;
    std::cout << nf3 << std::endl;
    std::cout << double(-1.2352356) * double(23.13356) << std::endl; 
}

void multiplication_test_2(){
    constexpr nt::float128_t f = 2.0_f128;
    constexpr nt::float128_t f3 = -3.85186e-34_f128;
    constexpr nt::float128_t nf3 = f3 * f;
    std::cout << nf3 << std::endl;
    std::cout << double(2.0) * double(-3.85186e-34) << std::endl; 
}

void division_test(){
    constexpr nt::float128_t f = -1.2352356_f128;
    constexpr nt::float128_t f3 = 23.13356_f128;
    nt::float128_t nf3 = f / f3;
    std::cout << nf3 << " ?= " << double(-1.2352356) / double(23.13356) << std::endl;
}

void division_test_2(){
    nt::float128_t f = nt::float128_t::from_double(-1.2352356);
    nt::float128_t f3 = nt::float128_t::from_double(23.13356);
    nt::float128_t nf3 = f / f3;
    std::cout << nt::float128_t::from_double(1.0) / f3 << " ?= " << 1.0 / double(23.13356) << std::endl;
    std::cout << nt::float128_t::from_double(1.0) / f << " ?= " << 1.0 / double(-1.2352356) << std::endl;
}

void division_test_3(){
    nt::float128_t f = nt::float128_t::from_double(-1.2352356);
    nt::float128_t f3 = nt::float128_t::from_double(23.13356);
    nt::float128_t nf3 = f3 / f;
    std::cout << nf3 <<  " ?= " << double(23.13356) / double(-1.2352356) << std::endl;
}


void test_kmath(){
    constexpr nt::float128_t f = -1.2342134_f128;
    std::cout << nt::math::kmath::abs(f) << std::endl;
    std::cout << nt::math::kmath::trunc(f) << std::endl;
}

void test_sqrt(){
    constexpr nt::float128_t f = 3.4631_f128;
    double d = 3.4631;
    std::cout << nt::math::sqrt(f) << std::endl;
    std::cout << std::sqrt(d) << std::endl;
    std::cout << nt::math::sqrt(f).get_bits() << std::endl;
    std::cout << nt::float128_t(std::sqrt(d)).get_bits() << std::endl;
    for(int i = 0; i < (1 + 15 - 1); ++i){
        std::cout << ' ';
    }
    std::cout << "^" << std::endl;
    std::cout << nt::bitset<64, uint64_t>(nt::bit_cast<uint64_t>(std::sqrt(d))) << std::endl;
    nt::b256 a(uint64_t(16378), uint64_t(972), uint64_t(78), uint64_t(5162));
    std::cout << a << std::endl;
    nt::b256 c(14);
    std::cout << c << std::endl;
    std::cout << (a / c) << std::endl;
    std::cout << (nt::b256(88) / nt::b256(8)) << std::endl;
}

void test_sqrt_2(){
    constexpr nt::float128_t f = 0.4631_f128;
    double d = 0.4631;
    std::cout << nt::math::sqrt(f) << std::endl;
    std::cout << std::sqrt(d) << std::endl;
    std::cout << nt::math::sqrt(f).get_bits() << std::endl;
    std::cout << nt::float128_t(std::sqrt(d)).get_bits() << std::endl;
    for(int i = 0; i < (1 + 15 - 1); ++i){
        std::cout << ' ';
    }
    std::cout << "^" << std::endl;
}

void test_sqrt_3(){
    constexpr nt::float128_t f = 306.4631_f128;
    double d = 306.4631;
    std::cout << nt::math::sqrt(f) << std::endl;
    std::cout << std::sqrt(d) << std::endl;
    std::cout << nt::math::sqrt(f).get_bits() << std::endl;
    std::cout << nt::float128_t(std::sqrt(d)).get_bits() << std::endl;
    for(int i = 0; i < (1 + 15 - 1); ++i){
        std::cout << ' ';
    }
    std::cout << "^" << std::endl;
}

void test_exp(){
    constexpr nt::float128_t f = 3.4631_f128;
    double d = 3.4631;
    std::cout << nt::math::exp(f) << std::endl;
    std::cout << std::exp(d) << std::endl;
}

void test_exp_2(){
    constexpr nt::float128_t f = 0.4631_f128;
    double d = 0.4631;
    std::cout << nt::math::exp(f) << std::endl;
    std::cout << std::exp(d) << std::endl;
}

void test_exp_3(){
    constexpr nt::float128_t f = 306.4631_f128;
    double d = 306.4631;
    std::cout << nt::math::exp(f) << std::endl;
    std::cout << std::exp(d) << std::endl;
}

void test_ldexp(){
    NT_CPP20_CONSTEXPR nt::float128_t f = nt::float128_t::from_double(4.5);
    double d = 4.5;
    std::cout << "ldexp test: " << std::endl;
    std::cout << nt::math::kmath::ldexp(f, 5) << std::endl;
    std::cout << std::ldexp(d, 5) << std::endl;
}


void test_log(){
    std::cout << "testing log" << std::endl;
    NT_CPP20_CONSTEXPR nt::float128_t f = nt::float128_t::from_double(3.4631);
    double d = 3.4631;
    std::cout << nt::math::log(f) << std::endl;
    std::cout << std::log(d) << std::endl;
}

void test_log_2(){
    NT_CPP20_CONSTEXPR nt::float128_t f = nt::float128_t::from_double(0.4631);
    double d = 0.4631;
    std::cout << nt::math::log(f) << std::endl;
    std::cout << std::log(d) << std::endl;
}

void test_log_3(){
    constexpr nt::float128_t f = 306.4631_f128;
    double d = 306.4631;
    std::cout << nt::math::log(f) << std::endl;
    std::cout << std::log(d) << std::endl;
}


void test_pow(){
    std::cout << "testing pow" << std::endl;
    constexpr nt::float128_t f = 3.4631_f128;
    constexpr nt::float128_t b = 5.6_f128;
    double d = 3.4631;
    std::cout << nt::math::f128_pow(f, b) << std::endl;
    std::cout << std::pow(d, 5.6) << std::endl;
}

void test_pow_2(){
    constexpr nt::float128_t f = 0.4631_f128;
    constexpr nt::float128_t b = 5.6_f128;
    double d = 0.4631;
    std::cout << nt::math::f128_pow(f, b) << std::endl;
    std::cout << std::pow(d, 5.6) << std::endl;
}

void test_pow_3(){
    constexpr nt::float128_t f = 306.4631_f128;
    constexpr nt::float128_t b = 5.6_f128;
    double d = 306.4631;
    std::cout << nt::math::f128_pow(f, b) << std::endl;
    std::cout << std::pow(d, 5.6) << std::endl;
}


void test_atan(){
    std::cout << "testing atan" << std::endl;
    constexpr nt::float128_t f = 3.4631_f128;
    double d = 3.4631;
    std::cout << nt::math::atan(f) << std::endl;
    std::cout << std::atan(d) << std::endl;
}

void test_atan_2(){
    constexpr nt::float128_t f = 0.4631_f128;
    double d = 0.4631;
    std::cout << nt::math::atan(f) << std::endl;
    std::cout << std::atan(d) << std::endl;
}

void test_atan_3(){
    constexpr nt::float128_t f = 306.4631_f128;
    double d = 306.4631;
    std::cout << nt::math::atan(f) << std::endl;
    std::cout << std::atan(d) << std::endl;
}

void test_tenth_power(){
    nt::float128_t f(1);
    // std::cout << f << ',' << f.get_bits() << std::endl;
    for(int i = 0; i < 4930; ++i){
        f = f * 10;
    }
    std::cout << std::boolalpha <<  nt::float128_t::make_inf().get_bits().is_inf() << std::noboolalpha << std::endl;
    std::cout << std::boolalpha << f.get_bits().is_inf() << std::noboolalpha << std::endl;
    for(int i = 0; i < 5; ++i){
        f = f * 10;
        std::cout << std::boolalpha << f.get_bits().is_inf() << std::noboolalpha << std::endl;
        std::cout << f << ',' << f.get_bits() << std::endl;
        for(int j = 0; j < (1 + 15 - 1); ++j){
            std::cout << ' ';
        }
        std::cout << "^" << std::endl;
    }
    std::cout << std::boolalpha << f.get_bits().is_inf() << std::noboolalpha << std::endl;

}

void test_tenth_neg_power(){
    nt::float128_t f(1);
    std::cout << f << ',' << f.get_bits() << std::endl;
    for(int i = 0; i < 40; ++i){
        f = f / 10;
        std::cout << f << ',' << f.get_bits() << std::endl;
    }
}


void print_bits_and_number(nt::float128_t f){
    std::cout << f << ',' << f.get_bits() << std::endl;
}

void from_string_test(){
    std::string s = "123.423566";
    std::size_t decimal = s.find('.');
    std::cout << s.substr(0, decimal) << "    " << s.substr(decimal+1) << std::endl;
    std::cout << s.substr(0, 4) << "    " << s.substr(4) << std::endl;
    NT_CPP20_CONSTEXPR nt::float128_t f = 123.42134421_f128;
    std::cout << std::setprecision(10) << f << std::endl;
}

inline nt::float128_t portable_128_int_to_floating(int128_t val) {
    bool sign = val < 0;
    val = sign ? -val : val;
    nt::b128 b = nt::bit_cast<nt::b128>(val);
    return sign ? -nt::float128_t::from_integer(b) : nt::float128_t::from_integer(b);
}

inline nt::float128_t portable_128_int_to_floating(uint128_t val) {
    nt::b128 b = nt::bit_cast<nt::b128>(val);
    return nt::float128_t::from_integer(b);
}



int main(){
    // NT_CPP20_CONSTEXPR nt::b128 a(10);
    // NT_CPP20_CONSTEXPR nt::b128 b(20019);
    // NT_CPP20_CONSTEXPR nt::b128 d = a + b;
    // std::cout << a << ',' << b << ',' << d << std::endl;
    // NT_CPP20_CONSTEXPR nt::b128 b_mult = a * b;
    // std::cout << b_mult << std::endl;
    // NT_CPP20_CONSTEXPR nt::float128_t f = nt::float128_t::from_double(-1.2352356);
    // NT_CPP20_CONSTEXPR nt::float128_t f3 = nt::float128_t::from_double(23.13356);
    // std::cout << double(f) << std::endl;
    // NT_CPP20_CONSTEXPR nt::float128_t f2 = nt::float128_t::from_double(12.9E-54);
    // std::cout << double(f2) << std::endl;

    // NT_CPP20_CONSTEXPR nt::float128_t integer = nt::float128_t::from_integer(341);
    // std::cout <<  integer << std::endl;

    // nt::float128_t integer_set_test = 0;


    // addition_test();
    // multiplication_test();
    // multiplication_test_2();
    // division_test();
    // division_test_2();
    // division_test_3();
    // test_kmath();
    // test_sqrt();
    // test_sqrt_2();
    // test_sqrt_3();
    // std::cout << "testing exp:" << std::endl;
    // test_exp();
    // test_exp_2();
    // test_exp_3();
    // test_ldexp();
    // test_log();
    // test_log_2();
    // test_log_3();
    // test_pow();
    // test_pow_2();
    // test_pow_3();
    // test_atan();
    // test_atan_2();
    // test_atan_3();
    // test_tenth_power();
    // test_tenth_neg_power();
    // print_bits_and_number(nt::float128_func::tenth_power(100));
    // print_bits_and_number(nt::float128_func::tenth_power(-100));
    // print_bits_and_number(nt::float128_func::tenth_power(0));
    // std::cout << nt::float128_func::to_string(f) << ',' << nt::float128_func::to_string(f3) << std::endl;
    // from_string_test();
    std::cout << "atanh" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::atanh), nt::math::atanh);
    std::cout << "tanh" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::tanh), nt::math::tanh);
    std::cout << "tan" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::tan), nt::math::tan);
    std::cout << "sin" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::sin), nt::math::sin);
    std::cout << "cos" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::cos), nt::math::cos);
    std::cout << "asin" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::asin), nt::math::asin);
    std::cout << "asinh" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::asinh), nt::math::asinh);
    std::cout << "acosh" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::acosh), nt::math::acosh);
    std::cout << "log" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::log), nt::math::log);
    std::cout << "sqrt" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::sqrt), nt::math::sqrt);
    std::cout << "atan" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::atan), nt::math::atan);
    std::cout << "floor" << std::endl;
    check_functions(static_cast<double(*) (double)>(std::floor), nt::math::floor);

    int128_t a = -10;
    nt::float128_t a_to_f = portable_128_int_to_floating(a);
    std::cout << a_to_f << std::endl;

    uint128_t b = 10;
    nt::float128_t b_to_f = portable_128_int_to_floating(b);
    std::cout << b_to_f << std::endl;

    return 0;
}
