#include "number.h"

#include <iostream>

number* number::numero = nullptr;

void number::init()
{
    numero = new number();
}

const texture number::get_texture_zero(){
    return numero->zero_instance_;
}

const texture number::get_texture_one(){
    return numero->one_instance_;
}

const texture number::get_texture_two(){
    return numero->two_instance_;
}

const texture number::get_texture_three(){
    return numero->three_instance_;
}

const texture number::get_texture_four() {
    return numero->four_instance_;
}

const texture number::get_texture_five() {
    return numero->five_instance_;
}

const texture number::get_texture_six() {
    return numero->six_instance_;
}

const texture number::get_texture_seven() {
    return numero->seven_instance_;
}

const texture number::get_texture_eight() {
    return numero->eight_instance_;
}

const texture number::get_texture_nine() {
    return numero->nine_instance_;
}


const texture number::get_texture_gamehud(){
    return numero->gamehud_instance_;
}