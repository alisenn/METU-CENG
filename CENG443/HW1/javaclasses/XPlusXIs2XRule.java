package hw1;

public class XPlusXIs2XRule implements Rule {
    Var x;
    MathExpression premise;
    MathExpression entails;

    public Var getX() {
        return x;
    }

    public XPlusXIs2XRule(Var x) {
        this.x = x;
        premise = new Op ("+", this.x,this.x);
        entails = new Op ("*", new Num (2),this.x);
    }

    @Override
    public boolean apply(MathExpression me) {
        clear();
        if(this.premise.match(me)){
            return true;
        }
        clear();
        return false;
    }

    @Override
    public MathExpression getPremise() {
        return premise;
    }

    @Override
    public MathExpression getEntails() {
        return entails;
    }

}
