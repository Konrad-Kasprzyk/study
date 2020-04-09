package l3;
import java.util.Arrays;
import java.util.Comparator;

public class l3z3_przed_zmianami {
    public static void main(String[] args) {
        Item items[] = new Item[3];
        items[0] = new Item(13,"ser", "normalna");
        items[1]= new Item(5,"szynka", "normalna");
        items[2] = new Item(9,"maslo", "masła i tłuszcze do smarowania");
        CashRegister cashRegister = new CashRegister();
        System.out.println(cashRegister.PrintBill(items, "by price"));
        System.out.println("cena łączna: " + String.format("%.2f", cashRegister.CalculatePrice(items), 2));
    }
}

class TaxCalculator{
    public double CalculateTax(Item item){
        switch (item.Category()){
            case "normalna":
                return item.Price() * 0.23;
            case "masła i tłuszcze do smarowania":
                return item.Price() * 0.05;
            default:
                return item.Price() * 0.18;
        }

    }
}

class Item{
    private double price;
    private String name;
    private String category;

    public Item(double price, String name, String category){
        this.price = price;
        this.name = name;
        this.category = category;
    }

    public double Price(){
        return this.price;
    }

    public String Name(){
        return this.name;
    }

    public String Category(){
        return this.category;
    }
}

class CashRegister{
    public TaxCalculator taxCalc = new TaxCalculator();

    public double CalculatePrice(Item[] Items){
        double _price = 0;
        for(Item item:Items){
            _price += item.Price() + taxCalc.CalculateTax(item);
        }
        return _price;
    }

    public String PrintBill(Item[] Items, String how){
        String _print = "";

        switch(how){
            case "alphabetical":
                Arrays.sort(Items,
                        Comparator.comparing(Item::Name));
                break;
            case "by price":
                Arrays.sort(Items,
                        Comparator.comparing(Item::Price));
                break;
        }

        for(var item:Items){
            _print += item.Name() + "\n";
        }

        return _print;
    }
}