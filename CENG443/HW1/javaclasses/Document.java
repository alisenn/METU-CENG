package hw1;

import java.util.ArrayList;
import java.util.Arrays;

public class Document implements DocElement {
    String title;
    ArrayList<DocElement> elements = new ArrayList<DocElement>();

    public ArrayList<DocElement> getElements() {
        return elements;
    }

    public void setElements(ArrayList<DocElement> arr) {
        this.elements = arr;
    }

    public void add(DocElement de){
        //if(elements == null)
        elements.add(de);
    }

    public Document(String title) {
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public <T> T accept(TextVisitor<T> visitor) {
        return visitor.visit(this);
    }
}
