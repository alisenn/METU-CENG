package hw1;
// MathExpression classes
public class Op implements MathExpression {
    String operand;
    MathExpression first;
    MathExpression second;

    public Op(String operand, MathExpression first, MathExpression second) {
        this.operand = operand;
        this.first = first;
        this.second = second;
    }

    public String getOperand() {
        return operand;
    }

    public MathExpression getFirst() {
        return first;
    }

    public MathExpression getSecond() {
        return second;
    }

    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if(!(me instanceof Op)){
            return false;
        }
        if(((Op) me).getOperand() != operand){
            return false;
        }
        if(!(this.getFirst().match(((Op) me).getFirst()) )){
            return  false;

        }
        if(!(this.getSecond().match(((Op) me).getSecond()) )){
            return  false;
        }
        return true;
    }

}
