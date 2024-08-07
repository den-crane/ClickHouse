#include <Functions/FunctionFactory.h>
#include <Functions/FunctionStringToString.h>
#include <Functions/LowerUpperImpl.h>


namespace DB
{
namespace
{

struct NameUpper
{
    static constexpr auto name = "upper";
};
using FunctionUpper = FunctionStringToString<LowerUpperImpl<'a', 'z'>, NameUpper>;

}

REGISTER_FUNCTION(Upper)
{
    factory.registerFunction<FunctionUpper>({}, FunctionFactory::Case::Insensitive);
    factory.registerAlias("ucase", FunctionUpper::name, FunctionFactory::Case::Insensitive);
}

}
