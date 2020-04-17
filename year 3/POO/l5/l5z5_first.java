package l5z5_first;

import java.util.ArrayList;

public class l5z5_first {
    public static void main(String[] args){
        PersonRegistry registry = new XmlPersonRegistry(new MailPersonNotifier());
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
    protected PersonNotifier notifier;
    protected ArrayList<Person> _persons;

    public PersonRegistry(PersonNotifier notifier){
        this.notifier = notifier;
        _persons = GetPersons();
    }

    public abstract ArrayList<Person> GetPersons();

    public void NotifyPersons(){
        for (Person person: _persons) {
            this.notifier.Notify(person);
        }
    }
}

class XmlPersonRegistry extends PersonRegistry {
    public XmlPersonRegistry(PersonNotifier notifier){
        super(notifier);
    }

    @Override
    public ArrayList<Person> GetPersons(){
        ArrayList<Person> persons = new ArrayList<Person>();
        persons.add(new Person("XML person 1"));
        persons.add(new Person("XML person 2"));
        persons.add(new Person("XML person 3"));
        return persons;
    }
}

class DatabasePersonRegistry extends PersonRegistry {
    public DatabasePersonRegistry(PersonNotifier notifier){
        super(notifier);
    }

    @Override
    public ArrayList<Person> GetPersons(){
        ArrayList<Person> persons = new ArrayList<Person>();
        persons.add(new Person("Database person 1"));
        persons.add(new Person("Database person 2"));
        persons.add(new Person("Database person 3"));
        return persons;
    }
}


abstract class PersonNotifier{
    public abstract void Notify(Person person);
}

class MailPersonNotifier extends PersonNotifier {
    @Override
    public void Notify(Person person){
        System.out.println("mail sent to " + person.name);
    }
}

class SMSPersonNotifier extends PersonNotifier {
    @Override
    public void Notify(Person person){
        System.out.println("sms sent to " + person.name);
    }
}