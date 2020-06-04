package hw2;

public class StudyGroup {
    String name;
    Lab lab;

    public StudyGroup(String name, Lab lab) {
        this.name = name;
        this.lab = lab;
    }
    //Enter the lab
    public  void startStudyingWith(){
        this.lab.addStudyGroup(this);
    }
    // Leave the lab
    public  void stopStudyingWith(){
        this.lab.removeStudyGroup(this);
    }

    //Public getters
    public String getName() {
        return name;
    }

    public Lab getLab() {
        return lab;
    }



}
