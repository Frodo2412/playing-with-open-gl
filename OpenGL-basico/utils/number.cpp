#include "number.h"

number* number::one_instance_ = new number("../assets/numbers/uno.jpg");
number* number::two_instance_ = new number("../assets/numbers/dos.jpg");
number* number::three_instance_ = new number("../assets/numbers/tres.jpg");
number* number::four_instance_ = new number("../assets/numbers/cuatro.png");
number* number::five_instance_ = new number("../assets/numbers/cinco.png");
number* number::six_instance_ = new number("../assets/numbers/seis.png");
number* number::seven_instance_ = new number("../assets/numbers/siete.png");
number* number::eight_instance_ = new number("../assets/numbers/ocho.png");
number* number::nine_instance_ = new number("../assets/numbers/nueve.png");
number* number::zero_instance_ = new number("../assets/numbers/cero.jpg");

 const texture number::get_texture()
{
    return texture_;
}

number* number::one()
{
    return one_instance_;
}

number* number::two()
{
    return two_instance_;
}

number* number::three()
{
    return three_instance_;
}

number* number::four()
{
    return four_instance_;
}

number* number::five()
{
    return five_instance_;
}

number* number::six()
{
    return six_instance_;
}

number* number::seven()
{
    return seven_instance_;
}

number* number::eight()
{
    return eight_instance_;
}

number* number::nine()
{
    return nine_instance_;
}

number* number::zero()
{
    return zero_instance_;
}