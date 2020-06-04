package hw1;

public class XDotYDivXIsYRule implements Rule {
    Var x;
    Var y;
    MathExpression premise;
    MathExpression entails;

    public Var getX() {
        return x;
    }

    public Var getY() {
        return y;
    }

    public XDotYDivXIsYRule(Var x, Var y) {
        this.x = x;
        this.y = y;
        MathExpression XDotY = new Op("*",this.x,this.y);
        //MathExpression one = new Op("*",new Num(1),new Num(1));
        premise = new Op("/",XDotY,this.x);
        entails = y;

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
