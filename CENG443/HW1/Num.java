package hw1;
// MathExpression classes
public class Num implements MathExpression {
    int value;

    public Num(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }
    @Override
    public boolean match(MathExpression me) {
        if(!(me instanceof Num)){
            return false;
        }
        else if( value == ((Num) me).getValue()) {
            return true;
        }
        return false;


    }
}
