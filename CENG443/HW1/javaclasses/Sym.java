package hw1;
// MathExpression classes
public class Sym implements MathExpression {
    String value;

    public String getValue() {
        return value;
    }

    public Sym(String value) {
        this.value = value;
    }

    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if(!(me instanceof Sym)){
            return false;
        }
        if(value == ((Sym) me).getValue()){
            return  true;
        }
        return false;
    }
}
