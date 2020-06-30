package hw1;
//MathExpression classes

public interface MathExpression {
    <T> T accept(MathVisitor<T> visitor);
        boolean match(MathExpression me);
}
