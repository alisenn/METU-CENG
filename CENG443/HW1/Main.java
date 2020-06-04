package hw1;


import java.io.*;
import java.util.ArrayList;

public class Main {

    public static void main(String[] args)throws FileNotFoundException  {
        // Creating a File object that represents the disk file.
        PrintStream o = new PrintStream(new File("A.html"));

        // Store current System.out before assigning a new value
        PrintStream console = System.out;

        // Assign o to output stream
        System.setOut(o);

/**********************************************Main 1******************************************************************************/
/*
        Document doc = new Document("test");
        doc.add(new Paragraph("Hello, this is a big expression."));
        Op op = new Op("/", new Op("*", new Sym("x"), new Op("/", new Num(2), new Sym("y"))), new Op("+", new Sym("x"),new Num(3)));
        doc.add(new EquationText(op));


        doc.add(new Paragraph("There should be "+op.accept(new CountAtomicsVisitor()).toString()+" atomics in the above equation."));


        Rule rule = new XPlusXIs2XRule(new Var(0));

        doc.add(new Paragraph("Now a rule, it should evaluate to 2V_0"));
        doc.add(new EquationText(rule.getPremise())); //burada bir sikinti var null veriyor
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
*/
/********************************************Main 1******************************************************************************/



        Document document = new Document("test2");

        document.add(new Paragraph("Atomics:"));
        document.add(new EquationText(new Num(42)));
        document.add(new EquationText(new Sym("x")));
        document.add(new EquationText(new Var(0)));

        document.add(new Paragraph("Ops with atomic operands:"));
        document.add(new EquationText(new Op("+", new Sym("x"), new Sym("y"))));
        document.add(new EquationText(new Op("/", new Sym("x"), new Sym("y"))));
        document.add(new EquationText(new Op("*", new Sym("x"), new Sym("y"))));
        document.add(new EquationText(new Op("|-", new Sym("x"), new Sym("y"))));

        document.add(new Paragraph("A big expression composed of small ones"));

        Sym x = new Sym("x");
        Num th = new Num(3);
        Sym y =  new Sym("y");
        Var V1 = new Var(1);

        Op small1 = new Op("/",new Op("+",x,th),V1);
        document.add(new Paragraph("small1"));
        document.add(new EquationText(small1));

        Op small2 = new Op("/",new Op("*",V1,x),new Op("/",V1,th));
        document.add(new Paragraph("small2"));
        document.add(new EquationText(small2));

        Op big = new Op("*",new Op("/",small1,V1),new Op("+",small2,x));
        document.add(new Paragraph("big"));
        document.add(new EquationText(big));

        document.add(new Paragraph(Integer.toString(big.accept(new CountAtomicsVisitor())) + " Atomics"));

        Var testvar = new Var(2);
        Op testexp = new Op("/",new Op("+",x,th),th);
        Op testexp2 = new Op("/",new Op("+",new Sym("x"),new Num(3)), new Num(3));
        Op testexp3 = new Op("/",new Op("+",new Sym("x"),new Num(3)), new Num(2));

        document.add(new Paragraph("testexp, testexp2, testexp3"));
        document.add(new EquationText(testexp));
        document.add(new EquationText(testexp2));
        document.add(new EquationText(testexp3));

        document.add(new Paragraph("testvar before being matched"));
        document.add(new Paragraph((new EquationText(testvar)).accept(new PrintHTMLVisitor()))); //hack to force print before everything is done

        document.add(new Paragraph("The match should be true with testexp since it is the first match: " + Boolean.toString(testvar.match(testexp))));
        document.add(new Paragraph("Now the situation is"));
        document.add(new Paragraph((new EquationText(testvar)).accept(new PrintHTMLVisitor()))); //hack to force print before everything is done

        document.add(new Paragraph("The match should be true with textexp2 since it is the same thing: " + Boolean.toString(testvar.match(testexp2))));
        document.add(new Paragraph("Now the situation is"));
        document.add(new Paragraph((new EquationText(testvar)).accept(new PrintHTMLVisitor()))); //hack to force print before everything is done

        document.add(new Paragraph("The match should be false with textexp3: " + Boolean.toString(testvar.match(testexp3))));
        document.add(new Paragraph("Now the situation is"));
        document.add(new Paragraph((new EquationText(testvar)).accept(new PrintHTMLVisitor()))); //hack to force print before everything is done

        document.add(new Paragraph("Try burying testvar into some big expression with other vars and then call ClearVarsVisitor to see the effects. Before"));
        Var v5 = new Var(5);
        v5.setPreviousMatch(new Num(5));
        Var v6 = new Var(6);
        v6.setPreviousMatch(new Sym("z"));
        Op big2 = new Op("/",new Num(1), new Op("/", v5, new Op("/", new Num(3), new Op("+",v6,testvar))));
        document.add(new Paragraph((new EquationText(big2)).accept(new PrintHTMLVisitor()))); //hack to force print before everything is done
        document.add(new Paragraph("after "));
        big2.accept(new ClearVarsVisitor());
        document.add(new Paragraph((new EquationText(big2)).accept(new PrintHTMLVisitor()))); //hack to force print before everything is done


        document.add(new Paragraph("Some sample expressions for X + X -| 2X"));

        Op r = new Op("/",new Num(1),new Num(0));
        Op r2 = new Op("/",new Num(1),new Num(0));

        Op matches1 = new Op("+",r,r2);
        document.add(new Paragraph("matches1"));
        document.add(new EquationText(matches1));

        Op matches2 = new Op("+",x,x);
        document.add(new Paragraph("matches2"));
        document.add(new EquationText(matches2));

        Op doesntmatch = new Op("+",x,r);
        document.add(new Paragraph("doesntmatch"));
        document.add(new EquationText(doesntmatch));

        XPlusXIs2XRule rule = new XPlusXIs2XRule(new Var(8));
        document.add(new Paragraph("rule, newly created"));
        document.add(new Paragraph((new EquationText(new Op("|-",rule.getPremise(),rule.getEntails()))).accept(new PrintHTMLVisitor())));

        document.add(new Paragraph("Try applying it to matches1, the rule is cleared, if it 'doesn't match', it should stay clear"));
        rule.apply(matches1);
        document.add(new Paragraph((new EquationText(new Op("|-",rule.getPremise(),rule.getEntails()))).accept(new PrintHTMLVisitor())));

        document.add(new Paragraph("Try applying it to matches2, the rule is cleared, if it 'doesn't match', it should stay clear"));
        rule.apply(matches2);
        document.add(new Paragraph((new EquationText(new Op("|-",rule.getPremise(),rule.getEntails()))).accept(new PrintHTMLVisitor())));

        document.add(new Paragraph("Try applying it to doesntmatch, the rule is cleared, if it 'doesn't match', it should stay clear"));
        rule.apply(doesntmatch);
        document.add(new Paragraph((new EquationText(new Op("|-",rule.getPremise(),rule.getEntails()))).accept(new PrintHTMLVisitor())));


        //System.out.println(doc.accept(new PrintHTMLVisitor())); //main1
        System.out.print(document.accept(new PrintHTMLVisitor()));// main2

        // Use stored value for output stream
        System.setOut(console);
        //System.out.println("This will be written on the console!");

        System.out.print(document.accept(new PrintHTMLVisitor()));//main2 console
        //System.out.println(doc.accept(new PrintHTMLVisitor()));


    }
}
