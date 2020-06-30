package hw1;
//Rule Classes
public interface Rule {
    default void clear(){
     this.getPremise().accept(new ClearVarsVisitor());
     this.getEntails().accept(new ClearVarsVisitor());
    }

    boolean apply(MathExpression me);
    MathExpression getPremise();
    MathExpression getEntails();
    default MathExpression entails(MathExpression me){
        apply(me);
        return getEntails();
    }
}
