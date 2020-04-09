package l3;
import java.util.Arrays;
import java.util.Comparator;

public class l3z3_po_zmianach {
    public static void main(String[] args) {
        Item2 items[] = new Item2[3];
        TaxType butterAndFatSpreadableTaxType = new ButterAndFatSpreadableTaxType();
        TaxType normalTaxType = new NormalTaxType();
        items[0] = new Item2(13,"ser", normalTaxType);
        items[1]= new Item2(5,"szynka", normalTaxType);
        items[2] = new Item2(9,"maslo", butterAndFatSpreadableTaxType);
        BillPrinter alphabeticalBillPrinter = new AlphabeticalBillPrinter();
        CashRegister2 cashRegister = new CashRegister2(alphabeticalBillPrinter);
        System.out.println(cashRegister.PrintBill(items));
        cashRegister.billPrinter = new ByPriceBillPrinter();
        System.out.println(cashRegister.PrintBill(items));
        System.out.println("cena łączna: " + String.format("%.2f", cashRegister.CalculatePrice(items), 2));
    }
}

interface BillPrinter {
    public String PrintBill(Item2[] Items);
}

interface TaxType {
    public double Tax();
}

class Item2{
    private double price;
    private String name;
    private TaxType taxType;


    public Item2(double price, String name, TaxType taxType){
        this.price = price;
        this.name = name;
        this.taxType = taxType;
    }

    public double Price(){
        return this.price;
    }

    public String Name(){
        return this.name;
    }

    public TaxType TaxType(){
        return this.taxType;
    }
}

class TaxCalculator2{
    public double CalculateTax(Item2 item){
        return item.Price() * item.TaxType().Tax();
    }
}

class CashRegister2{
    public TaxCalculator2 taxCalc = new TaxCalculator2();
    public BillPrinter billPrinter;

    public CashRegister2(BillPrinter billPrinter){
        this.billPrinter = billPrinter;
    }

    public double CalculatePrice(Item2[] Items){
        double _price = 0;
        for(Item2 item:Items){
            _price += item.Price() + taxCalc.CalculateTax(item);
        }
        return _price;
    }

    public String PrintBill(Item2[] Items){
        return billPrinter.PrintBill(Items);
    }
}

class NormalTaxType implements TaxType {
    @Override
    public double Tax(){
        return 0.23;
    }
}

class ButterAndFatSpreadableTaxType implements TaxType {
    @Override
    public double Tax(){
        return 0.05;
    }
}

class AlphabeticalBillPrinter implements BillPrinter {
    @Override
    public String PrintBill(Item2[] Items){
        String _print = "";
        Arrays.sort(Items,
                Comparator.comparing(Item2::Name));
        for(var item:Items){
            _print += item.Name() + "\n";
        }
        return _print;
    }
}

class ByPriceBillPrinter implements BillPrinter {
    @Override
    public String PrintBill(Item2[] Items){
        String _print = "";
        Arrays.sort(Items,
                Comparator.comparing(Item2::Price));
        for(var item:Items){
            _print += item.Name() + "\n";
        }
        return _print;
    }
}

class NormalBillPrinter implements BillPrinter {
    @Override
    public String PrintBill(Item2[] Items){
        String _print = "";
        for(var item:Items){
            _print += item.Name() + "\n";
        }
        return _print;
    }
}