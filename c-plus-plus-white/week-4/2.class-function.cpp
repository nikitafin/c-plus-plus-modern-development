#include <vector>

class FunctionPart
{
public:
    FunctionPart(char operation, double value) : operation(operation), value(value)
    {
    }

    double Apply(double source_value) const
    {
        if (operation == '+')
        {
            return source_value + value;
        }
        else
        {
            return source_value - value;
        }
    }

    void Invert()
    {
        if (operation == '-')
        {
            operation = '+';
        }
        else
        {
            operation = '-';
        }
    }

private:
    char operation;
    double value;
};

class Function
{
public:
    void AddPart(char operaion, double value)
    {
        parts.emplace_back(operaion, value);
    }

    double Apply(double value) const
    {
        for (const auto & part : parts)
        {
            value = part.Apply(value);
        }
        return value;
    }

    void Invert()
    {
        for (auto & part : parts)
        {
            part.Invert();
        }
        std::reverse(parts.begin(), parts.end());
    }

private:
    std::vector<FunctionPart> parts;
};
