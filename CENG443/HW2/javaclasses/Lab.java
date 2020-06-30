package hw2;

import java.util.ArrayList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Lab {
    private final String name;
    private final int capacity;
    private ArrayList<StudyGroup> studyGroups;          //Represents the lab
    private StudyGroup currentStudyGroup;               //Current studyGroup which studies in the lab
    private Lock lock = new ReentrantLock();            //To make Threads work synchronously
    private Condition condition = lock.newCondition();

    //Lab constructor
    public Lab(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
        this.studyGroups = new ArrayList<>();
    }
    //Adds study group to the Lab
    public void addStudyGroup(StudyGroup studyGroup) {
        this.lock.lock();
        try {
            //Since there may be waiting students from different groups
            while(true){
                //If the lab is empty any group can get inside
                if (this.isEmpty()) {
                    this.currentStudyGroup = studyGroup;
                }
                if(this.isFull()) { condition.await(); } //wait condition to met
                // Check if the lab isn't full and the student is in the same group with the studying ones inside
                else if (!this.isFull() && getCurrentStudyGroup().getName().equals(studyGroup.getName())) {
                    // Add the student
                    this.studyGroups.add(studyGroup);
                    break;
                }
                else{ condition.await(); }
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            this.lock.unlock(); //Release lock
        }
    }
    //Removes the studyGroup from the lab
    public void removeStudyGroup(StudyGroup studyGroup) {
        this.lock.lock();
        try {
            //If lab is not empty we can remove student
            if (!this.isEmpty()) {
                this.studyGroups.remove(studyGroup);
                if(this.isEmpty()){
                    this.currentStudyGroup = null;
                }
                condition.signalAll(); //Notify all threads
            }
            //If lab is empty do nothing
            else { return; }
        }
        finally {
            this.lock.unlock();
        }
    }
    //Public getters
    public String getName() {
        return name;
    }
    public int getCapacity() {
        return capacity;
    }

    //Check if lab is full
    public boolean isFull() {
        return this.capacity == this.studyGroups.size();
    }
    //Check if lab is empty
    public boolean isEmpty() {
        return this.studyGroups.isEmpty();
    }
    //To only allow the same groups to work in a lab at the same time
    public StudyGroup getCurrentStudyGroup() {
        return this.currentStudyGroup;
    }

}
