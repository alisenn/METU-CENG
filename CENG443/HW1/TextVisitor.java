package hw1;
//TextVisitor classes
public interface TextVisitor<T> {
    T visit(Document document);
    T visit(EquationText equationText);
    T visit(Paragraph paragraph);
}
