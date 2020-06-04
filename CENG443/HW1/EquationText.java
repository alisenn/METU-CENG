package hw1;

public class EquationText implements DocElement {
    MathExpression innerMath;

    public MathExpression getInnerMath() {
        return innerMath;
    }

    public EquationText(MathExpression innerMath) {
        this.innerMath = innerMath;
    }

    @Override
    public <T> T accept(TextVisitor<T> visitor) {
        return visitor.visit(this);
    }
}
