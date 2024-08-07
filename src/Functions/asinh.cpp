#include <Functions/FunctionFactory.h>
#include <Functions/FunctionMathUnary.h>

namespace DB
{
namespace
{

struct AsinhName
{
    static constexpr auto name = "asinh";
};
using FunctionAsinh = FunctionMathUnary<UnaryFunctionVectorized<AsinhName, asinh>>;

}

REGISTER_FUNCTION(Asinh)
{
    factory.registerFunction<FunctionAsinh>();
}

}
