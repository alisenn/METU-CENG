package hw1;
//MathVisitor classes
public class PrintMathMLVisitor implements MathVisitor<String> {


    @Override
    public String visit(Op op) {
        String first,oper;
        String second;
        String preS, midS, midS2,sufS,result;

        first = (String) op.getFirst().accept(this);
        second = (String) op.getSecond().accept(this);

        if(op.operand != "/"){ // for the variables S stands for String
            preS = "<mrow><mo>(</mo>";
            midS = "<mo>";
            midS2 = "</mo>";
            sufS = "<mo>)</mo></mrow>";
            oper = op.getOperand();
            if(oper =="*"){
                oper = "&times;";
            }
            if(oper == "|-"){
                oper = "&vdash;";
            }
            result = preS + first + midS + oper + midS2 + second  + sufS;
        }
        else{
            preS = "<mrow><mfrac>";
            sufS = "</mfrac></mrow>";
            oper = op.getOperand();
            if(oper =="*"){
                oper = "&times;";
            }
            result = preS + first + second + sufS;
        }
        return result;

    }

    @Override
    public String visit(Num num) {
        String preS, midS, midS2,sufS,result;
        preS = "<mrow><mn>";
        sufS = "</mn></mrow>";
        String getValue = Integer.toString(num.getValue());
        result = preS + getValue + sufS;
        return result;
    }

    @Override
    public String visit(Sym sym) {
        String preS, midS, midS2,sufS,result;
        preS = "<mrow><mi>";
        sufS = "</mi></mrow>";
        result = preS + sym.getValue() + sufS;
        return result;
    }

    @Override
    public String visit(Var var) {
        String preS, midS, midS2,sufS,result;
        String getId = Integer.toString(var.getId());
        preS = "<mrow><msub><mi>V</mi><mn>";
        if(var.getPreviousMatch() != null){ //var with previous match
            midS2 = "</mn></msub><mo>[</mo>";
            sufS = "<mo>]</mo></mrow>";
            result = preS + getId+ midS2 + var.getPreviousMatch().accept(this) +sufS;
        }
        else{ // var with no previous match
            String elseSufS = "</mn></msub></mrow>";
            result = preS + getId + elseSufS ;
        }
        return result;
    }
}
