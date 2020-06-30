package hw1;

public class Main {

    public static void main(String[] args) {
        Document doc = new Document("test");

        doc.add(new Paragraph("Hello, this is a big expression."));
        Op op = new Op("/", new Op("*", new Sym("x"), new Op("/", new Num(2), new Sym("y"))), new Op("+", new Sym("x"),new Num(3)));
        doc.add(new EquationText(op));

        doc.add(new Paragraph("There should be "+op.accept(new CountAtomicsVisitor()).toString()+" atomics in the above equation."));


        Rule rule = new XPlusXIs2XRule(new Var(0));

        doc.add(new Paragraph("Now a rule, it should evaluate to 2V_0"));
        doc.add(new EquationText(rule.getPremise()));
        doc.add(new Paragraph("Below fits it:"));
        Op op2 = new Op("+", new Op("/",new Sym("x"),new Sym("y")),new Op("/",new Sym("x"),new Sym("y")));
        doc.add(new EquationText(op2));

        rule = new XPlusXIs2XRule(new Var(0));
        doc.add(new Paragraph("Indeed it does:"));
        doc.add(new EquationText(new Op("|-",rule.getPremise(),rule.entails(op2))));

        rule = new XDotZeroIsZeroRule(new Var(1));
        doc.add(new Paragraph("If you multiply from the right you should get zero."));
        Op op3 = new Op("*",op,new Num(0));
        doc.add(new EquationText(op3));
        doc.add(new Paragraph("Indeed you do:"));
        doc.add(new EquationText(new Op("|-",rule.getPremise(),rule.entails(op3))));

        rule = new XDotYDivXIsYRule(new Var(2),new Var(3));

        Op op4 = new Op("+",new Num(5),new Sym("y"));
        Op op5 = new Op("/",new Num(4),new Num(2));
        Op op6 = new Op("/",new Num(4),new Num(2));
        Op op7 = new Op("/",new Op("*",op5,op4),op6);

        doc.add(new Paragraph("(X * Y)/X is Y. Try it out:"));
        doc.add(new Paragraph("This should fit:"));
        doc.add(new EquationText(op7));

        doc.add(new Paragraph("This works too!"));
        doc.add(new EquationText(new Op("|-",rule.getPremise(),rule.entails(op7))));

        System.out.println(doc.accept(new PrintHTMLVisitor()));
    }
}
