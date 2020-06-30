package hw1;

public class Paragraph implements DocElement {
    String text;

    @Override
    public <T> T accept(TextVisitor<T> visitor) {
        return visitor.visit(this);
    }

    public String getText() {
        return text;
    }

    public Paragraph(String text) {
        this.text = text;
    }
}
