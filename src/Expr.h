#include <memory>

#include <variant>

#include <Token.h>

#pragma once

struct Expr{};

using ExprPtr = std::unique_ptr<Expr>;
using Object = std::variant<nullptr_t, bool>;

struct BinaryExpr : public Expr
{
    ExprPtr m_left;
    Token m_operator;
    ExprPtr m_right;
};

struct GroupingExpr : public Expr
{
    ExprPtr m_expression;
};

struct LiteralExpr : public Expr
{
    Object m_value;
};

struct UnaryExpr : public Expr
{
    Token m_operator;
    ExprPtr m_right;
};

