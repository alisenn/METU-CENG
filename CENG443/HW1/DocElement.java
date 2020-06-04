package hw1;
//DocElement classes

public interface DocElement {
    <T> T accept(TextVisitor<T> visitor);
}
