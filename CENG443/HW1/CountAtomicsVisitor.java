package hw1;
//MathVisitor classes
public class CountAtomicsVisitor implements MathVisitor<Integer> {

    @Override
    public Integer visit(Op op) {
        MathExpression f = op.getFirst();
        MathExpression s = op.getSecond();
        Integer res = (Integer) s.accept(this) + (Integer) f.accept(this);
        return res;
    }

    @Override
    public Integer visit(Num num) { return 1; }

    @Override
    public Integer visit(Sym sym) {
        return 1;
    }

    @Override
    public Integer visit(Var var) {
        return 1;
    }
}
