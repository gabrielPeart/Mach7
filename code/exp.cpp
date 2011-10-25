#include <iostream>
#include <string>
#include "match_generic.hpp"

struct Expr;
struct Value;
struct Plus;
struct Minus;
struct Times;
struct Divide;

// Original visitation interface with default
struct ExprVisitor
{
    virtual void visit(const Expr&) { throw 5; } // Default handling of future classes
    virtual void visit(const Value&)  = 0;
    virtual void visit(const Plus&)   = 0;
    virtual void visit(const Minus&)  = 0;
    virtual void visit(const Times&)  = 0;
    virtual void visit(const Divide&) = 0;
};

// Root of the expression hierarchy
struct Expr 
{ 
    virtual void accept(ExprVisitor&) const = 0;
};

struct Value : Expr
{
    Value(int v) : value(v) {}
    void accept(ExprVisitor& v) const { v.visit(*this); }
    int value;
};

struct Plus : Expr
{
    Plus(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExprVisitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

struct Minus : Expr
{
    Minus(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExprVisitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

struct Times : Expr
{
    Times(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExprVisitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

struct Divide : Expr
{
    Divide(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExprVisitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

//------------------------------------------------------------------------------

std::string to_str(const Expr* e);

struct ToStrVisitor : virtual ExprVisitor
{
    // This function is needed to allow derived visitors to override handling of subvisitors
    virtual std::string evaluate(const Expr* e) const { return to_str(e); }

    using ExprVisitor::visit; // Bring in those we do not override for overload resolution

    void visit(const Value&  e) { result = "X"/*std::to_string(e.value)*/; }
    void visit(const Plus&   e) { result = '(' + evaluate(e.exp1) + '+' + evaluate(e.exp2) + ')'; }
    void visit(const Minus&  e) { result = '(' + evaluate(e.exp1) + '-' + evaluate(e.exp2) + ')'; }
    void visit(const Times&  e) { result = '(' + evaluate(e.exp1) + '*' + evaluate(e.exp2) + ')'; }
    void visit(const Divide& e) { result = '(' + evaluate(e.exp1) + '/' + evaluate(e.exp2) + ')'; }

    std::string result;
};

std::string to_str(const Expr* e)
{
    ToStrVisitor v;
    e->accept(v);
    return v.result;
}

//------------------------------------------------------------------------------

template <> struct match_members<Value>  { CM(0,Value::value); };
template <> struct match_members<Plus>   { CM(0,Plus::exp1);   CM(1,Plus::exp2);   };
template <> struct match_members<Minus>  { CM(0,Minus::exp1);  CM(1,Minus::exp2);  };
template <> struct match_members<Times>  { CM(0,Times::exp1);  CM(1,Times::exp2);  };
template <> struct match_members<Divide> { CM(0,Divide::exp1); CM(1,Divide::exp2); };

int eval1(const Expr* e)
{
    {
        auto const __selector_ptr = addr(e);
        typedef typename underlying<decltype(*__selector_ptr)>::type selector_type;
        ;
        enum 
        {
            __base_counter = 0 
        }
        ;
        typedef generic_switch<selector_type> switch_traits;
        static typename switch_traits::static_data_type static_data;
        typename switch_traits::local_data_type local_data;
        switch (switch_traits::choose(__selector_ptr,static_data,local_data)) 
        {
        case switch_traits::CaseLabel<0>::entry:
            {
                {
                    {
                        {
                        }
                    }
                }
                {
                    typedef typename switch_traits::template disambiguate<sizeof(Value)<sizeof(typename switch_traits::selector_type)>::template parameter<Value> target_specific;
                    typedef typename target_specific::target_type target_type;
                    enum 
                    {
                        default_layout = target_specific::layout, target_label = 1 -__base_counter 
                    }
                    ;
                    if (target_specific::main_condition(__selector_ptr, local_data)) 
                    {
                        switch_traits::on_first_pass(__selector_ptr, local_data, target_label);
        case target_specific::template CaseLabel<target_label>::value:
            auto matched = target_specific::get_matched(__selector_ptr,local_data);
            (void)matched;
            ;
            const auto& n = apply_member(matched, match_members<target_type,default_layout>::member0());
            {
                return n;
            }
                    }
                }
                {
                    typedef typename switch_traits::template disambiguate<sizeof(Plus)<sizeof(typename switch_traits::selector_type)>::template parameter<Plus> target_specific;
                    typedef typename target_specific::target_type target_type;
                    enum 
                    {
                        default_layout = target_specific::layout, target_label = 2 -__base_counter 
                    }
                    ;
                    if (target_specific::main_condition(__selector_ptr, local_data)) 
                    {
                        switch_traits::on_first_pass(__selector_ptr, local_data, target_label);
        case target_specific::template CaseLabel<target_label>::value:
            auto matched = target_specific::get_matched(__selector_ptr,local_data);
            (void)matched;
            ;
            const auto& a = apply_member(matched, match_members<target_type,default_layout>::member0());
            const auto& b = apply_member(matched, match_members<target_type,default_layout>::member1());
            {
                return eval(a) + eval(b);
            }
                    }
                }
                {
                    typedef typename switch_traits::template disambiguate<sizeof(Minus)<sizeof(typename switch_traits::selector_type)>::template parameter<Minus> target_specific;
                    typedef typename target_specific::target_type target_type;
                    enum 
                    {
                        default_layout = target_specific::layout, target_label = 3 -__base_counter 
                    }
                    ;
                    if (target_specific::main_condition(__selector_ptr, local_data)) 
                    {
                        switch_traits::on_first_pass(__selector_ptr, local_data, target_label);
        case target_specific::template CaseLabel<target_label>::value:
            auto matched = target_specific::get_matched(__selector_ptr,local_data);
            (void)matched;
            ;
            const auto& a = apply_member(matched, match_members<target_type,default_layout>::member0());
            const auto& b = apply_member(matched, match_members<target_type,default_layout>::member1());
            {
                return eval(a) - eval(b);
            }
                    }
                }
                {
                    typedef typename switch_traits::template disambiguate<sizeof(Times)<sizeof(typename switch_traits::selector_type)>::template parameter<Times> target_specific;
                    typedef typename target_specific::target_type target_type;
                    enum 
                    {
                        default_layout = target_specific::layout, target_label = 4 -__base_counter 
                    }
                    ;
                    if (target_specific::main_condition(__selector_ptr, local_data)) 
                    {
                        switch_traits::on_first_pass(__selector_ptr, local_data, target_label);
        case target_specific::template CaseLabel<target_label>::value:
            auto matched = target_specific::get_matched(__selector_ptr,local_data);
            (void)matched;
            ;
            const auto& a = apply_member(matched, match_members<target_type,default_layout>::member0());
            const auto& b = apply_member(matched, match_members<target_type,default_layout>::member1());
            {
                return eval(a) * eval(b);
            }
                    }
                }
                {
                    typedef typename switch_traits::template disambiguate<sizeof(Divide)<sizeof(typename switch_traits::selector_type)>::template parameter<Divide> target_specific;
                    typedef typename target_specific::target_type target_type;
                    enum 
                    {
                        default_layout = target_specific::layout, target_label = 5 -__base_counter 
                    }
                    ;
                    if (target_specific::main_condition(__selector_ptr, local_data)) 
                    {
                        switch_traits::on_first_pass(__selector_ptr, local_data, target_label);
        case target_specific::template CaseLabel<target_label>::value:
            auto matched = target_specific::get_matched(__selector_ptr,local_data);
            (void)matched;
            ;
            const auto& a = apply_member(matched, match_members<target_type,default_layout>::member0());
            const auto& b = apply_member(matched, match_members<target_type,default_layout>::member1());
            {
                return eval(a) / eval(b);
            }
                    }
                }
            }
            enum 
            {
                target_label = 6 -__base_counter 
            }
            ;
            switch_traits::on_end(__selector_ptr, local_data, target_label);
        case switch_traits::template CaseLabel<target_label>::exit:
            ;
        }
    }
}

int eval(const Expr* e)
{
    Match(e)
    {
    Case(Value, n)   return n;
    Case(Plus,  a,b) return eval(a) + eval(b);
    Case(Minus, a,b) return eval(a) - eval(b);
    Case(Times, a,b) return eval(a) * eval(b);
    Case(Divide,a,b) return eval(a) / eval(b);
    }
    EndMatch
}

const Expr* factorize(const Expr* e)
{
    const Expr *e1, *e2, *e3, *e4;

    if (match<Plus>(
            match<Times>(e1,e2),
            match<Times>(e3,e4)
        )(e))
    {
        if (e1 == e3)
            return new Times(e1, new Plus(e2,e4));
        if (e2 == e4)
            return new Times(new Plus(e1,e3), e4);
    }

    return e;
}

//------------------------------------------------------------------------------
// We now extend the class hierarchy with 2 additional classes Mod and Pow, not
// known to the original visitation interface.

struct ExtendedExpr1;
struct Mod;
struct Pow;

struct ExtendedExpr1Visitor : virtual ExprVisitor
{
    virtual void visit(const Expr& e);
    virtual void visit(const ExtendedExpr1&) { throw 6; } 
    virtual void visit(const Mod&)   = 0;
    virtual void visit(const Pow&)   = 0;
};

struct ExtendedExpr1 : Expr
{
            void accept(        ExprVisitor&  v) const { v.visit(*this); }
    virtual void accept(ExtendedExpr1Visitor& v) const { v.visit(*this); }
};

void ExtendedExpr1Visitor::visit(const Expr& e)
{
    // We really want to throw exception when it is not of that type as we 
    // cannot forward to base as it will arrive here again. When expression 
    // is not of that type, it means it is from a module that extended the 
    // hierarchy orthogonally to us, so we don't know anything about that class.
    dynamic_cast<const ExtendedExpr1&>(e).accept(*this);
}

struct Mod : ExtendedExpr1
{
    Mod(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExtendedExpr1Visitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

struct Pow : ExtendedExpr1
{
    Pow(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExtendedExpr1Visitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

std::string to_str_ex1(const Expr* e);

struct Extended1ToStrVisitor : ExtendedExpr1Visitor, ToStrVisitor
{
    // This function is needed to allow derived visitors to override handling of subvisitors
    virtual std::string evaluate(const Expr* e) const { return to_str_ex1(e); }

    using ToStrVisitor::visit; // Bring in those we do not override for overload resolution

    void visit(const ExtendedExpr1& e) { visit(static_cast<const Expr&>(e)); }
    void visit(const Mod& e)           { result = '(' + evaluate(e.exp1) + '%' + evaluate(e.exp2) + ')'; }
    void visit(const Pow& e)           { result = '(' + evaluate(e.exp1) + '^' + evaluate(e.exp2) + ')'; }
};

std::string to_str_ex1(const Expr* e)
{
    Extended1ToStrVisitor v;
    e->accept(v);
    return v.result;
}

//------------------------------------------------------------------------------
// We now independently from previous extension extend the class hierarchy with 
// another 2 classes Min and Max, not known to neither the original nor first 
// extended visitation interface.

struct ExtendedExpr2;
struct Min;
struct Max;

struct ExtendedExpr2Visitor : virtual ExprVisitor
{
    virtual void visit(const Expr& e);
    virtual void visit(const ExtendedExpr2&) { throw 7; } 
    virtual void visit(const Min&)   = 0;
    virtual void visit(const Max&)   = 0;
};

struct ExtendedExpr2 : Expr
{
            void accept(        ExprVisitor&  v) const { v.visit(*this); }
    virtual void accept(ExtendedExpr2Visitor& v) const { v.visit(*this); }
};

void ExtendedExpr2Visitor::visit(const Expr& e)
{
    // We really want to throw exception when it is not of that type as we 
    // cannot forward to base as it will arrive here again. When expression 
    // is not of that type, it means it is from a module that extended the 
    // hierarchy orthogonally to us, so we don't know anything about that class.
    dynamic_cast<const ExtendedExpr2&>(e).accept(*this);
}

struct Min : ExtendedExpr2
{
    Min(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExtendedExpr2Visitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

struct Max : ExtendedExpr2
{
    Max(const Expr* e1, const Expr* e2) : exp1(e1), exp2(e2) {}
    void accept(ExtendedExpr2Visitor& v) const { v.visit(*this); }
    const Expr* exp1;
    const Expr* exp2;
};

std::string to_str_ex2(const Expr* e);

struct Extended2ToStrVisitor : ExtendedExpr2Visitor, ToStrVisitor
{
    // This function is needed to allow derived visitors to override handling of subvisitors
    virtual std::string evaluate(const Expr* e) const { return to_str_ex2(e); }

    using ToStrVisitor::visit; // Bring in those we do not override for overload resolution

    void visit(const ExtendedExpr2& e) { visit(static_cast<const Expr&>(e)); }
    void visit(const Min& e)           { result = "min(" + evaluate(e.exp1) + ',' + evaluate(e.exp2) + ')'; }
    void visit(const Max& e)           { result = "max(" + evaluate(e.exp1) + ',' + evaluate(e.exp2) + ')'; }
};

std::string to_str_ex2(const Expr* e)
{
    Extended2ToStrVisitor v;
    e->accept(v);
    return v.result;
}

//------------------------------------------------------------------------------

int main()
{
    Expr* a = new Value(17);
    Expr* b = new Value(25);
    Expr* c = new Plus(a,b);
    std::cout << eval(c)   << std::endl;
    std::cout << to_str(c) << std::endl;

    // Mix of original operations with first extension
    Expr* d1 = new Mod(b,c);
    std::cout << eval(d1)       << std::endl;
    std::cout << to_str_ex1(d1) << std::endl;
    Expr* e1 = new Minus(c,d1);
    std::cout << eval(e1)       << std::endl;
    std::cout << to_str_ex1(e1) << std::endl;

    // Mix of original operations with second extension
    Expr* d2 = new Min(b,c);
    std::cout << eval(d2)       << std::endl;
    std::cout << to_str_ex2(d2) << std::endl;
    Expr* e2 = new Minus(c,d2);
    std::cout << eval(e2)       << std::endl;
    std::cout << to_str_ex2(e2) << std::endl;

    // Mix of operations from first and second extension
    Expr* e = new Plus(d1,d2);
    std::cout << eval(e)       << std::endl;
    //std::cout << to_str_ex2(e) << std::endl; // WRONG!

    Expr* f = new Times(a,b);
    Expr* g = new Plus(f,f);
    const Expr* h = factorize(g);
    std::cout << to_str_ex2(g) << std::endl;
    std::cout << to_str_ex2(h) << std::endl;
}
