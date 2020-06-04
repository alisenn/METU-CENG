package hw1;

public class XDotZeroIsZeroRule implements Rule {
    Var x;
    MathExpression premise;
    MathExpression entails;

    public Var getX() {
        return x;
    }

    public XDotZeroIsZeroRule(Var x) {
        this.x = x;
        //MathExpression one = new Op("*",new Num(1),new Num(1));
        Num a = new Num(0);
        premise = new Op( "*",this.x,new Num(0));
        //entails = new Op("*",new Num(0),one);
        entails = a;
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
