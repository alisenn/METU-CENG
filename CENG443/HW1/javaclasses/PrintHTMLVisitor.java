package hw1;

import java.util.ArrayList;

//TextVisitor classes
public class PrintHTMLVisitor implements TextVisitor<String> {


    @Override
    public String visit(Document document) {
        String start,mid,end,result,el="";
        ArrayList<DocElement> docEl = document.getElements();
        start = "<html><head><title>";
        mid = "</title></head><body>";
        end = "</body></html>";
        int size = document.getElements().size();
        for(int i=0; i<size; i++) el += docEl.get(i).accept(new PrintHTMLVisitor());
        result = start + document.title+ mid + el + end;
        return result;
    }

    @Override
    public String visit(EquationText equationText) {
        String start,mid,end,result,el="";
        MathExpression a = equationText.getInnerMath();
        start = "<math>";
        end = "</math>";
        result = start + a.accept(new PrintMathMLVisitor()) + end;
        return result;
    }

    @Override
    public String visit(Paragraph paragraph) {
        String start,mid,end,result,el="";
        start = "<p>";
        end = "</p>";
        result = start + paragraph.getText() + end;
        return result;
    }
}
