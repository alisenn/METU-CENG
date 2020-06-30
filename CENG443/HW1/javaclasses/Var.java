package hw1;
// MathExpression classes
public class Var implements MathExpression {
    int id;
    MathExpression previousMatch;

    public int getId() {
        return id;
    }

    public Var(int id) {
        this.id = id;
    }

    public MathExpression getPreviousMatch(){
        return previousMatch;
    }

    public void setPreviousMatch(MathExpression me){
        this.previousMatch = me;
    }

    @Override
    public <T> T accept(MathVisitor<T> visitor) {
        return visitor.visit(this);
    }

    @Override
    public boolean match(MathExpression me) {
        if((getPreviousMatch() == null)){
            setPreviousMatch(me);
            return true;
        }
        else{
            return getPreviousMatch().match(me);
        }

    }
}
