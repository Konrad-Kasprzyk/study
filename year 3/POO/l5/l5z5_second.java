package l5z5_second;

import java.util.ArrayList;

public class l5z5_second {
    public static void main(String[] args){
        PersonRegistry registry = new MailPersonRegistry(new DatabasePersonGetter());
        registry.NotifyPersons();
    }
}

class Person{
    public String name;

    public Person(String name){
        this.name = name;
    }
}

abstract class PersonRegistry{
    protected PersonGetter personGetter;
    protected ArrayList<Person> _persons;

    public PersonRegistry(PersonGetter personGetter){
        this.personGetter = personGetter;
        _persons = personGetter.GetPersons();
    }

    public ArrayList<Person> GetPersons(){
        return this.personGetter.GetPersons();
    }

    public abstract void NotifyPersons();
}


class MailPersonRegistry extends PersonRegistry {
    public MailPersonRegistry(PersonGetter personGetter){
        super(personGetter);
    }

    @Override
    public void NotifyPersons(){
        for (Person person: _persons) {
            System.out.println("mail sent to " + person.name);
        }
    }
}

class SMSPersonRegistry extends PersonRegistry {
    public SMSPersonRegistry(PersonGetter personGetter){
        super(personGetter);
    }

    @Override
    public void NotifyPersons(){
        for (Person person: _persons) {
            System.out.println("sms sent to " + person.name);
        }
    }
}

abstract class PersonGetter{
    public abstract ArrayList<Person> GetPersons();
}

class XMLPersonGetter extends PersonGetter {
    @Override
    public ArrayList<Person> GetPersons(){
        ArrayList<Person> persons = new ArrayList<Person>();
        persons.add(new Person("XML person 1"));
        persons.add(new Person("XML person 2"));
        persons.add(new Person("XML person 3"));
        return persons;
    }
}

class DatabasePersonGetter extends PersonGetter {
    @Override
    public ArrayList<Person> GetPersons(){
        ArrayList<Person> persons = new ArrayList<Person>();
        persons.add(new Person("Database person 1"));
        persons.add(new Person("Database person 2"));
        persons.add(new Person("Database person 3"));
        return persons;
    }
}